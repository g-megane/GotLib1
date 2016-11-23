//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/11/23
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

	int   getHp() const;
	void  setDamage(const int damage);
	const got::Vector2<float> getShotPosition() const; 
    const got::Vector2<float> getCenter() const;

private:
	float dx;           // x移動量
	float dy;           // y移動量
    float deceleration; // 減速量
	int   hp;           // ヒットポイント
	std::shared_ptr<PlayerBulletManager> playerBulletManager;
	std::shared_ptr<EnemyManager>		 enemyManager;
	got::Time time;

};