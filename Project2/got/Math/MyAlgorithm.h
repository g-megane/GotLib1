//////////////////////////////////////////////////
// 作成日:2017/4/18
// 更新日:2017/4/18
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include <algorithm>
#undef max
#undef min

namespace got
{
    class MyAlgorithm
    {
    public:
        MyAlgorithm() = delete;

        // 引数value_を引数min_〜引数max_の範囲に制限する
        template <class T>
        static T clamp(const T value_, const T max_, const T min_)
        {
            return std::min(std::max(min_, value_), max_);
        }
        // 引数value_がlimit以上の場合value_を0に、また0以下の場合value_をlimit_に
        template <class T>
        static T rollup(const T value_, const T limit_) {
            if (value_ < 0) {
                return limit_;
            }
            else if (value_ > limit_){
                return 0;
            }
            return value_;
        }
    };
}
