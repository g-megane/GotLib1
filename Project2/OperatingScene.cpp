//////////////////////////////////////////////////
// 作成日:2016/12/14
// 更新日:2016/12/14
// 制作者:got
//////////////////////////////////////////////////
#include "OperatingScene.h"
#include "MyDirectInput.h"
#include "Fade.h"

OperatingScene::OperatingScene()
{
}

OperatingScene::~OperatingScene()
{
}

bool OperatingScene::init()
{
    return true;
}

void OperatingScene::move()
{
    auto &fade = got::Fade::getInstance();
    if (got::MyDirectInput::getInstance().keyTrigger(DIK_RETURN)) {
        fade.setIsFadeOut(true);
    }
    if (fade.getIsFadeOut()) {
        fade.fadeOut(SceneManager::SCENE_NAME::TITLE);
    }
}

void OperatingScene::draw() const
{
    auto mt = got::Matrix4x4<float>::translate(position.ZERO);
    auto spriteSize = got::SpriteManager::getInstance().getSprite("Board")->getSize();
    auto color = got::Color<float>::WHITE;
    auto drawRect = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
    got::SpriteManager::getInstance().draw("Board", mt, drawRect, color);

    spriteSize = got::SpriteManager::getInstance().getSprite("OperatingMenu")->getSize();
    drawRect   = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
    got::SpriteManager::getInstance().draw("OperatingMenu", mt, drawRect, color);
}

void OperatingScene::end()
{
}
