//////////////////////////////////////////////////
// 作成日:2016/10/12
// 更新日:2016/12/15
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
        spPadDevice = nullptr;
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

    HRESULT MyDirectInput::initGamepad()
    {
        LPDIRECTINPUT8 dInput = nullptr;

        auto hr = DirectInput8Create
        (
            GetModuleHandle(nullptr),		   // オブジェクトを作成するアプリケーションまたはDLLのインスタンスハンドル
            DIRECTINPUT_VERSION,			   // どのバージョンのDirectInputシステムをDirectInputオブジェクトに使うかを指定
            IID_IDirectInput8,				   // 返るインターフェースを指定（ほとんどのアプリケーションは「IID_IDirectInput8」を渡して最新のバージョンを取得）
            reinterpret_cast<void**>(&dInput), // 呼び出しが成功した場合に、有効なインターフェースポインタで初期化される変数のアドレスである
            nullptr							   // 基本NULLでいい
        );
        if (FAILED(hr)) {
            spDInput = std::shared_ptr<IDirectInput8>(dInput, safeRelease<LPDIRECTINPUT8>);
            return hr;
        }
        spDInput = std::shared_ptr<IDirectInput8>(dInput, safeRelease<LPDIRECTINPUT8>);

        LPDIRECTINPUTDEVICE8 dDevice = spPadDevice.get();

        enumdata ed;
        ed.pInput = spDInput.get();
        ed.ppPadDevice = &dDevice;

        hr = dInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, &ed, DIEDFL_ATTACHEDONLY);
       // if (FAILED(hr) || spDDevice == nullptr) {
       //     spDDevice = std::shared_ptr<IDirectInputDevice8>(*ed.ppPadDevice, [](LPDIRECTINPUTDEVICE8 & ptr)
       //     {
       //         if (ptr == nullptr) return;
       //         ptr->Unacquire();
       //         safeRelease<LPDIRECTINPUTDEVICE8>(ptr);
       //     });
       //     return hr;
       // }
        if (FAILED(hr)) {
            spPadDevice = std::shared_ptr<IDirectInputDevice8>(dDevice, [](LPDIRECTINPUTDEVICE8 & ptr)
            {
                if (ptr == nullptr) return;
                ptr->Unacquire();
                safeRelease<LPDIRECTINPUTDEVICE8>(ptr);
            });
            return hr;
        }
        spPadDevice = std::shared_ptr<IDirectInputDevice8>(dDevice, [](LPDIRECTINPUTDEVICE8 & ptr)
        {
            if (ptr == nullptr) return;
            ptr->Unacquire();
            safeRelease<LPDIRECTINPUTDEVICE8>(ptr);
        });
        if (spPadDevice == nullptr) {
            return S_FALSE;
        }

        hr = spPadDevice->SetDataFormat(&c_dfDIJoystick2);
        if (FAILED(hr)) {
            return hr;
        }

        hr = spPadDevice->SetCooperativeLevel(DirectX11::getInstance().getWindow()->getHWND(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
        if (FAILED(hr)) {
            return hr;
        }
        
        diDevCaps.dwSize = sizeof(DIDEVCAPS);
        hr = spPadDevice->GetCapabilities(&diDevCaps);
        if (FAILED(hr)) {
            return hr;
        }

        hr = spPadDevice->EnumObjects(EnumAxesCallback, &ed, DIDFT_AXIS);
        if (FAILED(hr)) {
            return hr;
        }

       // hr = spDDevice->EnumObjects(EnumAxesCallback, this, DIDFT_AXIS);
       // if (FAILED(hr)) {
       //     return hr;
       // }

        return S_OK;
    }

    // キー情報の更新
    void MyDirectInput::update()
    {
        if (spDDevice == nullptr) { return; }
        std::copy(std::begin(buffer), std::end(buffer), bufferPrev);
        spDDevice->GetDeviceState(sizeof(buffer), &buffer);
    }

    // キーが押されているか
	bool MyDirectInput::keyDown(const int code)
	{
        if (spDDevice == nullptr) { return false; }
		// キーボードへのアクセス権の取得
		spDDevice->Acquire();

		//spDDevice->GetDeviceState(sizeof(buffer), &buffer);

		if (buffer[code] & 0x80) {
			return true;
		}
		return false;
	}
	// キーが押された瞬間か
	bool MyDirectInput::keyPressed(const int code)
	{
        if (spDDevice == nullptr) { return false; }
		bool result = false;
		// キーボードへのアクセス権の取得
		spDDevice->Acquire();

		//spDDevice->GetDeviceState(sizeof(buffer), &buffer);

		if ((buffer[code] & 0x80) != 0 && (bufferPrev[code] & 0x80) == 0) {
			result = true;
		}
		//std::copy(std::begin(buffer), std::end(buffer), bufferPrev);

		return result;
	}
	// キーが離した瞬間か
	bool MyDirectInput::keyReleased(const int code)
	{
        if (spDDevice == nullptr) { return false; }
        bool result = false;
        // キーボードへのアクセス権の取得
        spDDevice->Acquire();

        //spDDevice->GetDeviceState(sizeof(buffer), &buffer);

        if ((buffer[code] & 0x80) == 0 && (bufferPrev[code] & 0x80) != 0) {
            result = true;
        }
        std::copy(std::begin(buffer), std::end(buffer), bufferPrev);

        return result;
	}
    bool MyDirectInput::updateGamepad()
    {
        if(spPadDevice == nullptr) { return false; }
        auto hr = spPadDevice->Poll();
        if (FAILED(hr)) {
            spPadDevice->Acquire();
            //return false;
        }
        

        memcpy(&padDataPrev, &padData, sizeof(DIJOYSTATE2));
        hr = spPadDevice->GetDeviceState(sizeof(DIJOYSTATE2), &padData);
        if (FAILED(hr)) {
            return false;
        }

        return true;
    }
    MyDirectInput::STICK_STATE MyDirectInput::getStickPosY()
    {
        if (spPadDevice == nullptr) { return STICK_STATE::NOT_MOVING; }
        if (padData.lY < -500) {
            return STICK_STATE::UP; 
        }
        else if (padData.lY > 500) {
            return STICK_STATE::DOWN;
        }

        return STICK_STATE::NOT_MOVING;
    }
    MyDirectInput::STICK_STATE MyDirectInput::getStickPosX()
    {
        if (padData.lX < -500) {
            return STICK_STATE::LEFT;
        }
        else if (padData.lX > 500) {
            return STICK_STATE::RIGHT;
        }

        return STICK_STATE();
    }
    bool MyDirectInput::buttonDown(const int pos)
    {
        if(spPadDevice == nullptr) { return false; }
        return padData.rgbButtons[pos];
    }
    bool MyDirectInput::buttonPressed(const int pos)
    {
        if(spPadDevice == nullptr) { return false; }
        if (padData.rgbButtons[pos] && !padDataPrev.rgbButtons[pos]) {
            return true;
        }
        return false;
    }
    bool MyDirectInput::buttonReleased(const int pos)
    {
        if (spPadDevice == nullptr) { return false; }
        if (!padData.rgbButtons[pos] && padDataPrev.rgbButtons[pos]) {
            return true;
        }
        return false;
    }
    // ジョイスティックを列挙する関数
    //      使用するデバイスが見つかればLPDIRECTINPUTDEVICE8に設定して、DIENUM_STOPをリターンする
    BOOL MyDirectInput::EnumJoysticksCallback(const DIDEVICEINSTANCE * pdidInstance, LPVOID  pContext)
    {
        // SampleではC関数としてEnumJoysticksCallbackが宣言されているが、
        // ここでは、class MyDirectInputのメンバ関数として宣言されている。
        // このメンバ関数(非static)が実際に何に対応するかは、実行時に決定さ
        // れるためコンパイラには分からない。結果error C2276が発生した。
        // 解決策：・MyDirectInputクラスのstaticメンバ関数として宣言
        //        ・C関数として宣言する
        // どちらを選ぶにしてもthisポインタが利用できないので「VOID* pContext」
        // にMyDirectInputのインスタンスを渡すことになる
        enumdata* ed = reinterpret_cast<enumdata*>(pContext);

        //LPDIRECTINPUTDEVICE8 dDevice = ed->ppPadDevice;
        // 列挙されたジョイスティックへのインターフェースを取得する
        auto hr = ed->pInput->CreateDevice(pdidInstance->guidInstance, ed->ppPadDevice, nullptr);
        if (FAILED(hr)) {
            return DIENUM_CONTINUE;
        }

        return DIENUM_STOP;
    }
    BOOL MyDirectInput::EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
    {
        enumdata* ed = reinterpret_cast<enumdata*>(pvRef);
    
        DIPROPRANGE diprg;
        ZeroMemory(&diprg, sizeof(diprg));
        diprg.diph.dwSize = sizeof(diprg);
        diprg.diph.dwHeaderSize = sizeof(diprg.diph);
        diprg.diph.dwObj = lpddoi->dwType;
        diprg.diph.dwHow = DIPH_BYID;
        diprg.lMin = -1000;
        diprg.lMax =  1000;
        auto hr = ed->ppPadDevice[0][0].SetProperty(DIPROP_RANGE, &diprg.diph);
        if (FAILED(hr)) {
            return DIENUM_STOP;
        }
    
        return DIENUM_CONTINUE;
    }
}
