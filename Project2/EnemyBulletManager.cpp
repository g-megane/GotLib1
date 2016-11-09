//////////////////////////////////////////////////
// 作成日:2016/10/28
// 更新日:2016/11/9
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
	player = std::dynamic_pointer_cast<Player>(root->getChild(L"Player")); 

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
		if (bullet->getState() == STATE::UN_USE) { continue; }
		if (player->getRect().intersection(bullet->getRect())) {
			player->setDamage(1);
			bullet->setState(STATE::UN_USE);
			return;
			//SceneManager::getInstance().changeScene(SceneManager::RESULT);
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
		if (bullet->getState() == Bullet::STATE::UN_USE) {
			std::dynamic_pointer_cast<Bullet>(bullet)->Shot(pos, 0.0f, -10.0f);
			return;
		}
	}
}
