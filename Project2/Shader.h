//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/10/1
// 制作者:got
//////////////////////////////////////////////////
#pragma once

#include<d3d11.h>
#include<Windows.h>
#include<memory>

namespace got
{
	class Shader
	{
	public:
		Shader();
		~Shader();

		/* Comment
		 * 戻り値を "ID3DBlob*" に設定し引数の ID3DBlob を削除
		 * 失敗した場合は nullptr を返す
		 */
		static std::shared_ptr<ID3DBlob> shaderCompile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel);
	};
}
