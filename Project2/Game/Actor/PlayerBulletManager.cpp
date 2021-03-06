﻿//////////////////////////////////////////////////
// 作成日:2016/10/21
// 更新日:2016/11/30
// 制作者:got
//////////////////////////////////////////////////
#include "PlayerBulletManager.h"
#include "..\Common\Game.h"
#include "..\..\got\Utility\Collision.h"
#include "Player.h"
#include "..\..\got\Audio\XAudio2.h"

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

    shotCount = 0;

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
                got::XAudio2::getInstance().play("EnemyDamage");
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
        setShotFunc(_shotLevel);
    }

    this->shotFunc(pos);

    shotLevel = _shotLevel;
}


void PlayerBulletManager::setShotFunc(const int _shotLevel)
{
    switch (_shotLevel)
    {
    case 0:
        break;
    // 弾の発射(ShotLevel 1) : 直進で1発
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
    // 弾の発射(ShotLevel 2) : 直進で2発
    case 2:
        shotFunc = [&](const got::Vector2<float>& pos)
        {
            int count = 0;
            for (auto &bullet : children) {
                if (bullet->getState() == Bullet::STATE::UN_USE) {
                    if (count == 0) {
                        std::dynamic_pointer_cast<Bullet>(bullet)->shot(got::Vector2<float>(pos.x - 10.0f, pos.y), 0.0f, -0.8f);
                        ++count;
                    }
                    else if (count == 1) {
                        std::dynamic_pointer_cast<Bullet>(bullet)->shot(got::Vector2<float>(pos.x + 10.0f, pos.y), 0.0f, -0.8f);
                        return;
                    }
                }
            }
        };
        break;
    // 弾の発射(ShotLevel 3) : 直進で2発 + 左右の斜め2発
    case 3:
        shotFunc = [&](const got::Vector2<float>& pos)
        {
            int count = 0;
            for (auto &bullet : children) {
                if (bullet->getState() == Bullet::STATE::UN_USE) {
                    if (count == 0) {
                        std::dynamic_pointer_cast<Bullet>(bullet)->shot(got::Vector2<float>(pos.x - 10.0f, pos.y), 0.0f, -0.8f);
                        ++count;
                    }
                    else if (count == 1) {
                        std::dynamic_pointer_cast<Bullet>(bullet)->shot(got::Vector2<float>(pos.x + 10.0f, pos.y), 0.0f, -0.8f);
                        ++count;
                    }
                    else if (count == 2) {
                        std::dynamic_pointer_cast<Bullet>(bullet)->shot(got::Vector2<float>(pos.x + 10.0f, pos.y), 0.4f, -0.8f);
                        ++count;
                    }
                    else if (count == 3) {
                        std::dynamic_pointer_cast<Bullet>(bullet)->shot(got::Vector2<float>(pos.x - 10.0f, pos.y), -0.4f, -0.8f);
                        return;
                    }
                }
            }
        };
        break;
    // 弾の発射(ShotLevel 3) : 直進で2発 + 左右の斜め2発 + 5発に1回追尾弾
    case 4:
        shotFunc = [&](const got::Vector2<float>& pos)
        {
            int count = 0;
            for (auto &bullet : children) {
                if (bullet->getState() == Bullet::STATE::UN_USE) {
                    if (count == 0) {
                        std::dynamic_pointer_cast<Bullet>(bullet)->shot(got::Vector2<float>(pos.x - 10.0f, pos.y), 0.0f, -0.8f);
                        ++count;
                    }
                    else if (count == 1) {
                        std::dynamic_pointer_cast<Bullet>(bullet)->shot(got::Vector2<float>(pos.x + 10.0f, pos.y), 0.0f, -0.8f);
                        ++count;
                    }
                    else if (count == 2) {
                        std::dynamic_pointer_cast<Bullet>(bullet)->shot(got::Vector2<float>(pos.x + 10.0f, pos.y), 0.4f, -0.8f);
                        ++count;
                    }
                    else if (count == 3) {
                        std::dynamic_pointer_cast<Bullet>(bullet)->shot(got::Vector2<float>(pos.x - 10.0f, pos.y), -0.4f, -0.8f);
                        ++count;
                    }
                    else if (count == 4) {
                        ++shotCount;
                        if(shotCount < 5) { return; }
                        shotCount = 0;
                        float distance = 1000.0f;
                        std::shared_ptr<Actor> nearestEnemy = nullptr;
                        for (auto & enemy : enemyManager->getChildren()) {
                            if (enemy->getState() == STATE::UN_USE) { continue; }
                            if (distance >= pos.distance(enemy->getPosition())) {
                                distance = pos.distance(enemy->getPosition());
                                nearestEnemy = enemy;
                            }
                        }
                        // 敵が画面上にいない
                        if (nearestEnemy == nullptr) { 
                            std::dynamic_pointer_cast<Bullet>(bullet)->shot(got::Vector2<float>(pos.x - 10.0f, pos.y), 0.0f, -0.8f);
                        }
                        // 敵が見つかった
                        else {
                            std::dynamic_pointer_cast<Bullet>(bullet)->chaseShot(pos, nearestEnemy);
                            return;
                        }
                    }
                }
            }
        };
        break;
    default:
        assert(!"存在しないPlayerBulletPattern");
        break;
    }
}
