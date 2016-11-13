//////////////////////////////////////////////////
// 作成日:2016/11/9
// 更新日:2016/11/9
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Matrix4x4.h"
#include "Color.h"
#include "Rectangle.h"
#include "Vector2.h"

class BackGround
{
public:
    BackGround();
    ~BackGround();

    bool init();
    void move();
    void draw() const;
    void end();

private:
   float dx;
   float dy;
   got::Vector2<float> position;

};
