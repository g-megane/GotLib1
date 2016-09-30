//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/9/27
// 制作者:Got
//////////////////////////////////////////////////
#include "Texture.h"
#include <sstream>

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
	bool Texture::create()
	{
		ID3D11VertexShader *vertexShader = nullptr;
		ID3D11PixelShader  *pixelShader  = nullptr;
		ID3D11InputLayout  *vertexLayout = nullptr;
		ID3D11Buffer	   *vertexBuffer = nullptr;

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
		if (FAILED(hr)) {
			VSBlob->Release();
			return false;
		}

		// InputLayout
		D3D11_INPUT_ELEMENT_DESC layout[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		UINT numElements = ARRAYSIZE(layout);

		// Create InputLayout
		hr = DirectX11::getInstance().getDevice()->CreateInputLayout(
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

		// Compile PixelShader
		auto PSBlob = Shader::shaderCompile(L"PixelShader.hlsl", "main", "ps_5_0");
		if (VSBlob == nullptr) {
			MessageBox(NULL, L"PSコンパイル失敗", L"Error", MB_OK);
			return false;
		}

		// Create PixelShader
		hr = DirectX11::getInstance().getDevice()->CreatePixelShader(PSBlob->GetBufferPointer(), PSBlob->GetBufferSize(), NULL, &pixelShader);
		PSBlob->Release();
		if (FAILED(hr)) {
			return false;
		}

		// Create VertexBuffer
		vertices[0] = { -0.5f,  0.5f, 0.0f };
		vertices[1] = {  0.5f,  0.5f, 0.0f };
		vertices[2] = { -0.5f, -0.5f, 0.0f };
		vertices[3] = {  0.5f, -0.5f, 0.0f };

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage		  = D3D11_USAGE_DEFAULT;
		bd.ByteWidth	  = sizeof(SimpleVertex) * 4;
		bd.BindFlags	  = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags	  = 0;

		D3D11_SUBRESOURCE_DATA initData;
		ZeroMemory(&initData, sizeof(initData));
		initData.pSysMem = vertices;
		hr = DirectX11::getInstance().getDevice()->CreateBuffer(&bd, &initData, &vertexBuffer);
		if (FAILED(hr)) {
			return false;
		}

		// Set VertexBuffer
		UINT stride = sizeof(SimpleVertex);
		UINT offset = 0;
		DirectX11::getInstance().getDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

		// Set PrimitiveTopology
		DirectX11::getInstance().getDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		spVertexShader = std::shared_ptr<ID3D11VertexShader>(vertexShader, safeRelease<ID3D11VertexShader>);
		spPixelShader  = std::shared_ptr<ID3D11PixelShader> (pixelShader,  safeRelease<ID3D11PixelShader>);
		spVertexLayout = std::shared_ptr<ID3D11InputLayout> (vertexLayout, safeRelease<ID3D11InputLayout>);
		spVertexBuffer = std::shared_ptr<ID3D11Buffer>		(vertexBuffer, safeRelease<ID3D11Buffer>);

		return true;
	}

	// レンダリング
	void Texture::render()
	{
		auto textureRV	   = spTextureRV.get();
		auto samplerLinear = spSamplerLinear.get();
		auto &directX11    = DirectX11::getInstance();

		directX11.begineFrame();

		// シェーダーの登録
		directX11.getDeviceContext()->VSSetShader(spVertexShader.get(), nullptr, 0);
		directX11.getDeviceContext()->PSSetShader(spPixelShader.get(), nullptr, 0);

		directX11.getDeviceContext()->Draw(4, 0);
		directX11.endFrame();
	}

	bool Texture::loadTexture()
	{

		return true;
	}

	bool Texture::createShaderResourceView()
	{
		
		return true;
	}
}
