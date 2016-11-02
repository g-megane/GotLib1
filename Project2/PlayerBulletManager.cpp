//////////////////////////////////////////////////
// 作成日:2016/10/21
// 更新日:2016/11/1
// 制作者:got
//////////////////////////////////////////////////
#include "PlayerBulletManager.h"
#include "Game.h"

// コンストラクタ
PlayerBulletManager::PlayerBulletManager(const int num)
	: Actor(L"PlayerBulletManager"), bulletsNum(num)
{
	std::shared_ptr<Actor> bullet;
	for (int i = 0; i < bulletsNum; ++i) {
		bullet = std::make_shared<Bullet>();
		addChild(bullet);
	}
}
// デストラクタ
PlayerBulletManager::~PlayerBulletManager()
{
}
// 初期化
bool PlayerBulletManager::init()
{
	auto &root = Game::getInstance().getRootActor();
	enemyManager = dynamic_cast<EnemyManager*>(root->getChild(L"EnemyManager").get());

	for (auto & bullet : children) {
		if (!bullet->init()) {
			return false;
		}
	}

	return true;
}
// 移動
void PlayerBulletManager::move()
{
	for (auto & bullet : children) {
		bullet->move();
	}
	//std::vector<Actor>::iterator itr = ;
	for (auto & bullet : children) {
		if (bullet->getState() == UN_USE) { continue; }
		for (auto & enemy : enemyManager->getChildren()) {
			if (enemy->getState() == UN_USE) { continue; }
			if (bullet->getRect().intersection(enemy->getRect())) {
				bullet->setState(UN_USE);
				enemy->setState(UN_USE);
			}
		}
	}
}
// 描画
void PlayerBulletManager::draw() const
{

	for (auto & bullet : children) {
		bullet->draw();
	}
}
// 終了
void PlayerBulletManager::end()
{
}
// 弾の発射
void PlayerBulletManager::shot(const got::Vector2<float>& pos)
{
 	for (auto &bullet : children) {
		if (bullet->getState() == Bullet::State::UN_USE) {
			dynamic_cast<Bullet*>(bullet.get())->Shot(pos, 0.0f, 10.0f);
			return;
		}
	}
}
// 弾の発射
//void PlayerBulletManager::shot(float x, float y)
//{
//}
