//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/10/11
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include"Actor.h"
#include"Texture.h"

class Player : public Actor
{
public:
	Player();
	~Player();

	bool init() override;
	void move() override;
	void draw()const override;

};