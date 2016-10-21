//////////////////////////////////////////////////
// 作成日:2016/10/21
// 更新日:2016/10/21
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include <vector>
#include <memory>

#include "Bullet.h"

class BulletManager : public Actor
{
public:
	BulletManager(const int num);
	~BulletManager();
	bool init() override;
	void move() override;
	void draw() const override;
		
	void shot(float x, float y);
	void shot(got::Vector2<float> pos);

private:
	const int bulletsNum;
	std::vector<std::shared_ptr<Bullet>> bullets;
};