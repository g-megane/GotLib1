//////////////////////////////////////////////////
// 作成日:2016/10/28
// 更新日:2016/10/28
// 制作者:got
//////////////////////////////////////////////////
#include "EnemyBulletManager.h"

//コンストラクタ
EnemyBulletManager::EnemyBulletManager(const int _num)
	: Actor(L"EnemyBulletManager"), bulletsNum(_num), bullets(_num)
{
}
// デストラクタ
EnemyBulletManager::~EnemyBulletManager()
{
}
// 初期化
bool EnemyBulletManager::init()
{
	for (auto & bullet : bullets) {
		if (!bullet.init()) {
			return false;
		}
	}
	return true;
}
// 更新
void EnemyBulletManager::move()
{
	for (auto & bullet : bullets) {
		bullet.move();
	}
}
// 描画
void EnemyBulletManager::draw() const
{
	for (auto & bullet : bullets) {
		bullet.draw();
	}
}
// 終了
void EnemyBulletManager::end()
{
}
