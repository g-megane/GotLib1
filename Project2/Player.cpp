//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/11/24
// 制作者:got
//////////////////////////////////////////////////
#include "Player.h"
#include "Matrix4x4.h"
#include "SpriteManager.h"
#include "MyDirectInput.h"
#include "GV.h"
#include "Game.h"
#include "SceneManager.h"

// コンストラクタ
Player::Player()
	:Actor(L"Player"), time()
{
	time = got::Time();
    spriteName = "Player";
}
// デストラクタ
Player::~Player()
{
}
// 初期化
bool Player::init()
{
	dx           = 0.4f; //TODO:移動量(仮)
	dy           = 0.4f; //TODO:移動量(仮)
    deceleration = 1.0f; // 減速量
	hp           = 1;
	
	auto &root          = Game::getInstance().getRootActor();
	enemyManager		= std::dynamic_pointer_cast<EnemyManager>(root->getChild(L"EnemyManager"));
	playerBulletManager = std::dynamic_pointer_cast<PlayerBulletManager>(root->getChild(L"PlayerBulletManager"));

	auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();
	
	position.move(STAGE_WIDTH / 2, STAGE_HEIGHT - 100); //TODO:スタート地点（仮）
	collisionRect = got::Rectangle<int>(position, spriteSize.width, spriteSize.height);

	time.reset();

	return true;
}
// 更新
void Player::move()
{
	//TODO:・斜め移動早くなるやつ直す
	auto &input		= got::MyDirectInput::getInstance();
	auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();

    auto dTime = Game::getInstance().getDeltaTime();

    // 低速移動(左Shiftを押している間移動量を減らす)
    deceleration = 1.0f;
    if (input.keyPush(DIK_LSHIFT)) { deceleration = 0.5f; }

	// キー移動
	if		(input.keyPush(DIK_UP	)) { position.y -= dy * deceleration * dTime; }
	else if (input.keyPush(DIK_DOWN	)) { position.y += dy * deceleration * dTime; }
	if		(input.keyPush(DIK_RIGHT)) { position.x += dx * deceleration * dTime; }
	else if (input.keyPush(DIK_LEFT	)) { position.x	-= dx * deceleration * dTime; }

	// ステージ外に出たら補正する
	if (position.x < 0							     ) { position.x = 0;								}
	if (position.x > STAGE_WIDTH - spriteSize.width  ) { position.x = STAGE_WIDTH - spriteSize.width;	}
	if (position.y < 0								 ) { position.y = 0;								}
	if (position.y > STAGE_HEIGHT - spriteSize.height) { position.y = STAGE_HEIGHT - spriteSize.height; }

	collisionRect = got::Rectangle<int>(position, spriteSize.width, spriteSize.height);

	// 敵とのあたり判定
	for (auto & enemy : enemyManager->getChildren()) {
		if (enemy->getState() == STATE::UN_USE) { continue; }
        if (collisionRect.intersection(enemy->getRect())) {
#ifndef _DEBUG
            setDamage(1);
#endif // !_DEBUG
		}

	}

	//TODO:(仮)弾の発射
	if (!time.timeOver(250.0f)) { return; } // 発射間隔(仮)
	time.reset();
	if(input.keyPush(DIK_Z)) {
		playerBulletManager->shot(getShotPosition());
	}
}
// 描画
void Player::draw() const
{
	//TODO:テスト
	auto mt			= got::Matrix4x4<float>::translate(position);
	auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();
	auto color		= got::Color<float>();
	auto drawRect	= got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));

	got::SpriteManager::getInstance().draw(spriteName, mt, drawRect, color);
}
// 終了
void Player::end()
{
}
// ヒットポイントを返す
int Player::getHp() const
{
	return hp;
}
// ダメージ処理
void Player::setDamage(const int damage)
{
	hp -= damage;
	if (hp <= 0) {
		SceneManager::getInstance().changeScene(SceneManager::SCENE_NAME::RESULT);
	}
}
// 弾を発射する座標を返す
const got::Vector2<float> Player::getShotPosition() const
{
	auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();
	return got::Vector2<float>(position.x + (spriteSize.width / 2), position.y);
}

const got::Vector2<float> Player::getCenter() const
{
    auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();
    return got::Vector2<float>(position.x + spriteSize.width / 2, position.y + spriteSize.height / 2);
}
