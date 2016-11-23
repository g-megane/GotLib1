//////////////////////////////////////////////////
// 作成日:2016/10/27
// 更新日:2016/11/23
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


	Enemy();
	~Enemy() override;

	bool init() override;
	void move() override;
	void draw() const override;
	void end() override;

	int getHp() const;
	void setDamage(const int damage);
    void setData(const int _hp, const float _initX, const float _initY, const int _movePattern, const float _dx, const float _dy, const int _shotPattern, const float _bulletSpeed, const float _shotInterval);

private:
	float dx;
	float dy;
	int	  hp;
    float bulletSpeed;
    float shotInterval;
    float dTime;
	got::Time time;
	got::Time time2;
	std::shared_ptr<EnemyBulletManager> enemyBulletManager;

    std::function<void()> Enemy::moveFunc;
    std::function<void()> Enemy::shotFunc;  

    void setMovePattern(const int pattern);
    void setShotPattern(const int pattern);
	got::Vector2<float> getShotPosition() const;

};