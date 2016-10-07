//////////////////////////////////////////////////
// 作成日:2016/10/5
// 更新日:2016/10/5
// 制作者:Got
//////////////////////////////////////////////////
#pragma once
#include<cmath>
#include"GV.h"

namespace Got
{
	// 角度計算クラス
	template <class T>
	class Angle
	{
	public:
		// 弧度法に変換
		static T toRadian(const T angle)
		{
			return angle * static_cast<T>(PI / 180);
		}
		// 度数法に変換
		static T toDegree(const T rad)
		{
			return rad * static_cast<T>(180 / PI);
		}
	};
}
