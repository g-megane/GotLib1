//////////////////////////////////////////////////
// 作成日:2016/10/18
// 更新日:2016/12/14
// 制作者:got
//////////////////////////////////////////////////
#include "TitleScene.h"
#include "MyDirectInput.h"
#include "Fade.h"
#include "Game.h"
#include "XAudio2.h"

// コンストラクタ
TitleScene::TitleScene()
{
    background = std::make_shared<BackGround>("Background");
}
// デストラクタ
TitleScene::~TitleScene()
{
}
// 初期化
bool TitleScene::init()
{
    if (!background->init()) {
        return false;
    }
    
    auto &sm = got::SpriteManager::getInstance();
	position.ZERO;
    color.WHITE;
    choosePos.move(static_cast<float>(WINDOW_WIDTH / 2 - sm.getSprite("ChooseBar")->getSize().width / 2), 500.0f);
    canSelectDown = true;

    return true;
}
// 更新
void TitleScene::move()
{
    auto &di   = got::MyDirectInput::getInstance();
    auto &fade = got::Fade::getInstance();

    background->move();

    // 選択
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
        }
    }
    if (fade.getIsFadeOut()) {
        fade.fadeOut(choosePos.y <= 550.0f ? SceneManager::SCENE_NAME::MAIN : SceneManager::SCENE_NAME::OPERATING);
    }
}
// 描画
void TitleScene::draw() const
{
	auto &sm   = got::SpriteManager::getInstance();
	
    background->draw();

    //TODO: タイトルロゴを作って表示
    auto mt       = got::Matrix4x4<float>::translate(got::Vector2<float>(200.0f, position.y + 50.0f));
    auto drawRect = got::Rectangle<int>(got::Vector2<int>(sm.getSprite("TitleName")->getSize().width, sm.getSprite("TitleName")->getSize().height));
    got::SpriteManager::getInstance().draw("TitleName", mt, drawRect, color);

    // 選択しているメニューを強調するバー
    mt       = got::Matrix4x4<float>::translate(choosePos);
    drawRect = got::Rectangle<int>(got::Vector2<int>(sm.getSprite("ChooseBar")->getSize().width, sm.getSprite("ChooseBar")->getSize().height));
    sm.draw("ChooseBar", mt, drawRect, color);

    // スタート
	mt       = got::Matrix4x4<float>::translate(static_cast<float>(WINDOW_WIDTH / 2 - sm.getSprite("Start")->getSize().width / 2), 500.0f);
	drawRect = got::Rectangle<int>(got::Vector2<int>(sm.getSprite("Start")->getSize().width, sm.getSprite("Start")->getSize().height));
	sm.draw("Start", mt, drawRect, color);

    // 操作説明
    mt       = got::Matrix4x4<float>::translate(static_cast<float>(WINDOW_WIDTH / 2 - sm.getSprite("Operating")->getSize().width / 2), 600.0f);
	drawRect = got::Rectangle<int>(got::Vector2<int>(sm.getSprite("Operating")->getSize().width, sm.getSprite("Operating")->getSize().height));
	sm.draw("Operating", mt, drawRect, color);
}
// 終了
void TitleScene::end()
{
    background->end();
}
