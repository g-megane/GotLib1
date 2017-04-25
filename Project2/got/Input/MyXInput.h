//////////////////////////////////////////////////
// çÏê¨ì˙:2017/4/22
// çXêVì˙:2017/4/22
// êßçÏé“:got
//////////////////////////////////////////////////
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "../Utility/Singleton.h"
#include "../Math/Vector2.h"


#ifdef USE_DIRECTX_SDK
#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\include\xinput.h>
#pragma comment(lib,"xinput.lib")
#elif (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/)
#include <XInput.h>
#pragma comment(lib,"xinput.lib")
#else
#include <XInput.h>
#pragma comment(lib,"xinput9_1_0.lib")
#endif

#define MAX_CONTROLLERS 4
#define INPUT_DEADZONE (0.24f * FLOAT(0x7fff))

namespace got
{
    class MyXInput : public Singleton<MyXInput>
    {
    public:
        ~MyXInput();
        HRESULT updateControllerState();

        bool isButtonDown(const DWORD playerIndex_, const WORD key_);
        bool isButtonPressed(const DWORD playerIndex_, const WORD key_);
        bool isButtonReleased(DWORD playerIndex_, const WORD key_);
        bool isPadUp(const DWORD playerIndex_);
        bool isPadDown(const DWORD playerIndex_);
        bool isPadRight(const DWORD playerIndex_);
        bool isPadLeft(const DWORD playerIndex_);
        Vector2<float> padVec(const DWORD playerIndex_, const bool useDeadZone = true);

        void setLeftVibration(const DWORD playerIndex_, const WORD motorSpeed);
        void setRightVibration(const DWORD playerIndex_, const WORD motorSpeed);

    private:
        friend class Singleton<MyXInput>;
        MyXInput();
        bool isNeutral(DWORD playerIndex_);

        bool padInputPrev;

        struct CONTROLLER_STATE
        {
            XINPUT_STATE     state;
            XINPUT_STATE     statePrev;
            bool             connected;
            bool             lockVibration;
            XINPUT_VIBRATION vibration;
        };

        CONTROLLER_STATE controllers[MAX_CONTROLLERS];
    };
}
