//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/10/1
// 制作者:got
//////////////////////////////////////////////////
#pragma once

#include"DirectX11.h"
#include"DirectXTex.h"
#include"Shader.h"
#include"Dimention.h"
#include"Matrix4x4.h"
#include"Color.h"
#include"Rectangle.h"

namespace got
{
	class Texture
	{
	public:
		Texture();
		~Texture();

		bool create(const std::wstring &path);
		void render(const Matrix4x4<float> & _matrix, const Color<float> & _color, const Rectangle<float> & rect);
		Dimention<int> getTextureSize() const;

	private:
		bool loadTexture(const std::wstring &path);
		bool createShaderResourceView();
		bool createVertexShaderAndInputLayout();
		bool createInputLayout(std::shared_ptr<ID3DBlob> &VSBlob);
		bool createPixelShader();
		bool createBuffer();
		bool createSamplerState();
		bool createBulendState();
		bool createConstantBuffer();

		struct  SimpleVertex
		{
			float Pos[3];
			float col[4];
			float uv[2];
		} vertices[4];

		struct ConstantBuffer
		{
			float matrix[16];
			float color[4];
			float rect[4];
			float vWidth;
			float vHeight;
			float tWidth;
			float tHeight;
		} cb;

		Dimention<int> textureSize;
		DirectX::TexMetadata metadata;
		DirectX::ScratchImage image;

		std::shared_ptr<ID3D11VertexShader>       spVertexShader;
		std::shared_ptr<ID3D11PixelShader>        spPixelShader;
		std::shared_ptr<ID3D11InputLayout>        spVertexLayout;
		std::shared_ptr<ID3D11Buffer>			  spVertexBuffer;
		std::shared_ptr<ID3D11ShaderResourceView> spTextureRV;
		std::shared_ptr<ID3D11SamplerState>		  spSamplerLinear;
		std::shared_ptr<ID3D11ShaderResourceView> spResourceView;
		std::shared_ptr<ID3D11BlendState>		  spBlendState;
		std::shared_ptr<ID3D11Buffer>			  spConstantBuffer;
	};
}