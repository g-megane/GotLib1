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
    XAudio2::XAudio2()
    {
        CoInitializeEx(nullptr, COINIT_MULTITHREADED);

        IXAudio2 *xaudio2 = nullptr;
        auto hr = XAudio2Create(&xaudio2, 0);
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

    XAudio2::~XAudio2()
    {
        spSourceVoice.reset();
        spMasteringVoice.reset();
        spXAudio2.reset();
        CoUninitialize();
    }

    bool XAudio2::openWave(const std::string& fileName)
    {
        read(fileName);

        WAVEFORMATEXTENSIBLE wfx = {};
        //TODO: Formatだけで動いた？
        wfx.Format.cbSize = static_cast<WORD>(format.size);
        wfx.Format.nAvgBytesPerSec = format.bytepersec;
        wfx.Format.nBlockAlign = format.blockalign;
        wfx.Format.nChannels = format.channels;
        wfx.Format.nSamplesPerSec = format.samplerate;
        wfx.Format.wBitsPerSample = format.bitswidth;
        wfx.Format.wFormatTag = format.format;

        XAUDIO2_BUFFER buffer = {};
        buffer.Flags = XAUDIO2_END_OF_STREAM;
        buffer.AudioBytes = data.size;
        buffer.pAudioData = data.waveFormatData.data();
        buffer.PlayBegin = 10;

        IXAudio2SourceVoice *sourceVoice = nullptr;
        auto hr = spXAudio2->CreateSourceVoice(&sourceVoice, &wfx.Format);

        hr = sourceVoice->SubmitSourceBuffer(&buffer);

        spSourceVoice = std::shared_ptr<IXAudio2SourceVoice>(sourceVoice, [](IXAudio2SourceVoice *&ptr)
        {
            if (!ptr) { return; }
            ptr->DestroyVoice();
            ptr = nullptr;
        });
        spSourceVoice->Start(0);

        return true;
    }

    bool XAudio2::read(const std::string& fileName)
    {
        std::ifstream ifs(fileName, std::ios::binary);
        if (!ifs.is_open()) {
            return false;
        }

        if (!readRiff(ifs)) {
            return false;
        }

        if (!readFmt(ifs)) {
            return false;
        }

        if (!readData(ifs)) {
            return false;
        }

        ifs.close();

        return true;
    }

    bool XAudio2::readRiff(std::ifstream& ifs)
    {
        ifs.read(reinterpret_cast<char*>(&riff), sizeof(Riff));
        if (strncmp(reinterpret_cast<char *>(&riff.riff), "RIFF", 4) != 0) {
            return false;
        }

        return true;
    }

    bool XAudio2::readFmt(std::ifstream& ifs)
    {
        ifs.read(reinterpret_cast<char*>(&format), sizeof(Format));

        if (strncmp(reinterpret_cast<char*>(&format.id), "fmt ", 4) != 0) {
            return false;
        }

        return true;
    }

    bool XAudio2::readData(std::ifstream & ifs)
    {
        ifs.read(reinterpret_cast<char*>(&data.id), sizeof(4));
        if (strncmp(reinterpret_cast<char*>(&data.id), "data", 4) != 0) {
            return false;
        }

        ifs.read(reinterpret_cast<char*>(&data.size), sizeof(4));
        data.waveFormatData.resize(data.size);
        ifs.read(reinterpret_cast<char*>(data.waveFormatData.data()), data.size);

        return true;
    }

    bool XAudio2::play()
    {
        spSourceVoice->Start(0);

        //Sleep(5000);

        //spSourceVoice->Stop();
        //spSourceVoice->DestroyVoice();

        return true;
    }
}