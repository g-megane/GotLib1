//////////////////////////////////////////////////
// 作成日:2016/10/21
// 更新日:2016/10/21
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Actor.h"

class Bullet : public Actor
{
public:
	Bullet();

	~Bullet();// override;

	bool init() override;
	void move() override;
	void draw() const override;
	void end() override;

private:
	enum State
	{
		USE,
		UN_USE
	};

	//float dx;
	float dy;
	State state;
};