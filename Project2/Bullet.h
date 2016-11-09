//////////////////////////////////////////////////
// 作成日:2016/10/21
// 更新日:2016/11/9
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Actor.h"

class Bullet : public Actor
{
public:
	Bullet();
	~Bullet() override;

	bool init() override;
	void move() override;
	void draw() const override;
	void end() override;

	void Shot(const got::Vector2<float>& vec, const float _dx, const float _dy);

private:
	float dx;
	float dy;
};