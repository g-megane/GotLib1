//////////////////////////////////////////////////
// 作成日:2016/12/19
// 更新日:2016/1/11
// 制作者:got
//////////////////////////////////////////////////
#include "Boss.h"
#include "Game.h"
#include "EffectManager.h"
#include "ItemManager.h"

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

    spriteName = "Boss";
    hp = 100;
    color.WHITE;
    position.move(250.0f, -64.0f);
    setMovePattern(3);
    dx = 0.1f;
    dy = 0.1f;
    setShotPattern(4);
    bulletSpeed = 0.1f;
    shotInterval = 50.0f;
    score = 1000;
    rad = static_cast<float>(got::SpriteManager::getInstance().getSprite(spriteName)->getSize().width);

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
