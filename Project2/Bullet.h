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
	//enum State
	//{
	//	USE,
	//	UN_USE
	//};

	Bullet();
	~Bullet() override;

	bool init() override;
	void move() override;
	void draw() const override;
	void end() override;

	void Shot(const got::Vector2<float>& vec);
	//void Shot(const float x, const float y);

private:
	float dx;
	float dy;
};