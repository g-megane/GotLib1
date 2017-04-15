//////////////////////////////////////////////////
// 作成日:2016/11/9
// 更新日:2016/11/13
// 制作者:got
//////////////////////////////////////////////////
#include "BackGround.h"
#include "..\..\got\Math\Matrix4x4.h"
#include "..\..\got\Utility\SpriteManager.h"
#include "GV.h"
#include "Game.h"

// コンストラクタ
BackGround::BackGround(const std::string& _spriteName)
{
    spriteName = _spriteName;
}
// デストラクタ
BackGround::~BackGround()
{
}
// 初期化
bool BackGround::init()
{
    position.ZERO;
    dx = 0.0f;
    dy = 0.05f;
    color.WHITE;

    return true;
}
// 更新
void BackGround::move()
{
    const auto dTime = Game::getInstance().getDeltaTime();
    position.translate(dx * dTime, dy * dTime);
    auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();

    if (position.x > 0) {
        position.x -= spriteSize.width;
    }
    if (position.y > 0) {
        position.y -= spriteSize.height;
    }
}
// 描画
void BackGround::draw() const
{
    auto mt         = got::Matrix4x4<float>().translate(position);
    auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();
    auto drawRect   = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
    
    for (float y = position.y; y < WINDOW_HEIGHT; y += spriteSize.height) {
        for (float x = position.x; x < WINDOW_WIDTH; x += spriteSize.width) {
            mt = got::Matrix4x4<float>().translate(x, y);
            got::SpriteManager::getInstance().draw(spriteName, mt, drawRect, color);
        }
    }
}
// 終了
void BackGround::end()
{
}
