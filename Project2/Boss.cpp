//////////////////////////////////////////////////
// 作成日:2016/12/19
// 更新日:2016/1/25
// 制作者:got
//////////////////////////////////////////////////
#include "Boss.h"
#include "Game.h"
#include "EffectManager.h"
#include "ItemManager.h"

Boss::Boss()
    :Enemy(), subShotTimer()
{
}

Boss::~Boss()
{
}

bool Boss::init()
{

    if (!Enemy::init()) {
        return false;
    }

    spriteName = "Boss";
    hp = 200;
    color.WHITE;
    position.move(250.0f, -500.0f);
    setMovePattern(3);
    dx = 0.1f;
    dy = 0.1f;
    setShotPattern(3);
    bulletSpeed = 0.15f;
    shotInterval = 750.0f;
    score = 1000;
    subShotTimer.reset();
    rad = 64.0f;

    return true;
}

void Boss::move()
{
    if (state == STATE::UN_USE) { return; }

    auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();

    dTime = Game::getInstance().getDeltaTime();

    changeMove();

    // 移動
    this->moveFunc();
    checkMoveLimit();

    // ダメージ表現
    damageEffect();

    // 弾の発射
    if (time2.timeOver(shotInterval)) {
        this->shotFunc();
        time2.reset();
    }
    if (subShotTimer.timeOver(1000.0f)) {
        enemyBulletManager->shot2(getShotPosition(), 0.2f);
        subShotTimer.reset();
    }
}

void Boss::draw() const
{
    Enemy::draw();
}

void Boss::end()
{
}

void Boss::setDamage(const int damage)
{
    hp -= damage;
    color.a = 0.0f;
    // 死んでいる場合
    if (hp <= 0) {
        auto &game = Game::getInstance();

        state = STATE::UN_USE;
        game.addScore(score);
        EffectManager::getInstance().startEffect("Explosion", position);
        std::dynamic_pointer_cast<ItemManager>(game.getRootActor()->getChild(L"ItemManager"))->itemDrop(position);

        got::Fade::getInstance().setIsFadeOut(true);
        game.setIsNextScene(true);
    }
}

void Boss::changeMove()
{
    if (hp < 100) {
        setMovePattern(-1);
        setShotPattern(2);
    }
}

void Boss::checkMoveLimit()
{
    auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();
    if     (position.x < 0)                                { dx = -dx; }
    else if(position.x > STAGE_WIDTH - spriteSize.width)   { dx = -dx; }
    //if     (position.y < 0)                                { dy = -dy; }
    //else if(position.y > STAGE_HEIGHT - spriteSize.height) { dy = -dy; }
}
