//////////////////////////////////////////////////
// 作成日:2016/10/28
// 更新日:2016/11/23
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
#ifndef _DEBUG
			player->setDamage(1);
#endif // _DEBUG
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
            shotVec.move(player->getCenter().x - startPos.x, player->getCenter().y - startPos.y);
            shotVec2 = shotVec.normalize();
            std::dynamic_pointer_cast<Bullet>(bullet)->shot(startPos, shotVec2.x * speed, shotVec2.y * speed);
            return;
        }
    }
}
// 円形弾(引数のsizeは弾を何度ずつ出すかということ)
void EnemyBulletManager::shot3(const got::Vector2<float>& startPos, const int size, const float speed)
{
    // dtheta間隔で弾を発射
    const float dtheta = 360.0f / size;

    got::Vector2<float> shotVec(player->getCenter().x - startPos.x, player->getCenter().y - startPos.y);
    got::Vector2<float> shotVec2(shotVec.normalize());
    
    for (int i = 0; i < size; ++i) {
        for (auto & bullet : children) {
            if (bullet->getState() == Bullet::STATE::UN_USE) {
                shotVec = shotVec2.rotate(dtheta * i);
                std::dynamic_pointer_cast<Bullet>(bullet)->shot(startPos, shotVec.x * speed, shotVec.y * speed);
                break;
            }
        }
    }
}
// 奇数way弾
void EnemyBulletManager::shot4(const got::Vector2<float>& startPos, const int size, const float speed)
{
    const float dtheta = 10.0f * PI / 180;

    got::Vector2<float> shotVec(player->getCenter().x - startPos.x, player->getCenter().y - startPos.y);
    got::Vector2<float> shotVec2(shotVec.normalize());

    int loopCount = 0;
    int leftTurncount = 0;
    int rightTurnCount = 0;
    for (auto & bullet : children) {
        if (bullet->getState() == Bullet::STATE::UN_USE) {
            if(loopCount == size) {
                break;
            }
            if (loopCount == 0) {
                std::dynamic_pointer_cast<Bullet>(bullet)->shot(startPos, shotVec2.x * speed, shotVec2.y * speed);
                ++loopCount;
            }
            else if (loopCount % 2 == 1) {
                ++leftTurncount;
                shotVec = shotVec2.rotate(10.0f * leftTurncount);
                std::dynamic_pointer_cast<Bullet>(bullet)->shot(startPos, shotVec.x * speed, shotVec.y * speed);
                ++loopCount;
            }
            else if(loopCount % 2 == 0) {
                ++rightTurnCount;
                shotVec = shotVec2.rotate(-10.0f * rightTurnCount);
                std::dynamic_pointer_cast<Bullet>(bullet)->shot(startPos, shotVec.x * speed, shotVec.y * speed);
                ++loopCount;
            }
        }
    }
    
}
