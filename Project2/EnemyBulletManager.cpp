//////////////////////////////////////////////////
// 作成日:2016/10/28
// 更新日:2016/11/16
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
			//player->setDamage(1);
			bullet->setState(STATE::UN_USE);
			return;
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
// 進行方向に弾を発射
void EnemyBulletManager::shot1(const got::Vector2<float>& startPos, const float speed)
{
	for (auto & bullet : children) {
		if (bullet->getState() == Bullet::STATE::UN_USE) {
			std::dynamic_pointer_cast<Bullet>(bullet)->shot(startPos, 0.0f, speed);
			return;
		}
	}
}
// Playerを狙って弾を発射
void EnemyBulletManager::shot2(const got::Vector2<float>& startPos, const float speed)
{
    got::Vector2<float> shotVec;
    got::Vector2<float> shotVec2;

    for (auto & bullet : children) {
        if (bullet->getState() == Bullet::STATE::UN_USE) {
            shotVec.move(player->getPosition().x - startPos.x, player->getPosition().y - startPos.y);
            shotVec2 = shotVec.normalize();
            std::dynamic_pointer_cast<Bullet>(bullet)->shot(startPos, shotVec2.x * speed, shotVec2.y * speed);
            return;
        }
    }
}
// 円形弾(引数のsizeは弾を何度ずつ出すかということ)
void EnemyBulletManager::shot3(const got::Vector2<float>& startPos, const int size, const float speed)
{
    const float dtheta = 2.0f * PI / size;
    got::Vector2<float> shotVec;
    got::Vector2<float> shotVec2;
    got::Vector2<float> shotVec3;
    for (int i = 0; i < size; ++i) {
        for (auto & bullet : children) {
            if (bullet->getState() == Bullet::STATE::UN_USE) {
                shotVec.move(player->getPosition().x - startPos.x, player->getPosition().y - startPos.y);
                shotVec2 = shotVec.normalize();
                shotVec3 = shotVec2.rotate(dtheta * i);
                std::dynamic_pointer_cast<Bullet>(bullet)->shot(startPos, shotVec3.x * speed, shotVec3.y * speed);
                break;
            }
        }
    }
}

void EnemyBulletManager::shot4(const got::Vector2<float>& startPos, const int size, const float speed)
{
}
