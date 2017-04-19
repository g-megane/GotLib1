//////////////////////////////////////////////////
// 作成日:2016/10/5
// 更新日:2016/11/23
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include<cmath>
#include"..\..\Game\Common\GV.h"

namespace got
{
	// 角度計算クラス
	class Angle
	{
	public:
        Angle() = delete;
		// 弧度法に変換
        template <class T>
		static T toRadian(const T angle)
		{
			return angle * static_cast<T>(PI / 180);
		}
		// 度数法に変換
        template <class T>
		static T toDegree(const T rad)
		{
			return rad * static_cast<T>(180 / PI);
		}
	};
}
