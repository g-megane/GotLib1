//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/10/1
// 制作者:Got
//////////////////////////////////////////////////
#include "Texture.h"
#include <sstream>

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
		spVertexShader  = nullptr;
		spPixelShader   = nullptr;
		spVertexLayout  = nullptr;
		spVertexBuffer  = nullptr;
		spTextureRV		= nullptr;
		spSamplerLinear = nullptr;
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
	bool Texture::create(/*TODO:loadTexture()に渡す画像の名前*/)
	{
		if (!loadTexture(/*TODO:画像の名前を引数に*/)) { return false; }
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

	bool Texture::loadTexture()
	{
		// Create VertexBuffer
		vertices[0] = { -0.5f,  0.5f, 0.0f };
		vertices[1] = { 0.5f,  0.5f, 0.0f };
		vertices[2] = { -0.5f, -0.5f, 0.0f };
		vertices[3] = { 0.5f, -0.5f, 0.0f };

		return true;
	}

	bool Texture::createShaderResourceView()
	{
			
		return true;
	}
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
		return true;
	}
	bool Texture::createBulendState()
	{
		return true;
	}
	bool Texture::createConstantBuffer()
	{
		return true;
	}
}
