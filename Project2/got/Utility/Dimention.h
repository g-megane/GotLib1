//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/9/27
// 制作者:got
//////////////////////////////////////////////////
#pragma once

// 
namespace got
{
	template<class T>
	class Dimention
	{
	public:
		// コピーコンストラクタ
		Dimention(const Dimention<T> &other)
		{
			width  = other.width;
			height = other.height;
		}
		// コンストラクタ
		Dimention(const T &_width = static_cast<T>(0), const T &_height = static_cast<T>(0))
			:width(_width), height(_height)
		{
		}
		// デストラクタ
		~Dimention()
		{
		}
		// 中央を求める
		Dimention & getCenter() const
		{
			return Dimention(width / 2, height / 2);
		}
		//Dimention & operator=(const Dimention<T>& other) {
		//	width  = other.width;
		//	height = other.height;
		//	return *this;
		//}

		T width;
		T height;
	};
}
