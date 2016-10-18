//////////////////////////////////////////////////
// 作成日:2016/10/12
// 更新日:2016/10/17
// 制作者:got
//////////////////////////////////////////////////
#include "MyDirectInput.h"
#include "DirectX11.h"
#include "Window.h"

template<typename Ptr>
void safeRelease(Ptr & ptr)
{
	if (ptr == nullptr) return;
	ptr->Release();
	ptr = nullptr;
}

namespace got
{
	// コンストラクタ
	MyDirectInput::MyDirectInput()
	{
		spDInput  = nullptr;
		spDDevice = nullptr;
	}
	// デストラクタ
	MyDirectInput::~MyDirectInput()
	{
	}
	// DirectInputの初期化
	HRESULT MyDirectInput::init()
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
		spDInput = std::shared_ptr<IDirectInput8>(dInput, safeRelease<LPDIRECTINPUT8>);
		if (FAILED(hr)) {
			return E_FAIL;
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
		spDDevice = std::shared_ptr<IDirectInputDevice8>(dDevice, [](LPDIRECTINPUTDEVICE8 & ptr)
		{
			if (ptr == nullptr) return;
			ptr->Unacquire();
			safeRelease<LPDIRECTINPUTDEVICE8>(ptr);
		});
		if (FAILED(hr)) {
			return E_FAIL;
		}
		
		// キーボードのデータ形式の設定
		hr = dDevice->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(hr)) {
			return E_FAIL;
		}

		// キーボードの動作の設定
		hr = dDevice->SetCooperativeLevel
		(
			DirectX11::getInstance().getWindow()->getHWND(),
			DISCL_FOREGROUND | DISCL_NONEXCLUSIVE
		);
		if (FAILED(hr)) {
			return E_FAIL;
		}

		return S_OK;
	}
	// キーが押されているか
	bool MyDirectInput::keyPush(const int code)
	{
		// キーボードへのアクセス権の取得
		spDDevice->Acquire();

		spDDevice->GetDeviceState(sizeof(buffer), &buffer);

		if (buffer[code] & 0x80) {
			return true;
		}
		return false;
	}
	// キーが押された瞬間か
	bool MyDirectInput::keyTrigger(const int code)
	{
		bool result = false;
		// キーボードへのアクセス権の取得
		spDDevice->Acquire();

		spDDevice->GetDeviceState(sizeof(buffer), &buffer);

		if ((buffer[code] & 0x80) != 0 && (bufferPrev[code] & 0x80) == 0) {
			result = true;
		}
		std::copy(std::begin(buffer), std::end(buffer), bufferPrev);

		return result;
	}
	// キーが離した瞬間か
	//bool MyDirectInput::keyRelease(const int code)
	//{
	//	return false;
	//}
}
