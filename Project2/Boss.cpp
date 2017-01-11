//////////////////////////////////////////////////
// 作成日:2016/12/19
// 更新日:2016/1/11
// 制作者:got
//////////////////////////////////////////////////
#include "Boss.h"
#include "Game.h"

Boss::Boss()
    :Enemy()
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
    color.WHITE;

    return true;
}

void Boss::move()
{
    if (state == STATE::UN_USE) { return; }

    auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();

    dTime = Game::getInstance().getDeltaTime();

    // 移動
    this->moveFunc();

    // ダメージ表現
    damageEffect();

    // 弾の発射
    if (time2.timeOver(shotInterval)) {
        this->shotFunc();
        time2.reset();
    }
}

void Boss::draw() const
{
    Enemy::draw();
}

void Boss::end()
{
}
