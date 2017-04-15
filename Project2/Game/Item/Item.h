//////////////////////////////////////////////////
// 作成日:2016/12/21
// 更新日:2016/12/21
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "..\Actor\Actor.h"

class Item : public Actor
{
public:
    Item();
    ~Item() override;

    bool init() override;
    void move() override;
    void draw() const override;
    void end()  override;

    void drop(const got::Vector2<float> &dropPos);

private:
    float dy;

};
