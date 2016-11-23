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

	int  getHp() const;
	void setDamage(const int damage);
    void setData(const int          _hp,
                 const std::string& _spriteName,
                 const float        _initX, 
                 const float        _initY, 
                 const int          _movePattern, 
                 const float        _dx, 
                 const float        _dy, 
                 const int          _shotPattern, 
                 const float        _bulletSpeed, 
                 const float        _shotInterval, 
                 const int          _score);

private:
	int	  hp;
    std::string spriteName;
	float dx;
	float dy;
    float bulletSpeed;
    float shotInterval;
    int   score;
	got::Time time;
	got::Time time2;

    float dTime;
	std::shared_ptr<EnemyBulletManager> enemyBulletManager;

    std::function<void()> Enemy::moveFunc;
    std::function<void()> Enemy::shotFunc;  

    void setMovePattern(const int pattern);
    void setShotPattern(const int pattern);
	got::Vector2<float> getShotPosition() const;

};