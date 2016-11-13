//////////////////////////////////////////////////
// 作成日:2016/10/27
// 更新日:2016/11/9
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
    //player             = std::dynamic_pointer_cast<Player>(root->getChild(L"Player"));

	auto spriteSize = got::SpriteManager::getInstance().getSprite("Enemy")->getSize();
	position.move(STAGE_WIDTH / 2, -spriteSize.height);
    
	//TODO:仮の移動量
	dx = 2.0f;
	dy = 2.0f;
    
    //moveFunc = &Enemy::move1;
    //moveFunc = &Enemy::move2;
    moveFunc = &Enemy::move3;

    //TODO:timeの初期化は必要？
	time.reset();
	time2.reset();

	state = STATE::USE; //TODO:UN_USEにしておいてEnemyManagerがUSEにする
	
    collisionRect = got::Rectangle<int>(position, spriteSize.width, spriteSize.height);

	return true;
}
// 更新
void Enemy::move()
{
	if (state == STATE::UN_USE) { return; }

	auto spriteSize = got::SpriteManager::getInstance().getSprite("Enemy")->getSize();
	
	// 移動
    (this->*moveFunc)();

	// 弾の発射
	if (time2.timeOver(500.0f)) {
		enemyBulletManager->shot(getShotPosition());
		time2.reset();
	}
	// ステージ外に出たら消す(Enemyが画面外に完全に出たら)
	if (position.x - spriteSize.width < 0)  { setState(STATE::UN_USE); }
	if (position.x > STAGE_WIDTH)           { setState(STATE::UN_USE); }
	if (position.y + spriteSize.height< 0)  { setState(STATE::UN_USE); }
	if (position.y > STAGE_HEIGHT)          { setState(STATE::UN_USE); }

}
// 描画
void Enemy::draw() const
{
	if (state == STATE::UN_USE) { return; }
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
		state = STATE::UN_USE;
	}
}

void Enemy::move1()
{
    auto spriteSize = got::SpriteManager::getInstance().getSprite("Enemy")->getSize();

    position.translate(0, dy);
    collisionRect = got::Rectangle<int>(position, spriteSize.width, spriteSize.height);
}

void Enemy::move2()
{
    auto spriteSize = got::SpriteManager::getInstance().getSprite("Enemy")->getSize();
    
    position.translate(dx, dy);	
    collisionRect = got::Rectangle<int>(position, spriteSize.width, spriteSize.height);
    
    if (time.timeOver(1000.0f)) {
    	dx = -dx;
    	time.reset();
    }
}

void Enemy::move3()
{
    auto spriteSize = got::SpriteManager::getInstance().getSprite("Enemy")->getSize();

    position.translate(0, dy);
    collisionRect = got::Rectangle<int>(position, spriteSize.width, spriteSize.height);

    if(position.y >= STAGE_HEIGHT / 2 - spriteSize.height) { dy = -dy; }
}

got::Vector2<float> Enemy::getShotPosition() const
{
	auto spriteSize = got::SpriteManager::getInstance().getSprite("Enemy")->getSize();
	return got::Vector2<float>(position.x + (spriteSize.width / 2), position.y + spriteSize.height);
}
