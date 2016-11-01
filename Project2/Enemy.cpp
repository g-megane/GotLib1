//////////////////////////////////////////////////
// 作成日:2016/10/27
// 更新日:2016/11/1
// 制作者:got
//////////////////////////////////////////////////
#include "Enemy.h"
#include "SpriteManager.h"

// コンストラクタ
Enemy::Enemy()
	: Actor(), time()
{
}
// デストラクタ
Enemy::~Enemy()
{
}
// 初期化
bool Enemy::init()
{
	auto & spriteManager = got::SpriteManager::getInstance();
	position.move(STAGE_WIDTH / 2, 0);
	//TODO:仮の移動量
	dx = 2.5f;
	dy = 2.5f;
	//TODO:timeの初期化は必要？
	time.reset();
	state = USE;
	collisionRect = got::Rectangle<int>(position, spriteManager.getSprite("Enemy")->getSize().width, spriteManager.getSprite("Enemy")->getSize().height);

	return true;
}
// 更新
void Enemy::move()
{
	if (state == UN_USE) { return; }

	auto spriteSize = got::SpriteManager::getInstance().getSprite("Enemy")->getSize();
	
	if (!time.timeOver(1000.0f)) {
		position.translate(dx, dy);
		collisionRect = got::Rectangle<int>(position, spriteSize.width, spriteSize.height);
		return;
	}
	dx = -dx;
	// ステージ外に出たら消す
	if (position.x < 0)								   { setState(UN_USE); }
	if (position.x > STAGE_WIDTH - spriteSize.width)   { setState(UN_USE); }
	if (position.y < 0)								   { setState(UN_USE); }
	if (position.y > STAGE_HEIGHT - spriteSize.height) { setState(UN_USE); }

	time.reset();
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
