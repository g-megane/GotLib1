//////////////////////////////////////////////////
// 作成日:2016/10/12
// 更新日:2016/10/12
// 制作者:got
//////////////////////////////////////////////////
#include "MyDirectInput.h"
#include "DirectX11.h"
#include "Window.h"

namespace got
{
	// コンストラクタ
	MyDirectInput::MyDirectInput()
	{
	}
	// DirectInputの初期化
	bool MyDirectInput::init()
	{
		// DirectInputオブジェクトの作成
		LPDIRECTINPUT8 dInput = nullptr;
		
		auto hr = DirectInput8Create
		(
			GetModuleHandle(nullptr),		   // オブジェクトを作成するアプリケーションまたはDLLのインスタンスハンドル
			DIRECTINPUT_VERSION,			   // どのバージョンのDirectInputシステムをDirectInputオブジェクトに使うかを指定
			IID_IDirectInput8,				   // 返るインターフェースを指定（ほとんどのアプリケーションは「IID_IDirectInput8」を渡して最新のバージョンを取得）
			reinterpret_cast<void**>(&dInput), // 呼び出しが成功した場合に、有効なインターフェースポインタで初期化される変数のアドレスである
			nullptr							   // 基本NULLでいい
		);
		// 型が違うように見えるがLPDIRECTINPUT8はIDirectInput8
		// shred_ptr<LPDIRECTINPUT8>だとポインターのポインター
		// になってしまうので下記のようになっている
		spDInput = std::shared_ptr<IDirectInput8>(dInput, [](LPDIRECTINPUT8 ptr)
		{
			if (ptr == nullptr) return;
			ptr->Release();
			ptr = nullptr;
		});
		if (FAILED(hr)) {
			return false;
		}

		// DirectInputキーボードデバイスの作成
		LPDIRECTINPUTDEVICE8 dDevice = nullptr;
		
		hr = dInput->CreateDevice
		(
			GUID_SysKeyboard, // 作成するデバイスのグローバル一意識別子（GUID）
			&dDevice,		  // 成功した場合にインターフェースポインタで初期化される変数のアドレス
			nullptr			  // 通常はNULLを設定
		);
		// 型が違うように見えるがLPDIRECTINPUTDEVICE8はIDirectInputDevice8
		// shred_ptr<LPDIRECTINPUTDEVICE8>だとポインターのポインター
		// になってしまうので下記のようになっている
		spDDevice = std::shared_ptr<IDirectInputDevice8>(dDevice, [](LPDIRECTINPUTDEVICE8 ptr)
		{
			ptr->Unacquire();
			ptr->Release();
			ptr = nullptr;
		});
		if (FAILED(hr)) {
			return false;
		}
		
		// キーボードのデータ形式の設定
		hr = dDevice->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(hr)) {
			return false;
		}

		// キーボードの動作の設定
		hr = dDevice->SetCooperativeLevel
		(
			DirectX11::getInstance().getWindow()->getHWND(),
			DISCL_FOREGROUND | DISCL_NONEXCLUSIVE
		);
		if (FAILED(hr)) {
			return false;
		}

		// キーボードへのアクセス権の取得
		hr = dDevice->Acquire();
		if (FAILED(hr)) {
			return false;
		}

		return true;
	}
}
