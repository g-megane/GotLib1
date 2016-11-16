//////////////////////////////////////////////////
// 作成日:2016/10/21
// 更新日:2016/11/16
// 制作者:got
//////////////////////////////////////////////////
#include "Bullet.h"
#include "SpriteManager.h"

#include <random>

// コンストラクタ
Bullet::Bullet()
	:Actor()
{
	//std::random_device rd;
	//auto urd = std::uniform_real_distribution<float>(0.1f, 5.0f);
	//dy = urd(rd);	
}

// デストラクタ
Bullet::~Bullet()
{
}
// 初期化
bool Bullet::init()
{
	auto &spriteManager = got::SpriteManager::getInstance();
    collisionRect = got::Rectangle<int>(got::Vector2<int>(spriteManager.getSprite("Bullet")->getSize().width, spriteManager.getSprite("Bullet")->getSize().height));
	state = STATE::UN_USE;
	position.move(STAGE_WIDTH / 2, STAGE_HEIGHT - 100);
	collisionRect = got::Rectangle<int>(position, spriteManager.getSprite("Bullet")->getSize().width, spriteManager.getSprite("Bullet")->getSize().height);
	dx = 0.0f;
	dy = 0.0f;
	return true;
}
// 更新
void Bullet::move()
{
	if (state == STATE::UN_USE) { return; }
	auto &spriteManager = got::SpriteManager::getInstance();
    position.x += dx;
 	position.y += dy;
	collisionRect = got::Rectangle<int>(position, spriteManager.getSprite("Bullet")->getSize().width, spriteManager.getSprite("Bullet")->getSize().height);
	auto spriteSize = got::SpriteManager::getInstance().getSprite("Bullet")->getSize();
	if (position.x < 0)								   { setState(STATE::UN_USE); }
	if (position.x > STAGE_WIDTH - spriteSize.width)   { setState(STATE::UN_USE); }
	if (position.y < 0)								   { setState(STATE::UN_USE); }
	if (position.y > STAGE_HEIGHT - spriteSize.height) { setState(STATE::UN_USE); }
}
// 描画
void Bullet::draw() const
{
	if (state == STATE::UN_USE) { return; }
	
	auto mt = got::Matrix4x4<float>::translate(position);
	auto & spriteManager = got::SpriteManager::getInstance();
	auto color = got::Color<float>();
	auto drawRect = got::Rectangle<int>(got::Vector2<int>(spriteManager.getSprite("Bullet")->getSize().width, spriteManager.getSprite("Bullet")->getSize().height));

	got::SpriteManager::getInstance().draw("Bullet", mt, drawRect, color);
	
}
// 終了
void Bullet::end()
{
}

void Bullet::Shot(const got::Vector2<float>& vec, const float _dx, const float _dy)
{
	dx = _dx;
	dy = _dy;
	auto spriteSize = got::SpriteManager::getInstance().getSprite("Bullet")->getSize();
	position = got::Vector2<float>(vec.x - spriteSize.width / 2, vec.y - spriteSize.height / 2);
	state = STATE::USE;
}

//void Bullet::Shot(const float x, const float y)
//{
//}
