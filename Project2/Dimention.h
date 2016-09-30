//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/9/27
// 制作者:Got
//////////////////////////////////////////////////
#pragma once

// 
namespace Got
{
	template<class T>
	class Dimention
	{
	public:
		Dimention(const Dimention<T> &other)
		{
			this->width = other.width;
			this->height = other.height;
		}
		Dimention(const T &_width = static_cast<T>(0), const T &_height = static_cast<T>(0))
			:width(_width), height(_height)
		{
		}
		~Dimention()
		{
		}

		T width;
		T height;
	};
}
