//////////////////////////////////////////////////
// 作成日:2016/10/21
// 更新日:2016/11/24
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Actor.h"
#include <string>

class Bullet : public Actor
{
public:
	Bullet(const std::string& _spriteName);
	~Bullet() override;

	bool init() override;
	void move() override;
	void draw() const override;
	void end() override;

	void shot(const got::Vector2<float>& vec, const float _dx, const float _dy);

private:
	float dx;
	float dy;
    got::Color<float> color;

};