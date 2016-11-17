//////////////////////////////////////////////////
// 作成日:2016/10/28
// 更新日:2016/11/9
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Actor.h"
#include "Bullet.h"
#include "Vector2.h"
//#include "Player.h"

class Player;
class EnemyBulletManager : public Actor
{
public:
	EnemyBulletManager(const int _num);
	~EnemyBulletManager() override;
	bool init() override;
	void move() override;
	void draw() const override;
	void end() override;

	void shot1(const got::Vector2<float>& startPos, const float speed);
    void shot2(const got::Vector2<float>& startPos, const float speed);
    void shot3(const got::Vector2<float>& startPos, const int size, const float speed);
    void shot4(const got::Vector2<float>& startPos, const int size, const float speed);
    void shot5(const got::Vector2<float>& startPos, const int speed);

private:
	const int bulletsNum;
	std::shared_ptr<Player> player;
};