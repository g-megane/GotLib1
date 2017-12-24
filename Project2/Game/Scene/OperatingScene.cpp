//////////////////////////////////////////////////
// 作成日:2016/12/14
// 更新日:2016/1/18
// 制作者:got
//////////////////////////////////////////////////
#include "OperatingScene.h"
#include "..\Common\Fade.h"
#include "..\..\got\Input\MyDirectInput.h"
#include "..\..\got\Audio\XAudio2.h"
#include "..\..\got\Input\MyXInput.h"

OperatingScene::OperatingScene()
{
    background = std::make_shared<BackGround>("Background");
}

OperatingScene::~OperatingScene()
{
}

bool OperatingScene::init()
{
    color.WHITE;

    if (!background->init()) {
        return false;
    }

    return true;
}

void OperatingScene::move()
{
    background->move();

    auto &fade  = got::Fade::getInstance();
    auto &input = got::MyDirectInput::getInstance();
    auto &xInput = got::MyXInput::getInstance();

    if (!fade.getIsFadeOut() && !fade.getIsFadeIn()) {
        if (input.keyPressed(DIK_RETURN) || xInput.isButtonPressed(0, XINPUT_GAMEPAD_A)) {
            got::XAudio2::getInstance().play("Enter");
            fade.setIsFadeOut(true);
        }
    }
    if (fade.getIsFadeOut()) {
        fade.fadeOut(SceneManager::SCENE_NAME::TITLE);
    }
}

void OperatingScene::draw() const
{
    background->draw();

    auto mt = got::Matrix4x4<float>::translate(position.ZERO);
    auto spriteSize = got::SpriteManager::getInstance().getSprite("OperatingMenu")->getSize();
    auto drawRect   = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
    got::SpriteManager::getInstance().draw("OperatingMenu", mt, drawRect, color);
}

void OperatingScene::end()
{
    background->end();
}
