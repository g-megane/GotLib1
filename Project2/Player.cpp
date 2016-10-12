//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/9/27
// 制作者:got
//////////////////////////////////////////////////
#include "Player.h"
#include"Matrix4x4.h"
#include"SpriteManager.h"

Player::Player()
{
	//texture = std::make_shared<got::Texture>();
	//
	//texture->create(L"plane2.png");
}

Player::~Player()
{
}

bool Player::init()
{
	dx = 0.0f;
	dy = 0.0f;

	return false;
}

void Player::move()
{
	dx += 0.1f;
	dy += 0.1f;

	//position.move(dx, dy);
}

void Player::draw() const
{
	//TODO:テスト
	auto mt = got::Matrix4x4<float>::translate(dx, dy);
	//auto mt = got::Matrix4x4<float>::rotate(dx);
	//auto mt = got::Matrix4x4<float>::scale(dx, dy);
	//auto mt2 = got::Matrix4x4<float>::rotate(2.0f) * mt;
	auto color = got::Color<float>();
	auto & spriteManager = got::SpriteManager::getInstance();
	auto rect = got::Rectangle<int>(position, spriteManager.getSprite("Player")->getSize().width, spriteManager.getSprite("Player")->getSize().height);

	got::SpriteManager::getInstance().draw("Player", mt, rect, color);
	//texture->render(mt, rect, color);
}
