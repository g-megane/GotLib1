//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/12/22
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Actor.h"
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
    void  levelUp(const int _addLevel);
	const got::Vector2<float> getShotPosition() const; 

private:
    float dx;           // x移動量
    float dy;           // y移動量
    float deceleration; // 減速量
    int   hp;           // ヒットポイント
    const int maxHp;    // HPの限界値
    bool  isInvicible;
    std::shared_ptr<PlayerBulletManager> playerBulletManager;
    std::shared_ptr<EnemyManager>		 enemyManager;
    got::Time time;
    got::Time invincibleTime;
    got::Color<float> color;

    void damageEffect();
};