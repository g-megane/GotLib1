//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/10/1
// 制作者:got
//////////////////////////////////////////////////

#include "Shader.h"
#include <D3Dcompiler.h>
#pragma comment(lib, "D3Dcompiler.lib")

template<typename Ptr>
void safeRelease(Ptr *& ptr)
{
	if (ptr == nullptr) return;

	ptr->Release();
	ptr = nullptr;
}

namespace got
{
	Shader::Shader()
	{

	}

	Shader::~Shader()
	{
	}

	std::shared_ptr<ID3DBlob> Shader::shaderCompile(WCHAR *szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel)
	{
		ID3DBlob *ppBlobOut = nullptr;
		auto hr = S_OK;
		DWORD shaderFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
		//shaderFlags |= D3DCOMPILE_DEBUG;
#endif

		ID3DBlob *errorBlob = nullptr;

		hr = D3DCompileFromFile(
			szFileName,
			nullptr,
			nullptr,
			szEntryPoint,
			szShaderModel,
			shaderFlags,
			0,
			&ppBlobOut,
			&errorBlob);


		if (FAILED(hr)) {
			if (errorBlob != nullptr) {
				OutputDebugStringA(static_cast<char*>(errorBlob->GetBufferPointer()));
			}
			if (errorBlob) {
				errorBlob->Release();
			}
			return nullptr;
		}

		return std::shared_ptr<ID3DBlob>(ppBlobOut, safeRelease<ID3DBlob>);
	}
}
