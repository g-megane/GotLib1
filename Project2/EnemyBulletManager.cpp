//////////////////////////////////////////////////
// 作成日:2016/10/28
// 更新日:2016/11/2
// 制作者:got
//////////////////////////////////////////////////
#include "EnemyBulletManager.h"
#include "Game.h"
#include "SceneManager.h"
#include "Player.h"

//コンストラクタ
EnemyBulletManager::EnemyBulletManager(const int _num)
	: Actor(L"EnemyBulletManager"), bulletsNum(_num)
{
	std::shared_ptr<Actor> bullet;
	for (int i = 0; i < bulletsNum; ++i) {
		bullet = std::make_shared<Bullet>();
		addChild(bullet);
	}
}
// デストラクタ
EnemyBulletManager::~EnemyBulletManager()
{
}
// 初期化
bool EnemyBulletManager::init()
{
	auto &root = Game::getInstance().getRootActor();
	player = dynamic_cast<Player*>(root->getChild(L"Player").get()); 

	for (auto & bullet : children) {
		if (!bullet->init()) {
			return false;
		}
	}
	return true;
}
// 更新
void EnemyBulletManager::move()
{
	for (auto & bullet : children) {
		bullet->move();
	}

	for (auto & bullet : children) {
		if (bullet->getState() == UN_USE) { continue; }
		if (player->getRect().intersection(bullet->getRect())) {
			SceneManager::getInstance().changeScene(SceneManager::RESULT);
		}

	}
}
// 描画
void EnemyBulletManager::draw() const
{
	for (auto & bullet : children) {
		bullet->draw();
	}
}
// 終了
void EnemyBulletManager::end()
{
}

void EnemyBulletManager::shot(const got::Vector2<float>& pos)
{
	for (auto & bullet : children) {
		if (bullet->getState() == Bullet::State::UN_USE) {
			dynamic_cast<Bullet*>(bullet.get())->Shot(pos, 0.0f, -10.0f);
			return;
		}
	}
}
