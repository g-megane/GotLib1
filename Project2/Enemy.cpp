//////////////////////////////////////////////////
// 作成日:2016/10/27
// 更新日:2016/11/1
// 制作者:got
//////////////////////////////////////////////////
#include "Enemy.h"
#include "SpriteManager.h"
#include "Game.h"

// コンストラクタ
Enemy::Enemy(const int _hp)
	: Actor(), time(), time2()
{
	hp = _hp;
}
// デストラクタ
Enemy::~Enemy()
{
}
// 初期化
bool Enemy::init()
{
	auto &root = Game::getInstance().getRootActor();
	enemyBulletManager = std::dynamic_pointer_cast<EnemyBulletManager>(root->getChild(L"EnemyBulletManager"));
	auto & spriteManager = got::SpriteManager::getInstance();
	position.move(STAGE_WIDTH / 2, 0);
	//TODO:仮の移動量
	dx = 2.5f;
	dy = 2.5f;
	//TODO:timeの初期化は必要？
	time.reset();
	time2.reset();
	state = USE;
	collisionRect = got::Rectangle<int>(position, spriteManager.getSprite("Enemy")->getSize().width, spriteManager.getSprite("Enemy")->getSize().height);

	return true;
}
// 更新
void Enemy::move()
{
	if (state == UN_USE) { return; }

	auto spriteSize = got::SpriteManager::getInstance().getSprite("Enemy")->getSize();
	
	// 移動
	position.translate(dx, dy);	
	collisionRect = got::Rectangle<int>(position, spriteSize.width, spriteSize.height);
	if (time.timeOver(1000.0f)) {
		dx = -dx;
		time.reset();
	}

	// 弾の発射
	if (time2.timeOver(500.0f)) {
		enemyBulletManager->shot(getShotPosition());
		time2.reset();
	}
	// ステージ外に出たら消す(Enemyが画面外に完全に出たら)
	if (position.x - spriteSize.width < 0)  { setState(UN_USE); }
	if (position.x > STAGE_WIDTH)			{ setState(UN_USE); }
	if (position.y < 0) { setState(UN_USE); }
	if (position.y > STAGE_HEIGHT)			{ setState(UN_USE); }

}
// 描画
void Enemy::draw() const
{
	if (state == UN_USE) { return; }
	//TODO:テスト
	auto mt				 = got::Matrix4x4<float>::translate(position);
	auto & spriteManager = got::SpriteManager::getInstance();
	auto color			 = got::Color<float>();
	auto drawRect	     = got::Rectangle<int>(got::Vector2<int>(spriteManager.getSprite("Enemy")->getSize().width, spriteManager.getSprite("Enemy")->getSize().height));

	spriteManager.draw("Enemy", mt, drawRect, color);
}
// 終了
void Enemy::end()
{
}

int Enemy::getHp() const
{
	return hp;
}

void Enemy::setDamage(const int damage)
{
	hp -= damage;
	if (hp <= 0) {
		state = UN_USE;
	}
}

got::Vector2<float> Enemy::getShotPosition() const
{
	auto spriteSize = got::SpriteManager::getInstance().getSprite("Enemy")->getSize();
	return got::Vector2<float>(position.x + (spriteSize.width / 2), position.y + spriteSize.height);
}
