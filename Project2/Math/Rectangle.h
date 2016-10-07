//////////////////////////////////////////////////
// 作成日:2016/10/5
// 更新日:2016/10/5
// 制作者:Got
//////////////////////////////////////////////////
#pragma once
#include"Vector2.h"

namespace Got
{
	template <class T>
	class Rectangle
	{
	public:
		// デフォルトコンストラクタ
		Rectangle()
			: topLeft(Vector2<T>())
			, bottomRight(Vector2<T>())
		{
		}
		// コピーコンストラクタ
		Rectangle(const Rectangle &other)
		{
			topleft		= other.topleft;
			bottomRight = other.bottomRight;
		}
		// デストラクタ
		~Rectangle()
		{
		}
		// 引数：（左上隅、画像の幅、画像の高さ）
		Rectangle(const Vector2<T> & vec2, const T picWidth, const T picHeight)
			: topLeft(vec2)
		{
			bottomRight.x = vec2.x + picWidth;
			bottomRight.y = vec2.y + picHeight;
		}

		// 引数：（左上隅、右下隅）
		explicit Rectangle(const Vector2<T> & _min, const Vector2<T> & _max)
		{
			set(_min, _max);
		}
		// 引数：（右下隅）
		explicit Rectangle(const Vector2<T> & _max)
		{
			set(Vector2D<T>(), _max);
		}
		// 指定された幅と高さに変更
		Rectangle & setSize(const T width, const T height) {
			bottomRight.x = topLeft.x + width;
			bottomRight.y = topLeft.y + height;
			return *this;
		}
		// 指定された大きさに変更
		// 引数：（左上隅、右下隅）
		void set(const Vector2<T> & _min, const Vector2<T> & _max) {
			topLeft = _min;
			bottomRight = _max;
		}
		// 
		Rectangle  & translate(const Vector2<T> & vec) {
			topLeft.translate(vec);
			bottomRight.translate(vec);
			return *this;
		}
		//
		Rectangle & move(const Vector2<T> & vec) {
			topLeft = vec;
			bottomRight = bottomRight.translate(vec);
			return *this;
		}
		// 指定された短形と交差するか
		bool Intersection(const Rectangle & other) const {
			return topLeft.x < other.bottomRight.x && topLeft.y < other.bottomRight.y && other.topLeft.x < bottomRight.x && other.topLeft.y < bottomRight.y;
		}
		// 長方形の幅を取得
		T getWidth() const {
			return bottomRight.x - topLeft.x;
		}
		// 長方形の高さを取得
		T getHeight() const {
			return bottomRight.y - topLeft.y;
		}
		// 左上隅座標を取得
		Vector2<T> getTopLeft() const {
			return topLeft;
		}
		// 右下隅を取得
		Vector2<T> getBottomRight() const {
			return bottomRight;
		}

		Rectangle & operator=(const Rectangle& other) {
			topLeft = other.topLeft;
			bottomRight = other.bottomRight;
			return *this;
		}

	private:
		Vector2<T> topleft;     // 左上隅
		Vector2<T> bottomRight;	// 右下隅
	};
}