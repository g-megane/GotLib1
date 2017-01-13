//////////////////////////////////////////////////
// 作成日:2016/10/27
// 更新日:2016/12/19
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

	const int  getHp() const;
	void setDamage(const int damage);
    void setData(const int          _hp,
                 const got::Color<float> _color,
                 const std::string& _spriteName,
                 const float        _initX, 
                 const float        _initY, 
                 const int          _movePattern, 
                 const float        _dx, 
                 const float        _dy, 
                 const int          _shotPattern, 
                 const float        _bulletSpeed, 
                 const float        _shotInterval, 
                 const int          _score,
                 const bool         _isBoss
        );
    const bool getIsBoss() const;

protected:
	int	  hp;
	float dx;
	float dy;
    float bulletSpeed;
    float shotInterval;
    int   score;
    bool  isBoss;
    got::Color<float> color;
	got::Time time;
	got::Time time2;
    got::Time time3;

    float dTime;
	std::shared_ptr<EnemyBulletManager> enemyBulletManager;

    std::function<void()> Enemy::moveFunc;
    std::function<void()> Enemy::shotFunc;

    void outOfStage();
    void setMovePattern(const int pattern);
    void setShotPattern(const int pattern);
	got::Vector2<float> getShotPosition() const;
    void damageEffect();

};