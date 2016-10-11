//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/9/27
// 制作者:got
//////////////////////////////////////////////////
#include "Player.h"
#include"Matrix4x4.h"

Player::Player()
{
	texture = std::make_shared<got::Texture>();

	texture->create(L"plane2.png");
}

Player::~Player()
{
}

bool Player::init()
{

	return false;
}

void Player::move()
{
}

void Player::draw() const
{
	auto mt = got::Matrix4x4<float>();
	auto color = got::Color<float>();
	auto rect = got::Rectangle<float>(position,texture->getTextureSize().width, texture->getTextureSize().height);

	texture->render(mt, color, rect);
}
