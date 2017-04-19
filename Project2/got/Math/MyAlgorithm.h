//////////////////////////////////////////////////
// �쐬��:2017/4/18
// �X�V��:2017/4/18
// �����:got
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

        // ����value_������min_�`����max_�͈̔͂ɐ�������
        template <class T>
        static T clamp(const T value_, const T max_, const T min_)
        {
            return std::min(std::max(min_, value_), max_);
        }
        // ����value_��limit�ȏ�̏ꍇvalue_��0�ɁA�܂�0�ȉ��̏ꍇvalue_��limit_��
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
