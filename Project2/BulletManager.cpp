//////////////////////////////////////////////////
// 作成日:2016/10/21
// 更新日:2016/10/21
// 制作者:got
//////////////////////////////////////////////////
#include "BulletManager.h"

// コンストラクタ
BulletManager::BulletManager(const int num)
	: bulletsNum(num)
{
	bullets.reserve(bulletsNum);
	for (int i = 0; i < bulletsNum; i++) {
		bullets.emplace_back(std::make_shared<Bullet>());
	}
}
// デストラクタ
BulletManager::~BulletManager()
{
}
// 初期化
bool BulletManager::init()
{
	for (auto bullet : bullets) {
		if (!bullet->init()) {
			return false;
		}
	}

	return true;
}
void BulletManager::move()
{
	for (auto bullet : bullets) {
		bullet->move();
	}
}
void BulletManager::draw() const
{
	for (auto bullet : bullets) {
		bullet->draw();
	}
}
// 弾の発射
void BulletManager::shot(float x, float y)
{
}
// 弾の発射
void BulletManager::shot(got::Vector2<float> pos)
{
}
