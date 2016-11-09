//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/10/26
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Actor.h"
#include "Texture.h"
#include "PlayerBulletManager.h"
#include "EnemyManager.h"
#include "Time.h"

// プレイヤークラス（Actorを継承）
class Player : public Actor
{
public:
	Player();
	~Player() override;

	bool init() override;
	void move() override;
	void draw() const override;
	void end() override;

	int getHp() const;
	void setDamage(const int damage);
	got::Vector2<int> getShotPosition() const; 

private:
	float dx;
	float dy;
	int   hp;
	std::shared_ptr<PlayerBulletManager> playerBulletManager;
	std::shared_ptr<EnemyManager>		 enemyManager;
	got::Time time;

};