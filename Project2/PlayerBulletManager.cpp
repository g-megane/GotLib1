//////////////////////////////////////////////////
// 作成日:2016/10/21
// 更新日:2016/10/27
// 制作者:got
//////////////////////////////////////////////////
#include "PlayerBulletManager.h"

// コンストラクタ
PlayerBulletManager::PlayerBulletManager(const int num)
	: Actor(L"PlayerBulletManager"), bulletsNum(num), bullets(num)
{
}
// デストラクタ
PlayerBulletManager::~PlayerBulletManager()
{
}
// 初期化
bool PlayerBulletManager::init()
{
	for (auto & bullet : bullets) {
		if (!bullet.init()) {
			return false;
		}
	}

	return true;
}
// 移動
void PlayerBulletManager::move()
{
	for (auto & bullet : bullets) {
		bullet.move();
	}
}
// 描画
void PlayerBulletManager::draw() const
{
	for (auto & bullet : bullets) {
		bullet.draw();
	}
}
// 終了
void PlayerBulletManager::end()
{
}
// 弾の発射
void PlayerBulletManager::shot(const got::Vector2<float>& pos)
{
	for (auto &bullet : bullets) {
		if (bullet.getState() == Bullet::State::UN_USE) {
			bullet.Shot(pos);
			return;
		}
	}
}
// 弾の発射
void PlayerBulletManager::shot(float x, float y)
{
}
