//////////////////////////////////////////////////
// 作成日:2016/10/12
// 更新日:2016/12/15
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include<dinput.h>
#include<unordered_map>
#include<d3d11.h>

#pragma comment(lib, "dinput8.lib")
//TODO:WindowsSDKから直接パスを通す
#pragma comment(lib, "dxguid.lib")

#include"Singleton.h"

// DirectIputクラス
namespace got
{
	class MyDirectInput : public Singleton<MyDirectInput>
	{
	public:
		~MyDirectInput();
		HRESULT init();
		
        void update     ();
		bool keyPush	(const int code);
		bool keyTrigger (const int code);
        bool keyRelease (const int code);

	private:
		friend class Singleton<MyDirectInput>;
		MyDirectInput();

		unsigned char buffer[256];		// 現在の入力
		unsigned char bufferPrev[256];  // 前のフレームでの入力

		std::shared_ptr<IDirectInput8> spDInput;
		std::shared_ptr<IDirectInputDevice8> spDDevice; 
	};
}