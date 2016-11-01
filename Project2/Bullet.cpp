//////////////////////////////////////////////////
// 作成日:2016/10/21
// 更新日:2016/10/21
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
    rect = got::Rectangle<int>(got::Vector2<int>(spriteManager.getSprite("Bullet")->getSize().width, spriteManager.getSprite("Bullet")->getSize().height));
	state = UN_USE;
	position.move(STAGE_WIDTH / 2, STAGE_HEIGHT - 100);
	rect = got::Rectangle<int>(position, spriteManager.getSprite("Bullet")->getSize().width, spriteManager.getSprite("Bullet")->getSize().height);
	dx = 0.5f;
	dy = 10.0f;
	return true;
}
// 更新
void Bullet::move()
{
	if (state == UN_USE) { return; }
	auto &spriteManager = got::SpriteManager::getInstance();
	position.y -= dy;
	rect = got::Rectangle<int>(position, spriteManager.getSprite("Bullet")->getSize().width, spriteManager.getSprite("Bullet")->getSize().height);
	auto spriteSize = got::SpriteManager::getInstance().getSprite("Bullet")->getSize();
	if (position.x < 0)								   { setState(UN_USE); }
	if (position.x > STAGE_WIDTH - spriteSize.width)   { setState(UN_USE); }
	if (position.y < 0)								   { setState(UN_USE); }
	if (position.y > STAGE_HEIGHT - spriteSize.height) { setState(UN_USE); }
}
// 描画
void Bullet::draw() const
{
	if (state == UN_USE) { return; }
	
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

void Bullet::Shot(const got::Vector2<float>& vec)
{
	auto spriteSize = got::SpriteManager::getInstance().getSprite("Bullet")->getSize();
	position = got::Vector2<float>(vec.x - spriteSize.width / 2, vec.y - spriteSize.height / 2);
	state = USE;
}

void Bullet::Shot(const float x, const float y)
{
}
