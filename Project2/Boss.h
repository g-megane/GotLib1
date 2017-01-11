//////////////////////////////////////////////////
// 作成日:2016/12/19
// 更新日:2016/12/19
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

private:
    int	  hp;
    float dx;
    float dy;
    float bulletSpeed;
    float shotInterval;
    int   score;
};
