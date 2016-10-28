//////////////////////////////////////////////////
// 作成日:2016/10/28
// 更新日:2016/10/28
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include <vector>
#include "Actor.h"
#include "Bullet.h"

class EnemyBulletManager : public Actor
{
public:
	EnemyBulletManager(const int _num);
	~EnemyBulletManager() override;
	bool init() override;
	void move() override;
	void draw() const override;
	void end() override;

private:
	const int bulletsNum;
	std::vector<Bullet> bullets;

};