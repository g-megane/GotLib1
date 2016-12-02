//////////////////////////////////////////////////
// 作成日:2016/12/2
// 更新日:2016/12/2
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Color.h"

class Fade
{
public:
    Fade();
    ~Fade();

    bool fadeIn();
    bool fadeOut();

private:
    got::Color<float> color;

};