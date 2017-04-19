//////////////////////////////////////////////////
// ì¬“ú:2017/4/18
// XV“ú:2017/4/18
// §ìÒ:got
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

        // ˆø”value_‚ğˆø”min_`ˆø”max_‚Ì”ÍˆÍ‚É§ŒÀ‚·‚é
        template <class T>
        static T clamp(const T value_, const T max_, const T min_)
        {
            return std::min(std::max(min_, value_), max_);
        }
        // ˆø”value_‚ªlimitˆÈã‚Ìê‡value_‚ğ0‚ÉA‚Ü‚½0ˆÈ‰º‚Ìê‡value_‚ğlimit_‚É
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
