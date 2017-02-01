//////////////////////////////////////////////////
// 作成日:2016/11/30
// 更新日:2016/11/30
// 制作者:got
//////////////////////////////////////////////////
#include "PauseScene.h"
#include "SceneManager.h"
#include "MyDirectInput.h"
#include "Game.h"
#include "XAudio2.h"

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
    if (!background->init()) {
        return false;
    }

    auto &sm = got::SpriteManager::getInstance();
    position.ZERO;
    choosePos.move(static_cast<float>(WINDOW_WIDTH / 2 - sm.getSprite("ChooseBar")->getSize().width / 2), 500.0f);
    canSelectDown = false;

    return true;
}
// 更新
void PauseScene::move()
{
    background->move();

    // 選択
    auto &di   = got::MyDirectInput::getInstance();
    auto &fade = got::Fade::getInstance();
    if (!fade.getIsFadeOut() && !fade.getIsFadeIn()) {
        auto spriteSize = got::SpriteManager::getInstance().getSprite("ChooseBar")->getSize();
        if (di.keyPressed(DIK_UP) || di.getStickPosY() == got::MyDirectInput::STICK_STATE::UP) {
            if (!canSelectDown) { got::XAudio2::getInstance().play("MenuSelect"); }
            choosePos.move(static_cast<float>(WINDOW_WIDTH / 2 - spriteSize.width / 2), 500.0f);
            canSelectDown = true;
            return;
        }
        else if (di.keyPressed(DIK_DOWN) || di.getStickPosY() == got::MyDirectInput::STICK_STATE::DOWN) {
            if (canSelectDown) { got::XAudio2::getInstance().play("MenuSelect"); };
            choosePos.move(static_cast<float>(WINDOW_WIDTH / 2 - spriteSize.width / 2), 600.0f);
            canSelectDown = false;
            return;
        }
        // シーン遷移(TITLE->MAIN or TITLE->OPERATING)
        if (di.keyPressed(DIK_RETURN) || di.buttonPressed(0)) {
            got::XAudio2::getInstance().play("Enter");
            fade.setIsFadeOut(true);
            Game::getInstance().setIsPause(false);
        }
    }

    if (fade.getIsFadeOut()) {
        if (choosePos.y <= 550.0f) {
            fade.fadeOut(SceneManager::getInstance().getBeforeSceneName(), false);
        }
        else {
            got::XAudio2::getInstance().stopBGM();
            fade.fadeOut(SceneManager::SCENE_NAME::TITLE);
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
