﻿//////////////////////////////////////////////////
// 作成日:2016/11/23
// 更新日:2016/11/23
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Vector2.h"

namespace got
{
    class Collison 
    {
    public:
        Collison() = delete;

        // 円と円のあたり判定
        template<typename T>
        static bool citcleToClircle(got::Vector2<T> vec1, T _rad1, got::Vector2<T> vec2, T _rad2)
        {
            return (vec2.x - vec1.x) * (vec2.x - vec1.x) + (vec2.y - vec1.y) * (vec2.y - vec1.y) < (_rad1 + _rad2) * (_rad1 + _rad2);
        }
    };
}