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
    //TODO: 操作説明を描画
}

void OperatingScene::end()
{
}
