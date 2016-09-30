//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/10/1
// 制作者:Got
//////////////////////////////////////////////////
#include <sstream>
#include "Texture.h"

template<typename Ptr>
void safeRelease(Ptr *& ptr)
{
	if (ptr == nullptr) return;

	ptr->Release();
	ptr = nullptr;
}

namespace Got
{
	// コンストラクタ
	Texture::Texture()
	{
		spVertexShader	 = nullptr;
		spPixelShader	 = nullptr;
		spVertexLayout	 = nullptr;
		spVertexBuffer	 = nullptr;
		spTextureRV		 = nullptr;
		spSamplerLinear  = nullptr;
		spResourceView   = nullptr;
		spBlendState	 = nullptr;
		spConstantBuffer = nullptr;
	}
	// デストラクタ
	Texture::~Texture()
	{
	}

	/* Comment
	 * shaderCompile を "ShaderTest.fx" から "ComputeShader.hlsl" と "PixelShader.hlsl" に変更
	 * shaderCompile の EntryPoint を "VS", "PS" から "main"に変更
	 * VBlob を shaderCompile の戻り値に設定
	 * 戻り値がbool型のため "return hr" を 失敗した場合 "return false"に変更
	 */

	//
	bool Texture::create(const std::wstring &path)
	{
		if (!loadTexture(path)) { return false; }
		if (!createShaderResourceView())			{ return false; }
		if (!createVertexShaderAndInputLayout())	{ return false; }
		if (!createPixelShader())					{ return false; }
		if (!createBuffer())						{ return false; }
		if (!createSamplerState())					{ return false; }
		if (!createBulendState())					{ return false; }
		if (!createConstantBuffer())				{ return false; }

		return true;
	}

	// レンダリング
	void Texture::render()
	{
		// Set VertexBuffer
		UINT stride = sizeof(SimpleVertex);
		UINT offset = 0;

		auto vertexBuffer = spVertexBuffer.get();
		//auto samplerLinear = spSamplerLinear.get();
		//auto textureRV	   = spTextureRV.get();
		//auto samplerLinear = spSamplerLinear.get();
		auto &directX11    = DirectX11::getInstance();

		directX11.begineFrame();
		DirectX11::getInstance().getDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

		directX11.getDeviceContext()->VSSetShader(spVertexShader.get(), nullptr, 0);
		DirectX11::getInstance().getDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		
		directX11.getDeviceContext()->PSSetShader(spPixelShader.get(), nullptr, 0);

		directX11.getDeviceContext()->Draw(4, 0);
		directX11.endFrame();
	}
	// テクスチャのサイズを取得
	Dimention<int> Texture::getTextureSize() const
	{
		return textureSize;
	}
	// テクスチャの読み込み
	bool Texture::loadTexture(const std::wstring &path)
	{
		DirectX::LoadFromWICFile(path.c_str(), 0, &metadata, image);

		textureSize = Dimention<int>(static_cast<int>(image.GetImages()->width), static_cast<int>(image.GetImages()->height));

		// Create VertexBuffer
		vertices[0] = { -0.5f,  0.5f, 0.0f };
		vertices[1] = {  0.5f,  0.5f, 0.0f };
		vertices[2] = { -0.5f, -0.5f, 0.0f };
		vertices[3] = {  0.5f, -0.5f, 0.0f };

		return true;
	}
	//
	bool Texture::createShaderResourceView()
	{
		ID3D11ShaderResourceView *resourceView = nullptr;

		DirectX::CreateShaderResourceView(DirectX11::getInstance().getDevice().get(), image.GetImages(), image.GetImageCount(), metadata, &resourceView);

		spResourceView = std::shared_ptr<ID3D11ShaderResourceView>(resourceView, safeRelease<ID3D11ShaderResourceView>);

		return true;
	}
	//
	bool Texture::createVertexShaderAndInputLayout()
	{
		ID3D11VertexShader *vertexShader = nullptr;

		// Compile VertexShader
		auto VSBlob = Shader::shaderCompile(L"ComputeShader.hlsl", "main", "vs_5_0");
		std::basic_ostringstream<wchar_t> oss;

		if (VSBlob == nullptr) {
			oss << L"VSのコンパイル失敗 : ";
			MessageBox(NULL, oss.str().c_str(), L"Error", MB_OK);
			return false;
		}

		// Create VertexShader
		auto hr = DirectX11::getInstance().getDevice()->CreateVertexShader(VSBlob->GetBufferPointer(), VSBlob->GetBufferSize(), nullptr, &vertexShader);
		spVertexShader = std::shared_ptr<ID3D11VertexShader>(vertexShader, safeRelease<ID3D11VertexShader>);
		if (FAILED(hr)) {
			VSBlob->Release();
			return false;
		}

		return createInputLayout(VSBlob);
	}
	//
	bool Texture::createInputLayout(std::shared_ptr<ID3DBlob> &VSBlob)
	{
		ID3D11InputLayout  *vertexLayout = nullptr;

		// InputLayout
		D3D11_INPUT_ELEMENT_DESC layout[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		UINT numElements = ARRAYSIZE(layout);

		// Create InputLayout
		auto hr = DirectX11::getInstance().getDevice()->CreateInputLayout(
			layout,
			numElements,
			VSBlob->GetBufferPointer(),
			VSBlob->GetBufferSize(),
			&vertexLayout
		);
		VSBlob->Release();
		if (FAILED(hr)) {
			return false;
		}

		// Set InputLayout
		DirectX11::getInstance().getDeviceContext()->IASetInputLayout(vertexLayout);

		spVertexLayout = std::shared_ptr<ID3D11InputLayout>(vertexLayout, safeRelease<ID3D11InputLayout>);


		return true;
	}
	bool Texture::createPixelShader()
	{
		ID3D11PixelShader  *pixelShader = nullptr;

		// Compile PixelShader
		auto PSBlob = Shader::shaderCompile(L"PixelShader.hlsl", "main", "ps_5_0");
		if (PSBlob == nullptr) {
			MessageBox(NULL, L"PSコンパイル失敗", L"Error", MB_OK);
			return false;
		}

		// Create PixelShader
		auto hr = DirectX11::getInstance().getDevice()->CreatePixelShader(PSBlob->GetBufferPointer(), PSBlob->GetBufferSize(), NULL, &pixelShader);
		spPixelShader = std::shared_ptr<ID3D11PixelShader>(pixelShader, safeRelease<ID3D11PixelShader>);
		PSBlob->Release();
		if (FAILED(hr)) {
			return false;
		}

		return true;
	}
	bool Texture::createBuffer()
	{
		ID3D11Buffer *vertexBuffer = nullptr;

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(SimpleVertex) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		ZeroMemory(&initData, sizeof(initData));
		initData.pSysMem = vertices;
		auto hr = DirectX11::getInstance().getDevice()->CreateBuffer(&bd, &initData, &vertexBuffer);
		spVertexBuffer = std::shared_ptr<ID3D11Buffer>(vertexBuffer, safeRelease<ID3D11Buffer>);
		if (FAILED(hr)) {
			return false;
		}

		return true;
	}
	bool Texture::createSamplerState()
	{
		ID3D11SamplerState *samplerLinear = nullptr;

		D3D11_SAMPLER_DESC samplerDesc;
		ZeroMemory(&samplerDesc, sizeof(samplerDesc));
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		auto hr = DirectX11::getInstance().getDevice()->CreateSamplerState(&samplerDesc, &samplerLinear);
		spSamplerLinear = std::shared_ptr<ID3D11SamplerState>(samplerLinear, safeRelease<ID3D11SamplerState>);
		if (FAILED(hr)) {
			return false;
		}

		return true;
	}
	//
	bool Texture::createBulendState()
	{
		ID3D11BlendState *blendState = nullptr;

		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(blendDesc));
		blendDesc.AlphaToCoverageEnable					= false;
		blendDesc.IndependentBlendEnable				= false;
		blendDesc.RenderTarget[0].BlendEnable			= true;
		blendDesc.RenderTarget[0].SrcBlend				= D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend				= D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOp				= D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha			= D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha		= D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha		    = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		DirectX11::getInstance().getDevice()->CreateBlendState(&blendDesc, &blendState);
		spBlendState = std::shared_ptr<ID3D11BlendState>(blendState, safeRelease<ID3D11BlendState>);

		DirectX11::getInstance().getDeviceContext()->OMSetBlendState(blendState, blendFactor, 0xffffffff);
		return true;
	}
	//
	bool Texture::createConstantBuffer()
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage		  = D3D11_USAGE_DEFAULT;
		bd.ByteWidth	  = sizeof(ConstantBuffer);
		bd.BindFlags	  = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;

		ID3D11Buffer *bufferaa;
		DirectX11::getInstance().getDevice()->CreateBuffer(&bd, nullptr, &bufferaa);

		spConstantBuffer = std::shared_ptr<ID3D11Buffer>(bufferaa, safeRelease<ID3D11Buffer>);

		return true;
	}
}
