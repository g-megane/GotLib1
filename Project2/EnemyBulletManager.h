//////////////////////////////////////////////////
// 作成日:2016/10/28
// 更新日:2016/11/2
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Actor.h"
#include "Bullet.h"
#include "Vector2.h"
//#include "Player.h"

class Player;
class EnemyBulletManager : public Actor
{
public:
	EnemyBulletManager(const int _num);
	~EnemyBulletManager() override;
	bool init() override;
	void move() override;
	void draw() const override;
	void end() override;

	void shot(const got::Vector2<float>& pos);

private:
	const int bulletsNum;
	Player *player;
};