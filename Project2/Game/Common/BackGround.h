//////////////////////////////////////////////////
// 作成日:2016/11/9
// 更新日:2016/11/9
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include <string>
#include "..\..\got\Math\Matrix4x4.h"
#include "..\..\got\Utility\Color.h"
#include "..\..\got\Math\Vector2.h"

class BackGround
{
public:
    BackGround(const std::string& _spriteName);
    ~BackGround();

    bool init();
    void move();
    void draw() const;
    void end();

private:
   float dx;
   float dy;
   got::Vector2<float> position;
   std::string spriteName;
   got::Color<float> color;

};
