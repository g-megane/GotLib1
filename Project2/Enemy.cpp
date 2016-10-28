//////////////////////////////////////////////////
// 作成日:2016/10/27
// 更新日:2016/10/28
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
	position.ZERO;
	//TODO:仮の移動量
	dx = 2.5f;
	dy = 2.5f;
	//TODO:timeの初期化は必要？
	time.reset();
	state = USE;

	return true;
}
// 更新
void Enemy::move()
{
	if (state == UN_USE) { return; }
	// ステージ外に出たら補正する
	auto spriteSize = got::SpriteManager::getInstance().getSprite("Enemy")->getSize();
	if (position.x < 0)								   { setState(UN_USE); }
	if (position.x > STAGE_WIDTH - spriteSize.width)   { setState(UN_USE); }
	if (position.y < 0)								   { setState(UN_USE); }
	if (position.y > STAGE_HEIGHT - spriteSize.height) { setState(UN_USE); }

	if (!time.timeOver(1000.0f)) {
		position.translate(dx, dy);
		return;
	}
	dx = -dx;
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
	auto rect			 = got::Rectangle<int>(got::Vector2<int>(spriteManager.getSprite("Enemy")->getSize().width, spriteManager.getSprite("Enemy")->getSize().height));

	spriteManager.draw("Enemy", mt, rect, color);
}
// 終了
void Enemy::end()
{
}
