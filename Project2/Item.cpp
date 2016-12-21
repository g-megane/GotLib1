//////////////////////////////////////////////////
// 作成日:2016/12/21
// 更新日:2016/12/21
// 制作者:got
//////////////////////////////////////////////////
#include "Item.h"
#include "SpriteManager.h"
#include "Game.h"

// コンストラクタ
Item::Item()
    : Actor()
{
}
// デストラクタ
Item::~Item()
{
}
// 初期化
bool Item::init()
{
    state = STATE::UN_USE;
    
    dy = -0.2f;
    position.ZERO;
    spriteName = "Result";
    rad = got::SpriteManager::getInstance().getSprite(spriteName)->getSize().width / 2;

    return true;
}
// 移動
void Item::move()
{
    if (state == STATE::UN_USE) { return; }

    position.y += dy * Game::getInstance().getDeltaTime();
    dy += 0.0025f;

    //TODO: StageのBottomより下に行ったらstateをUN_USEに
    if (position.y > STAGE_HEIGHT) { state = STATE::UN_USE; }
}
// 描画
void Item::draw() const
{
    if (state == STATE::UN_USE) { return; }

    auto & spriteManager = got::SpriteManager::getInstance();
    auto mt       = got::Matrix4x4<float>::translate(position);
    auto color    = got::Color<float>();
    auto drawRect = got::Rectangle<int>(got::Vector2<int>(spriteManager.getSprite(spriteName)->getSize().width, spriteManager.getSprite(spriteName)->getSize().height));

    got::SpriteManager::getInstance().draw(spriteName, mt, drawRect, color);
}
// 終了
void Item::end()
{
}

void Item::drop(const got::Vector2<float>& dropPos)
{
    position = dropPos;
    dy = -0.2f;

    state = STATE::USE;
}
