﻿//////////////////////////////////////////////////
// 作成日:2016/10/21
// 更新日:2016/11/30
// 制作者:got
//////////////////////////////////////////////////
#include "PlayerBulletManager.h"
#include "Game.h"
#include "Collision.h"
#include "Player.h"

// コンストラクタ
PlayerBulletManager::PlayerBulletManager(const int num)
	: Actor(L"PlayerBulletManager")
{
	std::shared_ptr<Actor> bullet;
	for (int i = 0; i < num; ++i) {
		bullet = std::make_shared<Bullet>("Bullet2");
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
    shotLevel = std::dynamic_pointer_cast<Player>(Game::getInstance().getRootActor()->getChild(L"Player"))->getHp();

    setShotFunc(shotLevel);
	auto &root = Game::getInstance().getRootActor();
	enemyManager = std::dynamic_pointer_cast<EnemyManager>(root->getChild(L"EnemyManager"));
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

	for (auto & bullet : children) {
		if (bullet->getState() == STATE::UN_USE) { continue; }
		for (auto & enemy : enemyManager->getChildren()) {
			if (enemy->getState() == STATE::UN_USE) { continue; }
			if(got::Collison::circleToCircle<float>(bullet->getCenter(), 8.0f, enemy->getCenter(), enemy->getRad())) {
            	bullet->setState(STATE::UN_USE);
				std::dynamic_pointer_cast<Enemy>(enemy)->setDamage(1);
                break;
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
void PlayerBulletManager::shot(const got::Vector2<float>& pos, const int _shotLevel)
{
    // shotLevelが上がっていれば
    if (shotLevel != _shotLevel) {
        //TODO: shotのパターンを変更する
        setShotFunc(_shotLevel);
    }

    this->shotFunc(pos);

    shotLevel = _shotLevel;
}
// 弾の発射(ShotLevel 1) : 直進で1発
void PlayerBulletManager::shot1(const got::Vector2<float>& pos)
{
 	for (auto &bullet : children) {
		if (bullet->getState() == Bullet::STATE::UN_USE) {
			std::dynamic_pointer_cast<Bullet>(bullet)->shot(pos, 0.0f, -0.8f);
			return;
		}
	}
}
// 弾の発射(ShotLevel 2) : 直進で2発
void PlayerBulletManager::shot2(const got::Vector2<float>& pos)
{
    int count = 0;
    for (auto &bullet : children) {
        if (bullet->getState() == Bullet::STATE::UN_USE) {
            if (count == 0) {
                std::dynamic_pointer_cast<Bullet>(bullet)->shot(pos.x - 10.0f, pos.y, 0.0f, -0.8f);
                ++count;
            }
            else if (count == 1) {
                std::dynamic_pointer_cast<Bullet>(bullet)->shot(pos.x + 10.0f, pos.y, 0.0f, -0.8f);
                return;
            }
        }
    }
}

void PlayerBulletManager::setShotFunc(const int _shotLevel)
{
    switch (_shotLevel)
    {
    case 1:
        shotFunc = [&](const got::Vector2<float>& pos)
        {
            for (auto &bullet : children) {
                if (bullet->getState() == Bullet::STATE::UN_USE) {
                    std::dynamic_pointer_cast<Bullet>(bullet)->shot(pos, 0.0f, -0.8f);
                    return;
                }
            }
        };
        break;
    case 2:
        shotFunc = [&](const got::Vector2<float>& pos)
        {
            int count = 0;
            for (auto &bullet : children) {
                if (bullet->getState() == Bullet::STATE::UN_USE) {
                    if (count == 0) {
                        std::dynamic_pointer_cast<Bullet>(bullet)->shot(pos.x - 10.0f, pos.y, 0.0f, -0.8f);
                        ++count;
                    }
                    else if (count == 1) {
                        std::dynamic_pointer_cast<Bullet>(bullet)->shot(pos.x + 10.0f, pos.y, 0.0f, -0.8f);
                        return;
                    }
                }
            }
        };
        break;
    case 0:
    default:
        break;
    }
}
