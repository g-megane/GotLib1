//////////////////////////////////////////////////
// 作成日:2016/10/27
// 更新日:2016/12/19
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include <random>
#include <functional>
#include "Actor.h"
#include "..\..\got\Utility\Time.h"
#include "EnemyBulletManager.h"
#include "..\..\got\Utility\Sprite.h"

class Enemy : public Actor
{
public:
	Enemy();
	~Enemy() override;

	bool init() override;
	void move() override;
	void draw() const override;
	void end()  override;

	const int  getHp() const;
	virtual void setDamage(const int damage);
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
                 const int          _score
        );

protected:
	int	  hp;
	float dx;
	float dy;
    float bulletSpeed;
    float shotInterval;
    int   score;
    float dTime;
    got::Color<float> color;
	got::Time time;
	got::Time time2;
    std::random_device rd;

	std::shared_ptr<EnemyBulletManager> enemyBulletManager;
    // 関数オブジェクト
    std::function<void()> Enemy::moveFunc;
    std::function<void()> Enemy::shotFunc;
    // private関数
    inline void outOfStage();
    void setMovePattern(const int pattern);
    void setShotPattern(const int pattern);
	got::Vector2<float> getShotPosition() const;
    void damageEffect();

};