//////////////////////////////////////////////////
// 作成日:2016/10/5
// 更新日:2016/10/5
// 制作者:Got
//////////////////////////////////////////////////
#pragma once
#include<cmath>
#include<cfloat>
#include"Angle.h"

// 2Dベクトルクラス
namespace Got
{
	template <class T>
	class Vector2
	{
	public:
		// デフォルトコンストラクタ
		Vector2() : x(T()), y(T())
		{
		}
		// コピーコンストラクタ
		Vector2(const Vector2 &other)
		{
			x = other.x;
			y = other.y;
		}
		// デストラクタ
		~Vector2()
		{

		}
		// コンストラクタ
		explicit Vector2(const T _x, const T _y)
		{
			x = _x;
			y = _y;
		}

		// 指定された座標に移動させる
		void move(const T _x, const T _y)
		{
			x = _x;
			y = _y;
		}
		// 座標を引数分ずらす
		Vector2 & translate(const Vector2 &vec)
		{
			x += vec.x;
			y += vec.y;
			return *this;
		}
		Vector2 & translate(const T _x, const T _y)
		{
			x += _x;
			y += _y;
			return *this;
		}
		// 内積を求める
		T dot(const Vector2 &other) const
		{
			return (x * other.x) + (y * other.y);
		}
		// 外積を求める
		T cross(const Vector2 &other) const
		{
			return (x * other.y) - (y * other.x);
		}
		// 長さを求める
		T length() const
		{
			return std::sqrt(dot(*this));
		}
		// 距離を求める
		T distance(const Vector2 &other) const
		{
			return  (*this - other).length();
		}
		// 正規化する
		Vector2 normalize() const
		{
			const float len = length();
			if (len < FLT_EPSILON) {
				return Vector2
			}
		}
		// ゼロベクトルか？
		bool isZero() const
		{
			return *this == Vector2::ZERO;
		}
		// 角度からベクトルを作成
		static Vector2 fromAngle(T degree)
		{
			const float rad = Angle<T>::toRadian(degree); // 弧度法に変換
			return Vector2(std::cos(rad), std::sin(rad));
		}
		// ベクトルが向いている角度を求める
		T toAngle() const
		{
			if (isZero()) return static_cast<T>(0); // ゼロベクトルは角度を求められない
			return Vector2(std::atan2(y, x)); // 度数法に変換
		}
		// 回転
		Vector2 rotate(T degree) const
		{
			const float rad = Angle<T>::toRadian(degree); // 弧度法に変換
			return Vector2(x * std::cos(rad) - y * std::sin(rad),
						   x * std::sin(rad) + y * std::cos(rad));
		}

		// 演算子オーバーロード
		Vector2 & operator+=(const Vector2 &other)
		{
			return *this = *this + other;
		}
		Vector2 & operator-=(const Vector2 &other)
		{
			return *this = *this - other;
		}
		Vector2 & operator*=(const T scalar)
		{
			return *this = *this * other;
		}
		Vector2 & operator/=(const T scalar)
		{
			return *this = *this / other;
		}
		const Vector2 operator+(const Vector2 &other) const
		{
			return Vector2(x + other.x, y + other.y);
		}
		const Vector2 operator-(const Vector2 &other) const
		{
			return Vector2(x - other.x, y - other.y);
		}
		const Vector2 operator*(const T scalar) const
		{
			return Vector2(x * scalar, y * scalar);
		}
		const Vector2 operator/(const T scalar) const
		{
			return Vector2(x / scalar, y / scalar);
		}
		const Vector2 operator-() const
		{
			return Vector2(-x, -y);
		}
		bool operator==(const Vector2 &other) const
		{
			return (x == other.x) && (y == other.y);
		}
		bool operator!=(const Vector2 &other) const
		{
			return !(*this == other);
		}
		bool operator<(const Vector2 &other) const
		{
			if (x < other.x) return true;
			if (y < other.y) return true;
			return false;
		}
		Vector2 & operator=(const Vector2 &other) const
		{
			if (this != &other) {
				x = other.x;
				y = other.y;
			}
			return *this;
		}

		// 定数
		static constexpr Vector2 ZERO;	// ゼロベクトル
		static constexpr Vector2 LEFT;	// 左
		static constexpr Vector2 RIGHT; // 右
		static constexpr Vector2 DOWN;	// 下
		static constexpr Vector2 UP		// 上

	public:
		T x; // X座標
		T y; // y座標
	};

	template<class T>
	const Vector2<T>::ZERO( static_cast<T>(0),  static_cast(0));
	template<class T>
	const Vector2<T>::LEFT( static_cast<T>(-1), static_cast(0));
	template<class T>
	const Vector2<T>::RIGHT(static_cast<T>(1),  static_cast(0));
	template<class T>
	const Vector2<T>::DOWN( static_cast<T>(0),  static_cast(-1));
	template<class T>
	const Vector2<T>::ZERO( static_cast<T>(0),  static_cast(1));
}
