//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/10/18
// 制作者:got
//////////////////////////////////////////////////
#include "Player.h"
#include "Matrix4x4.h"
#include "SpriteManager.h"
#include "MyDirectInput.h"
#include "GV.h"
#include "Game.h"
#include "PlayerBulletManager.h"

Player::Player()
	:Actor(L"Player")
{
}

Player::~Player()
{
}

bool Player::init()
{
	dx = 6.0f; //TODO:移動量(仮)
	dy = 6.0f; //TODO:移動量(仮)
	auto &rootActor = Game::getInstance().getRootActor();

	auto spriteSize = got::SpriteManager::getInstance().getSprite("Player")->getSize();
	//texture->setTextureSize(spriteSize.width, spriteSize.height);

	position.move(STAGE_WIDTH / 2, STAGE_HEIGHT - 100); //TODO:スタート地点（仮）

	return false;
}
// 更新
void Player::move()
{
	//TODO:・斜め移動早くなるやつ直す
	//     ・弾の発射
	//     ・当たり判定
	auto &input		= got::MyDirectInput::getInstance();
	auto spriteSize = got::SpriteManager::getInstance().getSprite("Player")->getSize();

	// キー移動
	if		(input.keyPush(DIK_UP	)) { position.y -= dy; }
	else if (input.keyPush(DIK_DOWN	)) { position.y += dy; }
	if		(input.keyPush(DIK_RIGHT)) { position.x += dx; }
	else if (input.keyPush(DIK_LEFT	)) { position.x	-= dx; }

	// ステージ外に出たら補正する
	if (position.x < 0							     ) { position.x = 0;								}
	if (position.x > STAGE_WIDTH - spriteSize.width  ) { position.x = STAGE_WIDTH - spriteSize.width;	}
	if (position.y < 0								 ) { position.y = 0;								}
	if (position.y > STAGE_HEIGHT - spriteSize.height) { position.y = STAGE_HEIGHT - spriteSize.height; }

	//TODO:(仮)弾の発射
	if(input.keyTrigger(DIK_SPACE)) {
		auto &rootActor = Game::getInstance().getRootActor();
		auto bm = dynamic_cast<PlayerBulletManager*>(rootActor->getChild(L"PlayerBulletManager").get());
		bm->shot(getShotPosition());
	}
}

void Player::draw() const
{
	//TODO:テスト
	auto mt				 = got::Matrix4x4<float>::translate(position);
	auto & spriteManager = got::SpriteManager::getInstance();
	auto color			 = got::Color<float>();
	auto rect			 = got::Rectangle<int>(got::Vector2<int>(spriteManager.getSprite("Player")->getSize().width, spriteManager.getSprite("Player")->getSize().height));

	got::SpriteManager::getInstance().draw("Player", mt, rect, color);
}

void Player::end()
{
}

got::Vector2<int> Player::getShotPosition() const
{
	auto spriteSize = got::SpriteManager::getInstance().getSprite("Player")->getSize();
	return got::Vector2<float>(position.x + (spriteSize.width / 2), position.y);
}
