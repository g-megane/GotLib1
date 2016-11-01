//////////////////////////////////////////////////
// 作成日:2016/10/28
// 更新日:2016/10/28
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Actor.h"
#include "Enemy.h"

class EnemyManager : public Actor
{
public:
	EnemyManager(const int _num);
	~EnemyManager() override;

	bool init() override;
	void move() override;
	void draw() const override;
	void end() override;

private:
	//std::vector<Enemy> enemies;

};
