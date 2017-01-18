//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/12/22
// 制作者:got
//////////////////////////////////////////////////
#include "Player.h"
#include "Matrix4x4.h"
#include "SpriteManager.h"
#include "MyDirectInput.h"
#include "GV.h"
#include "Game.h"
#include "SceneManager.h"
#include "Collision.h"
#include "XAudio2.h"

// コンストラクタ
//TODO: Shotのパターン数やゲームの難しさを考慮して決める
Player::Player()
    :Actor(L"Player"), time(), maxHp(4)
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
    hp           = 1;    // ヒットポイント
    rad          = 4.0f; // 円のあたり判定の半径
    
    auto &root          = Game::getInstance().getRootActor();
    enemyManager        = std::dynamic_pointer_cast<EnemyManager>(root->getChild(L"EnemyManager"));
    playerBulletManager = std::dynamic_pointer_cast<PlayerBulletManager>(root->getChild(L"PlayerBulletManager"));
    
    auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();
    
    position.move(STAGE_WIDTH / 2, STAGE_HEIGHT - 100); //TODO:スタート地点（仮）
    
    time.reset();
    
    return true;
}
// 更新
void Player::move()
{
    //TODO:・斜め移動早くなるやつ直す
    auto &input     = got::MyDirectInput::getInstance();
    auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();

    auto dTime = Game::getInstance().getDeltaTime();

    // 低速移動(左Shiftを押している間移動量を減らす)
    deceleration = 1.0f;
    if (input.keyPush(DIK_LSHIFT))     { deceleration = 0.3f; }

    // キー移動
    if      (input.keyPush(DIK_UP   )) { position.y -= dy * deceleration * dTime; }
    else if (input.keyPush(DIK_DOWN )) { position.y += dy * deceleration * dTime; }
    if      (input.keyPush(DIK_RIGHT)) { position.x += dx * deceleration * dTime; }
    else if (input.keyPush(DIK_LEFT )) { position.x	-= dx * deceleration * dTime; }

    // ステージ外に出たら補正する
    if      (position.x < 0                               ) { position.x = 0;                                }
    else if (position.x > STAGE_WIDTH - spriteSize.width  ) { position.x = STAGE_WIDTH - spriteSize.width;   }
    if      (position.y < 0                               ) { position.y = 0;                                }
    else if (position.y > STAGE_HEIGHT - spriteSize.height) { position.y = STAGE_HEIGHT - spriteSize.height; }

    // 敵とのあたり判定
    for (auto & enemy : enemyManager->getChildren()) {
        if (enemy->getState() == STATE::UN_USE) { continue; }
        if(got::Collison::circleToCircle(this->getCenter(), rad, enemy->getCenter(), enemy->getRad())) {
#ifndef _DEBUG
            setDamage(1);
#endif // !_DEBUG
        }
    }
    
    // 弾の発射
    if (!time.timeOver(250.0f)) { return; } // 発射間隔(仮)
    time.reset();
    if(input.keyPush(DIK_Z)) {
        playerBulletManager->shot(getShotPosition(), hp);
           got::XAudio2::getInstance().play("Shot1");
    }
}
// 描画
void Player::draw() const
{
    //TODO:テスト
    auto mt         = got::Matrix4x4<float>::translate(position);
    auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();
    auto color      = got::Color<float>();
    auto drawRect   = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
    
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
    // 死亡時の処理
    if (hp <= 0) {
        got::Fade::getInstance().setIsFadeOut(true);
        Game::getInstance().setIsNextScene(true);
        got::XAudio2::getInstance().stopBGM();
    }
}
// プレイヤーのショットレベルを上げる
void Player::levelUp(const int _addLevel)
{
    hp += _addLevel;

    // HPの限界値の確認
    if (hp >= maxHp) {
        hp = maxHp;
        return;
    }
    got::XAudio2::getInstance().play("LevelUp");
}
// 弾を発射する座標を返す
const got::Vector2<float> Player::getShotPosition() const
{
    auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();
    return got::Vector2<float>(position.x + (spriteSize.width / 2.0f), position.y);
}
