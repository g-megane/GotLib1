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
	state = UN_USE;
	position.move(STAGE_WIDTH / 2, STAGE_HEIGHT - 100);
	dx = 0.5f;
	dy = 10.0f;
	return true;
}
// 更新
void Bullet::move()
{
	if (state == UN_USE) return;

	position.y -= dy;

	auto spriteSize = got::SpriteManager::getInstance().getSprite("Bullet")->getSize();
	if (position.x < 0)								   { stateReset(); }
	if (position.x > STAGE_WIDTH - spriteSize.width)   { stateReset(); }
	if (position.y < 0)								   { stateReset(); }
	if (position.y > STAGE_HEIGHT - spriteSize.height) { stateReset(); }
}
// 描画
void Bullet::draw() const
{
	if (state == UN_USE) return;
	
	auto mt = got::Matrix4x4<float>::translate(position);
	auto & spriteManager = got::SpriteManager::getInstance();
	auto color = got::Color<float>();
	auto rect = got::Rectangle<int>(got::Vector2<int>(spriteManager.getSprite("Bullet")->getSize().width, spriteManager.getSprite("Bullet")->getSize().height));

	got::SpriteManager::getInstance().draw("Bullet", mt, rect, color);
	
}

void Bullet::end()
{
}

void Bullet::Shot(const got::Vector2<float> vec)
{
	position = vec;
	state = USE;
}

void Bullet::Shot(const float x, const float y)
{
}

void Bullet::setState(const State _state)
{
	state = _state;
}

Bullet::State Bullet::getState() const
{
	return state;
}

void Bullet::stateReset()
{
	state = UN_USE;
}
