#include "XAudio2.h"
#include <fstream>

template<class T>
void safeRelease(T *&ptr)
{
    if (!ptr) return;
    ptr->Release();
    ptr = nullptr;
}

namespace got {
    // コンストラクタ
    XAudio2::XAudio2()
    {
        auto hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
        if (FAILED(hr)) {
            return;
        }

        IXAudio2 *xaudio2 = nullptr;
        hr = XAudio2Create(&xaudio2, 0);
        if (FAILED(hr)) {
            spXAudio2 = std::shared_ptr<IXAudio2>(xaudio2, safeRelease<IXAudio2>);
            CoUninitialize();
            return;
        }

        IXAudio2MasteringVoice *masteringVoice = nullptr;
        hr = xaudio2->CreateMasteringVoice(&masteringVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, nullptr);
        if (FAILED(hr)) {
            spXAudio2 = std::shared_ptr<IXAudio2>(xaudio2, safeRelease<IXAudio2>);
            CoUninitialize();
            return;
        }

        spMasteringVoice = std::shared_ptr<IXAudio2MasteringVoice>(masteringVoice, [](IXAudio2MasteringVoice *&ptr)
        {
            if (!ptr) { return; }
            ptr->DestroyVoice();
            ptr = nullptr;
        });
        spXAudio2 = std::shared_ptr<IXAudio2>(xaudio2, safeRelease<IXAudio2>);
    }
    // デストラクタ
    XAudio2::~XAudio2()
    {
        //while (itr != voices_.end()) {
        //    (*itr)->Stop();
        //    (*itr)->DestroyVoice();
        //     voices_.erase(itr);
        //     ++itr;
        //}
        voices_.clear();
        //spSourceVoice.reset();
        BGM.reset();
        spMasteringVoice.reset();
        spXAudio2.reset();
        CoUninitialize();
    }
    // Waveファイルの読み込み
    bool XAudio2::openWave(const std::string keyName, const std::string& fileName)
    {
        std::ifstream ifs(fileName, std::ios::binary);

        // riffチャンクの読み込み
        Riff riff;
        // 構造体のサイズ分一気に読み込む
        ifs.read(reinterpret_cast<char*>(&riff), sizeof(Riff));
        if (strncmp(reinterpret_cast<char *>(&riff.riff), "RIFF", 4) != 0) {
            return false;
        }

        // fmtチャンクの読み込み
        Format format;
        // 構造体のサイズ分一気に読み込む
        ifs.read(reinterpret_cast<char*>(&format), sizeof(Format));
        if (strncmp(reinterpret_cast<char*>(&format.id), "fmt ", 4) != 0) {
            return false;
        }

        // dataチャンクの読み込み
        //   daraチャンクはファイル毎にデータのサイズが違うので
        //   sizeを見てその分だけ読み込む
        Data data;
        ifs.read(reinterpret_cast<char*>(&data.id), sizeof(4));
        if (strncmp(reinterpret_cast<char*>(&data.id), "data", 4) != 0) {
            return false;
        }
        ifs.read(reinterpret_cast<char*>(&data.size), sizeof(4));
        data.waveFormatData.resize(data.size);
        ifs.read(reinterpret_cast<char*>(data.waveFormatData.data()), data.size);

        WAVEFORMATEXTENSIBLE wfx = {};
        wfx.Format.cbSize          = static_cast<WORD>(format.size);
        wfx.Format.nAvgBytesPerSec = format.bytepersec;
        wfx.Format.nBlockAlign     = format.blockalign;
        wfx.Format.nChannels       = format.channels;
        wfx.Format.nSamplesPerSec  = format.samplerate;
        wfx.Format.wBitsPerSample  = format.bitswidth;
        wfx.Format.wFormatTag      = format.format;

        Wave wave;
        wave.data = data;
        wave.wfx  = wfx;

        waveMap[keyName] = wave;

        return true;
    }

    //bool XAudio2::read(const std::string& fileName)
    //{
    //    std::ifstream ifs(fileName, std::ios::binary);
    //    if (!ifs.is_open()) {
    //        return false;
    //    }
    //
    //    if (!readRiff(ifs)) {
    //        return false;
    //    }
    //
    //    if (!readFmt(ifs)) {
    //        return false;
    //    }
    //
    //    if (!readData(ifs)) {
    //        return false;
    //    }
    //
    //    ifs.close();
    //
    //    return true;
    //}
    //
    //// RIFFヘッダの読み込み
    //bool XAudio2::readRiff(std::ifstream& ifs)
    //{
    //    ifs.read(reinterpret_cast<char*>(&riff), sizeof(Riff));
    //    if (strncmp(reinterpret_cast<char *>(&riff.riff), "RIFF", 4) != 0) {
    //        return false;
    //    }
    //
    //    return true;
    //}
    //
    //// fmtチャンクの読み込み
    //bool XAudio2::readFmt(std::ifstream& ifs)
    //{
    //    ifs.read(reinterpret_cast<char*>(&format), sizeof(Format));
    //
    //    if (strncmp(reinterpret_cast<char*>(&format.id), "fmt ", 4) != 0) {
    //        return false;
    //    }
    //
    //    return true;
    //}
    //
    //// dataチャンクの読み込み
    //bool XAudio2::readData(std::ifstream & ifs)
    //{
    //    ifs.read(reinterpret_cast<char*>(&data.id), sizeof(4));
    //    if (strncmp(reinterpret_cast<char*>(&data.id), "data", 4) != 0) {
    //        return false;
    //    }
    //
    //    ifs.read(reinterpret_cast<char*>(&data.size), sizeof(4));
    //    data.waveFormatData.resize(data.size);
    //    ifs.read(reinterpret_cast<char*>(data.waveFormatData.data()), data.size);
    //
    //    return true;
    //}

    // 終了している効果音を探し終了処理を行う
    void XAudio2::update()
    {
        auto itr = voices_.begin();
        while (itr != voices_.end()) {
            XAUDIO2_VOICE_STATE state;
            (*itr)->GetState(&state);
            if (state.BuffersQueued <= 0) {
                itr = voices_.erase(itr);
            }
            else {
                ++itr;
            }
        }
    }

    // ループ再生
    bool XAudio2::playBGM(const std::string key)
    {
        // 引数で渡されたkeyがあるか？
        if (waveMap.find(key) == waveMap.end()) {
            return false;
        }

        XAUDIO2_BUFFER buffer = {};
        buffer.Flags      = XAUDIO2_END_OF_STREAM;
        buffer.AudioBytes = waveMap[key].data.size;
        buffer.pAudioData = waveMap[key].data.waveFormatData.data();
        buffer.LoopCount  = XAUDIO2_LOOP_INFINITE;

        IXAudio2SourceVoice *sourceVoice = nullptr;
        auto hr = spXAudio2->CreateSourceVoice(&sourceVoice, &waveMap[key].wfx.Format);
        if (FAILED(hr)) {
            sourceVoice->DestroyVoice();
            return false;
        }

        hr = sourceVoice->SubmitSourceBuffer(&buffer);
        if (FAILED(hr)) {
            sourceVoice->DestroyVoice();
            return false;
        }

        BGM = std::shared_ptr<IXAudio2SourceVoice>(sourceVoice, [](IXAudio2SourceVoice *&ptr)
        {
            if (!ptr) { return; }
            ptr->DestroyVoice();
            ptr = nullptr;
        });
                
        BGM->Start(0);

        return true;
    }

    // ループなしの再生
    bool XAudio2::play(const std::string key)
    {
        // 引数で渡されたkeyがあるか？
        if (waveMap.find(key) == waveMap.end()) {
            return false;
        }

        XAUDIO2_BUFFER buffer = {};
        buffer.Flags = XAUDIO2_END_OF_STREAM;
        buffer.AudioBytes = waveMap[key].data.size;
        buffer.pAudioData = waveMap[key].data.waveFormatData.data();

        IXAudio2SourceVoice *sourceVoice = nullptr;
        auto hr = spXAudio2->CreateSourceVoice(&sourceVoice, &waveMap[key].wfx.Format);

        hr = sourceVoice->SubmitSourceBuffer(&buffer);
        if (FAILED(hr)) {
            sourceVoice->DestroyVoice();
            return false;
        }

        decltype(spSourceVoice) temp = nullptr;
        temp = std::shared_ptr<IXAudio2SourceVoice>(sourceVoice, [](IXAudio2SourceVoice *&ptr)
        {
            if (!ptr) { return; }
            ptr->Stop();
            ptr->DestroyVoice();
            ptr = nullptr;
        });

        voices_.emplace_back(temp);
        //spSourceVoice.reset();

        sourceVoice->Start(0);

        return true;
    }

    // ループ再生しているBGMを止める
    void XAudio2::stopBGM()
    {
        if (BGM != nullptr) {
            BGM->Stop();
            BGM = nullptr;
        }
    }
}