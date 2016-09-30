﻿//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/10/1
// 制作者:Got
//////////////////////////////////////////////////
#pragma once

#include"DirectX11.h"
#include"Shader.h"

namespace Got
{
	class Texture
	{
	public:
		Texture();
		~Texture();

		bool create();
		void render();

	private:
		bool loadTexture();
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
		} vertices[4];

		std::shared_ptr<ID3D11VertexShader>       spVertexShader;
		std::shared_ptr<ID3D11PixelShader>        spPixelShader;
		std::shared_ptr<ID3D11InputLayout>        spVertexLayout;
		std::shared_ptr<ID3D11Buffer>			  spVertexBuffer;
		std::shared_ptr<ID3D11ShaderResourceView> spTextureRV;
		std::shared_ptr<ID3D11SamplerState>		  spSamplerLinear;
	};
}