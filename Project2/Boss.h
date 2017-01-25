//////////////////////////////////////////////////
// 作成日:2016/12/19
// 更新日:2016/1/25
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Enemy.h"

class Boss : public Enemy
{
public:
    Boss();
    ~Boss() override;

    bool init() override;
    void move() override;
    void draw() const override;
    void end()  override;
    void setDamage(const int damage) override;

private:
    virtual void changeMove();
    void checkMoveLimit();

    got::Time subShotTimer;

};
