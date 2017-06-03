//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/10/1
// 制作者:got
//////////////////////////////////////////////////
#include <tchar.h>
#include <algorithm>
#include "DirectX11.h"
#include "..\..\Game\Common\GV.h"
#include "..\Window\Window.h"

template<typename Ptr>
void safeRelease(Ptr *& ptr)
{
	if (ptr == nullptr) return;
	ptr->Release();
	ptr = nullptr;
}

namespace got
{
	// コンストラクタ
	got::DirectX11::DirectX11()
	{
	}
	// デストラクタ
	got::DirectX11::~DirectX11()
	{
	}
	// 初期化関数
	HRESULT DirectX11::initialize(std::shared_ptr<Window> _window)
	{
		window			   = _window;
		spDevice		   = nullptr;
		spDeviceContext	   = nullptr;
		spSwapChain		   = nullptr;
		spRenderTargetView = nullptr;
		featureLevel	   = D3D_FEATURE_LEVEL_11_0;
		g_driverType	   = D3D_DRIVER_TYPE_NULL;
		clearColor		   = Color<float>::BLUE;

		init = createDeviceAndSwapChain();
		if (FAILED(init)) {
			OutputDebugString("createDeviceAndSwapChain()の失敗");
			return E_FAIL;
		}
		
		init = createRenderTargetView();
		if (FAILED(init)) {
			OutputDebugString("createRenderTargetView()の失敗");
			return E_FAIL;
		}
		setRenderTargetView();

		return S_OK;
	}

	// フレームを開始
	void DirectX11::begineFrame() const
	{
		//TODO:Colorクラスを作って実装しなおし
		float ClearColor[4]{ 0.0f, 0.125f, 0.3f, 1.0f };
		// レンダーターゲットのすべての要素に１つの値を設定
		spDeviceContext->ClearRenderTargetView(spRenderTargetView.get(), ClearColor);
	}

	// フレームを終了
	void DirectX11::endFrame() const
	{
        //spRenderTarget->EndDraw();
		spSwapChain->Present(0, 0); // レンダリングされたイメージをユーザーに表示
	}

	// 初期化が正常に完了しているか
	HRESULT DirectX11::isInit() const
	{
		return init;
	}

	// デバイスを取得する
	std::shared_ptr<ID3D11Device> DirectX11::getDevice() const
	{
		return spDevice;
	}

	// デバイスコンテキストを取得
	std::shared_ptr<ID3D11DeviceContext> DirectX11::getDeviceContext() const
	{
		return spDeviceContext;
	}
	std::shared_ptr<Window> DirectX11::getWindow() const
	{
		return window;
	}
	// サイズを返す
	Dimention<int> DirectX11::getSize() const
	{
		return size;
	}

	// デバイスとスワップチェーンを作成
	HRESULT DirectX11::createDeviceAndSwapChain()
	{
		ID3D11Device		*device		   = nullptr;
		ID3D11DeviceContext *deviceContext = nullptr;
		IDXGISwapChain		*swapChain	   = nullptr;
		HRESULT				 hr			   = S_OK;
		size = window->getWindowSize();

		// ドライバーの種類のオプション
		D3D_DRIVER_TYPE driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE,
		};
		UINT numDriverTypes = ARRAYSIZE(driverTypes);

		// Direct3Dデバイスのターゲットとなる機能セット
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1,
		};
		UINT numFeatureLevels = ARRAYSIZE(featureLevels);

		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 1;								   // スワップチェーンのバッファー数
		sd.BufferDesc.Width = size.width;				   // 解像度の幅
		sd.BufferDesc.Height = size.height;				   // 解像度の高さ
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 表示フォーマット
		sd.BufferDesc.RefreshRate.Numerator = 60;		   // 有理数の最大値
		sd.BufferDesc.RefreshRate.Denominator = 1;		   // 有理数の最小値
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;  // バックバッファーのサーフェス使用法およびCPUアクセスオプション
		sd.OutputWindow = window->getHWND();			   // 出力ウィンドウへのHWNDハンドル
		sd.SampleDesc.Count = 1;						   // ピクセル単位のマルチサンプリングの数
		sd.SampleDesc.Quality = 0;						   // イメージの品質レベル
		sd.Windowed = TRUE;								   // 出力がウィンドウモードの場合はTRUEそれ以外はFALSE


		for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
		{
			g_driverType = driverTypes[driverTypeIndex];
			hr = D3D11CreateDeviceAndSwapChain(
				nullptr,	       // 使用するビデオアダプターへのポインター（既定のものを使う場合NULL）
				g_driverType,	   // 使用するデバイスの種類
				nullptr,     	   // ソフトウェアラスタライザーを実装するDLLのハンドル
                0,				   // 有効にするランタイムレイヤー
				featureLevels,	   // D3D_FEATURE_LEVELの配列へのポインター
				numFeatureLevels,  // 上記配列の要素数
				D3D11_SDK_VERSION, // SDKのバージョン
				&sd,			   // DXGI_SWAP_CHAINへのポインター
				&swapChain,		   // IDXGISwapChainオブジェクトへのポインターのアドレスを返す
				&device,		   // ID3D11Deviceオブジェクトへのポインターのアドレスを返す
				&featureLevel,	   // D3D_FEATURE_LEVELへのポインターを返す
				&deviceContext	   // ID3D11DeviceContextオブジェクトへのポインターのアドレスを返す

			);

			if (SUCCEEDED(hr)) break;
		}
		if (FAILED(hr)) return hr;

		//TODO:make_sharedに
		// ポインターに対する処理
		spSwapChain     = std::shared_ptr<IDXGISwapChain>(swapChain, safeRelease<IDXGISwapChain>);
		spDevice        = std::shared_ptr<ID3D11Device>(device, safeRelease<ID3D11Device>);
		spDeviceContext = std::shared_ptr<ID3D11DeviceContext>(deviceContext, [](ID3D11DeviceContext *&ptr)
		{
			ptr->ClearState();
			safeRelease(ptr);
		});
      
        return S_OK;
	}

	// レンダーターゲットビューの作成
	HRESULT DirectX11::createRenderTargetView()
	{
		ID3D11Texture2D		   *backBuffer       = nullptr;
		ID3D11RenderTargetView *renderTargetView = nullptr;
        
        //TODO: 元々のコード
        // バックバッファの取得
		spSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*> (&backBuffer));
		// レンダーターゲットビューの作成
		auto hr = spDevice->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
		if (FAILED(hr)) {
            return E_FAIL;
		}
        
        IDXGISurface *surf;
        hr = spSwapChain->GetBuffer(0, IID_PPV_ARGS(&surf));
        if (FAILED(hr)) {
            return E_FAIL;
        }
        
        spRenderTargetView = std::shared_ptr<ID3D11RenderTargetView>(renderTargetView, safeRelease<ID3D11RenderTargetView>);
		safeRelease(backBuffer);
        
		return S_OK;
	}

	// レンダーターゲットビューの設定
	void DirectX11::setRenderTargetView()
	{		 
		auto renderTargetView = spRenderTargetView.get();
		spDeviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);

		// Viewportの初期化
		D3D11_VIEWPORT vp;
		vp.Width    = static_cast<FLOAT>(size.width);	 // ビューポート左側のX位置
		vp.Height   = static_cast<FLOAT>(size.height);   // ビューポート上側のY位置
		vp.MinDepth = 0.0f;								 // ビューポートの幅
		vp.MaxDepth = 1.0f;								 // ビューポートの高さ
		vp.TopLeftX = 0;								 // ビューポートの最小震度（0～1）
		vp.TopLeftY = 0;								 // ビューポートの最大深度（0～1）
		spDeviceContext->RSSetViewports(1, &vp);
	}
}