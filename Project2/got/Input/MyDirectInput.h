//////////////////////////////////////////////////
// 作成日:2016/10/12
// 更新日:2016/12/15
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <unordered_map>
#include <d3d11.h>
#include "..\..\got\Utility\Singleton.h"
#include "..\Math\Vector2.h"

#pragma comment(lib, "dinput8.lib")
//TODO:WindowsSDKから直接パスを通す
#pragma comment(lib, "dxguid.lib")

// DirectIputクラス
namespace got
{
	class MyDirectInput : public Singleton<MyDirectInput>
	{
	public:
        enum class STICK_STATE
        {
            UP,
            DOWN,
            LEFT,
            RIGHT,
            NOT_MOVING,
        };

		~MyDirectInput();
		HRESULT init();
		HRESULT initGamepad();

        void update     ();
		bool keyDown	(const int code);
		bool keyPressed (const int code);
        bool keyReleased (const int code);
        
        bool updateGamepad();
        Vector2<float> getStickVec();
        STICK_STATE getStickPosY();
        STICK_STATE getStickPosX();
        bool buttonDown(const int pos);
        bool buttonPressed(const int pos);
        bool buttonReleased(const int pos);

        static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, LPVOID pContext);
        static BOOL CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);



	private:
		friend class Singleton<MyDirectInput>;
		MyDirectInput();

        struct enumdata
        {
            LPDIRECTINPUT8 pInput;
            LPDIRECTINPUTDEVICE8 *ppPadDevice;
        };

		unsigned char buffer[256];		// 現在の入力
		unsigned char bufferPrev[256];  // 前のフレームでの入力
        DIJOYSTATE2 padData;
        DIJOYSTATE2 padDataPrev;
        bool stickState[4];
        bool stickStatePrev[4];

		std::shared_ptr<IDirectInput8> spDInput;
		std::shared_ptr<IDirectInputDevice8> spDDevice; 
        std::shared_ptr<IDirectInputDevice8> spPadDevice;
        DIDEVCAPS diDevCaps;
	};
}