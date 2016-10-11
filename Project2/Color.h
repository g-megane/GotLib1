//////////////////////////////////////////////////
// 作成日:2016/10/5
// 更新日:2016/10/8
// 制作者:got
//////////////////////////////////////////////////
#pragma once

// カラークラス
namespace got
{
	template <class T>
	class Color
	{
	public:
		union
		{
			struct
			{
				T r;
				T g;
				T b;
				T a;
			};
			T rgba[4];
		};

		//	コンストラクタ
		Color(const T _r = static_cast<T>(1), const T _g = static_cast<T>(1), const T _b = static_cast<T>(1), const T _a = static_cast<T>(1))
			:r(_r), g(_g), b(_b), a(_a)
		{
		}
		// コピーコンストラクタ
		Color(const Color& other)
			:r(other.r), g(other.g), b(other.b), a(other.a)
		{
		}
		// デストラクタ
		~Color()
		{
		}

		// 演算子オーバーロード
		bool operator==(const Color& other) const
		{
			return (r == other.r) && (g == other.g) && (b == other.b) && (a == other.a);
		}
		bool operator!=(const Color& other) const
		{
			return !(*this == other);
		}

		// 定数
		static const Color WHITE;
		static const Color BLACK;
		static const Color RED;
		static const Color GREEN;
		static const Color BLUE;
	};

	template<class T>
	const Color<T> Color<T>::WHITE(static_cast<T>(1), static_cast<T>(1), static_cast<T>(1), static_cast<T>(1));
	template<class T>
	const Color<T> Color<T>::BLACK(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
	template<class T>
	const Color<T> Color<T>::RED  (static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
	template<class T>
	const Color<T> Color<T>::GREEN(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(1));
	template<class T>
	const Color<T> Color<T>::BLUE (static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(1));
}
