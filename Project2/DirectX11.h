//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/10/1
// 制作者:got
//////////////////////////////////////////////////
#pragma once

#include <d3d11.h>
#include"Singleton.h"
#include"Dimention.h"

// DirectX11の制御クラス
namespace got
{
	class Window;
	class DirectX11 : public Singleton<DirectX11>
	{
	public:
		~DirectX11();

		void DirectX11::initialize(std::shared_ptr<Window> _window);

		void begineFrame() const;
		void endFrame() const;
		
		std::shared_ptr<ID3D11Device> getDevice() const;
		std::shared_ptr<ID3D11DeviceContext> getDeviceContext() const;
		std::shared_ptr<Window> getWindow() const;
		Dimention<int> getSize() const;
		bool isInit() const;

	private:
		DirectX11();
		friend class Singleton<DirectX11>;

		HRESULT DirectX11::createDeviceAndSwapChain();
		HRESULT createRenderTargetView();
		void setRenderTargetView();

		std::shared_ptr<Window>					window;
		std::shared_ptr<ID3D11Device>			spDevice;
		std::shared_ptr<ID3D11DeviceContext>	spDeviceContext;
		std::shared_ptr<IDXGISwapChain>			spSwapChain;
		std::shared_ptr<ID3D11RenderTargetView> spRenderTargetView;
		D3D_FEATURE_LEVEL featureLevel;
		D3D_DRIVER_TYPE   g_driverType;

		Dimention<int> size;
		bool init;
	};
}
