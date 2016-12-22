//////////////////////////////////////////////////
// 作成日:2016/10/21
// 更新日:2016/11/9
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include <vector>
#include <memory>
#include <functional>
#include "Bullet.h"
#include "EnemyManager.h"

class PlayerBulletManager : public Actor
{
public:
	PlayerBulletManager(const int num);
	~PlayerBulletManager() override;
	bool init() override;
	void move() override;
	void draw() const override;
	void end() override;
		
    void shot (const got::Vector2<float>& pos, const int _shotLevel);

private:
    int shotLevel;
    int shotCount;
    void setShotFunc(const int _shotLevel);
    std::function<void(const got::Vector2<float>&)> PlayerBulletManager::shotFunc;
	std::shared_ptr<EnemyManager> enemyManager;
};