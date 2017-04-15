//////////////////////////////////////////////////
// 作成日:2016/12/27
// 更新日:2016/12/27
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Effect.h"

class Explosion : public Effect
{
public:
    Explosion(std::string name);
    ~Explosion() override;

    bool init() override;
    void move() override;
    void draw() const override;
    void end()  override;

    void startEffect(const got::Vector2<float>& effectPos) override;

private:
    float scale;
    float dy;

};