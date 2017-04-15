//////////////////////////////////////////////////
// 作成日:2016/10/12
// 更新日:2016/10/12
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include<memory>
#include<string>

#include"..\..\got\Math\Matrix4x4.h"
#include"Dimention.h"
#include"Texture.h"

namespace got
{
	class Sprite
	{
	public:
		Sprite(const std::wstring& path = L"");
		bool create(const std::wstring& path);
		Dimention<int> getSize() const;

		template<class T = float>
		void draw(const Matrix4x4<T>& matrix, const Rectangle<int>& rect, const Color<T>& color)
		{
			//auto x = Color<T>::WHITE;
			texture->render(matrix, rect, color);
		}

	private:
		Dimention<int> size;
		std::shared_ptr<Texture> texture;
	};
}