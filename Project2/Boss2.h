//////////////////////////////////////////////////
// 作成日:2016/1/30
// 更新日:2016/1/30
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Boss.h"

class Boss2 : public Boss
{
public:
    Boss2();
    ~Boss2() override;

    bool init() override;
    void move() override;
    void draw() const override;
    void end()  override;
    void setDamage(const int damage) override;

private:
    void changeMove() override;
    void checkMoveLimit();

    got::Time subShotTimer;

};
