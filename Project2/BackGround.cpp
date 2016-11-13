//////////////////////////////////////////////////
// 作成日:2016/11/9
// 更新日:2016/11/13
// 制作者:got
//////////////////////////////////////////////////
#include "BackGround.h"
#include "Matrix4x4.h"
#include "SpriteManager.h"
#include "GV.h"

// コンストラクタ
BackGround::BackGround()
{
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
    dy = 1.0f;
    return true;
}
// 更新
void BackGround::move()
{
    position.translate(dx, dy);
    auto spriteSize = got::SpriteManager::getInstance().getSprite("BackGround")->getSize();

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
    auto mt = got::Matrix4x4<float>().translate(position);
    auto spriteSize = got::SpriteManager::getInstance().getSprite("BackGround")->getSize();
    auto color = got::Color<float>();
    auto drawRect = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
    
    for (float y = position.y; y < STAGE_HEIGHT; y += spriteSize.height) {
        for (float x = position.x; x < STAGE_WIDTH; x += spriteSize.width) {
            mt = got::Matrix4x4<float>().translate(x, y);
            got::SpriteManager::getInstance().draw("BackGround", mt, drawRect, color);
        }
    }
}
// 終了
void BackGround::end()
{
}
