//////////////////////////////////////////////////
// 作成日:2016/11/2
// 更新日:2016/11/2
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Actor.h"
#include "SpriteManager.h"
#include "Vector2.h"
#include "Time.h"

class Information : public Actor
{
public:
	Information();
	~Information();

	bool init() override;
	void move() override;
	void draw() const override;
	void end() override;

private:
	got::Vector2<float> poses[5];
	got::Time time;
	float elapsedTime;

};