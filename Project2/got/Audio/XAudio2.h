//////////////////////////////////////////////////
// 作成日:2016/12/6
// 更新日:2016/12/6
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#pragma comment(lib, "xaudio2.lib")
#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include <xaudio2.h>
#include <mmsystem.h>
#include <memory>
#include <vector>
#include <unordered_map>
#include "..\..\got\Utility\Singleton.h"

namespace got {
    class XAudio2 : public Singleton<XAudio2>
    {
    public:
        ~XAudio2();
        bool openWave(const std::string& keyName, const std::string& fileName);

        void update();
        bool playBGM(const std::string& key);
        bool play(const std::string& key);
        void stopBGM();

        struct Riff
        {
            uint32_t riff;
            int32_t  size;
            uint32_t type;
        };

        struct Format
        {
            uint32_t id;
            int32_t  size;
            int16_t  format;
            uint16_t channels;
            uint32_t samplerate;
            uint32_t bytepersec;
            uint16_t blockalign;
            uint16_t bitswidth;
        };

        struct Data
        {
            uint32_t id;
            int32_t  size;
            std::vector<uint8_t> waveFormatData;
        };

        struct Wave
        {
            WAVEFORMATEXTENSIBLE wfx;
            Data data;
        };

    private:
        friend class Singleton<XAudio2>;
        XAudio2();

        //bool read(const std::string &fileName);
        //bool readRiff(std::ifstream &ifs);
        //bool readFmt(std::ifstream &ifs);
        //bool readData(std::ifstream &ifs);

        std::unordered_map<std::string, Wave> waveMap;
        std::vector<std::shared_ptr<IXAudio2SourceVoice>> voices_;

        std::shared_ptr<IXAudio2> spXAudio2;
        std::shared_ptr<IXAudio2MasteringVoice> spMasteringVoice;
        std::shared_ptr<IXAudio2SourceVoice> BGM;
        std::shared_ptr<IXAudio2SourceVoice> spSourceVoice;
    };

}