//////////////////////////////////////////////////
// 作成日:2016/10/27
// 更新日:2016/10/27
// 制作者:got
//////////////////////////////////////////////////
#pragma once

#include <functional>
#include "Actor.h"
#include "Time.h"
#include "EnemyBulletManager.h"
#include "Sprite.h"

class Enemy : public Actor
{
public:
	Enemy(const int hp);
	~Enemy() override;

	bool init() override;
	void move() override;
	void draw() const override;
	void end() override;

	int getHp() const;
	void setDamage(const int damage);

private:
	float dx;
	float dy;
	int	  hp;
	got::Time time;
	got::Time time2;
	std::shared_ptr<EnemyBulletManager> enemyBulletManager;
    std::shared_ptr<Player> player;

    //std::function<void()> Enemy::moveFunc;
    void (Enemy::*moveFunc)();
    void move1();
    void move2();
    void move3();

	got::Vector2<float>  getShotPosition() const;

};