//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/10/18
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include"Actor.h"
#include"Texture.h"

// プレイヤークラス（Actorを継承）
class Player : public Actor
{
public:
	Player();
	~Player();// override;

	bool init() override;
	void move() override;
	void draw() const override;
	void end() override;

private:
	float dx;
	float dy;


};