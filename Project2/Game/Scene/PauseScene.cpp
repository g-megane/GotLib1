//////////////////////////////////////////////////
// 作成日:2016/11/30
// 更新日:2016/11/30
// 制作者:got
//////////////////////////////////////////////////
#include "PauseScene.h"
#include "SceneManager.h"
#include "..\Common\Game.h"
#include "..\..\got\Input\MyDirectInput.h"
#include "..\..\got\Input\MyXInput.h"
#include "..\..\got\Audio\XAudio2.h"
#include "..\..\got\Math\MyAlgorithm.h"

// コンストラクタ
PauseScene::PauseScene()
{
    background = std::make_shared<BackGround>("Background");
}
// デストラクタ
PauseScene::~PauseScene()
{
}

// 初期化
bool PauseScene::init()
{
    auto &sm = got::SpriteManager::getInstance();
    position.ZERO;
    choosePos.move(static_cast<float>(WINDOW_WIDTH / 2 - sm.getSprite("ChooseBar")->getSize().width / 2), 500.0f);
    canSelectDown = false;
    menuNum = 0;
    
    got::MyXInput::getInstance().setRightVibration(0, 0);

    if (!background->init()) {
        return false;
    }

    return true;
}
// 更新
void PauseScene::move()
{
    background->move();

    // 選択
    //TODO: Xinputに変更
    auto &di   = got::MyDirectInput::getInstance();
    auto &xi   = got::MyXInput::getInstance();
    auto &fade = got::Fade::getInstance();

    if (!fade.getIsFadeOut() && !fade.getIsFadeIn()) {
        auto spriteSize = got::SpriteManager::getInstance().getSprite("ChooseBar")->getSize();
        if (di.keyPressed(DIK_UP) || xi.isPadUp(0)) {
            --menuNum;
            got::XAudio2::getInstance().play("MenuSelect");
            return;
        }
        else if (di.keyPressed(DIK_DOWN) || xi.isPadDown(0)) {
            ++menuNum;
            got::XAudio2::getInstance().play("MenuSelect");
            return;
        }

        menuNum = got::MyAlgorithm::rollup(menuNum, 1);
        choosePos.move(static_cast<float>(WINDOW_WIDTH / 2 - spriteSize.width / 2), 500.0f + menuNum * 100.0f);

        // シーン遷移(TITLE->MAIN or TITLE->OPERATING)
        if (di.keyPressed(DIK_RETURN) || xi.isButtonPressed(0, XINPUT_GAMEPAD_A)) {
            got::XAudio2::getInstance().play("Enter");
            fade.setIsFadeOut(true);
            Game::getInstance().setIsPause(false);
        }
    }

    if (fade.getIsFadeOut()) {
        switch (menuNum) {
        case 0:
            fade.fadeOut(SceneManager::getInstance().getBeforeSceneName(), false);
            break;
        case 1:
            got::XAudio2::getInstance().stopBGM();
            fade.fadeOut(SceneManager::SCENE_NAME::TITLE);
            break;
        default:
            assert(!"PauseSceneMove()で不正な値");
            break;
        }
    }
}

// 描画
void PauseScene::draw() const
{
    background->draw();

    // 選択しているメニューを強調するバー
    auto &sm = got::SpriteManager::getInstance();
    auto mt = got::Matrix4x4<float>::translate(choosePos);
    auto drawRect = got::Rectangle<int>(got::Vector2<int>(sm.getSprite("ChooseBar")->getSize().width, sm.getSprite("ChooseBar")->getSize().height));
    sm.draw("ChooseBar", mt, drawRect, color);

    // スタート
    mt = got::Matrix4x4<float>::translate(static_cast<float>(WINDOW_WIDTH / 2 - sm.getSprite("Start")->getSize().width / 2), 500.0f);
    drawRect = got::Rectangle<int>(got::Vector2<int>(sm.getSprite("Start")->getSize().width, sm.getSprite("Start")->getSize().height));
    sm.draw("Start", mt, drawRect, color);

    // 操作説明
    mt = got::Matrix4x4<float>::translate(static_cast<float>(WINDOW_WIDTH / 2 - sm.getSprite("Title")->getSize().width / 2), 600.0f);
    drawRect = got::Rectangle<int>(got::Vector2<int>(sm.getSprite("Title")->getSize().width, sm.getSprite("Title")->getSize().height));
    sm.draw("Title", mt, drawRect, color);
}
// 終了
void PauseScene::end()
{
    background->end();
}
