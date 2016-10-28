//////////////////////////////////////////////////
// 作成日:2016/10/27
// 更新日:2016/10/27
// 制作者:got
//////////////////////////////////////////////////
#pragma once

#include "Actor.h"
#include "Time.h"

class Enemy : public Actor
{
public:
	Enemy();
	~Enemy() override;

	bool init() override;
	void move() override;
	void draw() const override;
	void end() override;

private:
	float dx;
	float dy;
	got::Time time;

};