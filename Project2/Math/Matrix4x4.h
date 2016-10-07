//////////////////////////////////////////////////
// 作成日:2016/10/5
// 更新日:2016/10/7
// 制作者:Got
//////////////////////////////////////////////////
#pragma once
#include<cmath>
#include"Vector2.h"

// 4x4の行列クラス(2D用)
namespace Got
{
	template <class T>
	class Matrix4x4
	{
	public:
		union
		{
			struct
			{
				T m11; T m12; T m13; T m14;
				T m21; T m22; T m23; T m24;
				T m31; T m32; T m33; T m34;
				T m41; T m42; T m43; T m44;
			};
			T mat4x4[4][4];
			T mat16[16];
		};

		// コピーコンストラクタ
		Matrix4x4(const Matrix4x4 &other)
			:m11(other.m11), m12(other.m12), m13(other.m13), m14(other.m14),
			 m21(other.m21), m22(other.m22), m23(other.m23), m24(other.m24),
			 m31(other.m31), m32(other.m32), m33(other.m33), m34(other.m34),
			 m41(other.m41), m42(other.m42), m43(other.m43), m44(other.m44)
		{
		}
		// コンストラクタ
		Matrix4x4(
			const T& _m11 = static_cast<T>(1), const T& _m12 = static_cast<T>(0), const T& _m13 = static_cast<T>(0), const T& _m14 = static_cast<T>(0),
			const T& _m21 = static_cast<T>(0), const T& _m22 = static_cast<T>(1), const T& _m23 = static_cast<T>(0), const T& _m24 = static_cast<T>(0),
			const T& _m31 = static_cast<T>(0), const T& _m32 = static_cast<T>(0), const T& _m33 = static_cast<T>(1), const T& _m34 = static_cast<T>(0),
			const T& _m41 = static_cast<T>(0), const T& _m42 = static_cast<T>(0), const T& _m43 = static_cast<T>(0), const T& _m44 = static_cast<T>(1)
		):
			m11(_m11), m12(_m12), m13(_m13), m14(_m14),
			m21(_m21), m22(_m22), m23(_m23), m24(_m24),
			m31(_m31), m32(_m32), m33(_m33), m34(_m34),
			m41(_m41), m42(_m42), m43(_m43), m44(_m44)
		{

		}
		
		// 平行移動
		template<class U>
		static Matrix4x4 translate(const Vector2<U>& vec)
		{
			Matrix4x4 tmp;
			tmp.m41 = static_cast<T>(vec.x);
			tmp.m42 = static_cast<T>(vec.y);
			return tmp;
		}
		template<class U>
		static Matrix4x4 translate(const U& x, const U& y, const U& z = static_cast<U>(1))
		{
			Matrix4x4 tmp;
			tmp.m41 = static_cast<T>(x);
			tmp.m42 = static_cast<T>(y);
			tmp.m43 = static_cast<T>(z);
			return tmp;
		}
		// 回転(X)
		template<class U>
		static Matrix4x4 rotateX(const U& angle)
		{
			Matrix4x4 tmp;
			tmp.m22 =  std::cos(static_cast<T>(angle));
			tmp.m23 =  std::sin(static_cast<T>(angle));
			tmp.m32 = -std::sin(static_cast<T>(angle));
			tmp.m33 =  std::cos(static_cast<T>(angle));
			return tmp;
		}
		// 回転(Y)
		template<class U>
		static Matrix4x4 rotateY(const U& angle)
		{
			Matrix4x4 tmp;
			tmp.m11 =  std::cos(static_cast<T>(angle));
			tmp.m13 = -std::sin(static_cast<T>(angle));
			tmp.m13 =  std::sin(static_cast<T>(angle));
			tmp.m33 =  std::cos(static_cast<T>(angle));
			return tmp;
		}
		// 回転(Z)
		template<class U>
		static Matrix4x4 rotateZ(const U& angle)
		{
			Matrix4x4 tmp;
			tmp.m11 =  std::cos(static_cast<T>(angle));
			tmp.m12 =  std::sin(static_cast<T>(angle));
			tmp.m21 = -std::sin(static_cast<T>(angle));
			tmp.m22 =  std::cos(static_cast<T>(angle));
			return tmp;
		}
		// 拡大縮小
		template<class U>
		static Matrix4x4 scale(const U& scale)
		{
			Matrix4x4 tmp;
			tmp.m11 = scale;
			tmp.m22 = scale;
			return tmp;
		}
		template<class U>
		static Matrix4x4 scale(const U& x, const U& y)
		{
			Matrix4x4 tmp;
			tmp.m11 = x;
			tmp.m22 = y;
			return tmp;
		}
	};
}