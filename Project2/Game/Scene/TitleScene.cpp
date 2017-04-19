//////////////////////////////////////////////////
// 作成日:2016/10/18
// 更新日:2016/12/14
// 制作者:got
//////////////////////////////////////////////////
#include "TitleScene.h"
#include "..\..\got\Input\MyDirectInput.h"
#include "..\..\got\Utility\Fade.h"
#include "..\Common\Game.h"
#include "..\..\got\Audio\XAudio2.h"
#include "..\..\got\Math\MyAlgorithm.h"

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
    menuNum = 0;

    return true;
}
// 更新
void TitleScene::move()
{
    auto &di   = got::MyDirectInput::getInstance();
    auto &fade = got::Fade::getInstance();

    background->move();

    if (!fade.getIsFadeOut() && !fade.getIsFadeIn()) {
        auto spriteSize = got::SpriteManager::getInstance().getSprite("ChooseBar")->getSize();

        // 上が押された
        if (di.keyPressed(DIK_UP) || di.getStickPosY() == got::MyDirectInput::STICK_STATE::UP) {
            --menuNum;
            got::XAudio2::getInstance().play("MenuSelect");
            return;
        }
        // 下が押された
        else if (di.keyPressed(DIK_DOWN) || di.getStickPosY() == got::MyDirectInput::STICK_STATE::DOWN) {
            ++menuNum;
            got::XAudio2::getInstance().play("MenuSelect");
            return;
        }
        menuNum = got::MyAlgorithm::rollup(menuNum, 2);
        choosePos.move(static_cast<float>(WINDOW_WIDTH / 2 - spriteSize.width / 2), 500.0f + menuNum * 100.0f);

        // 決定キー
        if (di.keyPressed(DIK_RETURN) || di.buttonPressed(0)) {
            got::XAudio2::getInstance().play("Enter");
            fade.setIsFadeOut(true);
        }
    }
    if (fade.getIsFadeOut()) {
        switch (menuNum) {
        case 0:
            fade.fadeOut(SceneManager::SCENE_NAME::MAIN);
            break;
        case 1:
            fade.fadeOut(SceneManager::SCENE_NAME::OPERATING);
            break;
        case 2:
            Game::getInstance().setIsRun(false);
            break;
        default:
            //TODO: assertを実装
            break;
        }
    }
}
// 描画
void TitleScene::draw() const
{
	auto &sm   = got::SpriteManager::getInstance();
	
    background->draw();

    // タイトルロゴ
    auto mt       = got::Matrix4x4<float>::translate(got::Vector2<float>(200.0f, position.y + 50.0f));
    auto drawRect = got::Rectangle<int>(got::Vector2<int>(sm.getSprite("TitleName")->getSize().width, sm.getSprite("TitleName")->getSize().height));
    got::SpriteManager::getInstance().draw("TitleName", mt, drawRect, color);

    // 選択しているメニューを強調するバー
    mt       = got::Matrix4x4<float>::translate(choosePos);
    drawRect = got::Rectangle<int>(got::Vector2<int>(sm.getSprite("ChooseBar")->getSize().width, sm.getSprite("ChooseBar")->getSize().height));
    sm.draw("ChooseBar", mt, drawRect, color);

    // Start(スタート)
	mt       = got::Matrix4x4<float>::translate(static_cast<float>(WINDOW_WIDTH / 2 - sm.getSprite("Start")->getSize().width / 2), 500.0f);
	drawRect = got::Rectangle<int>(got::Vector2<int>(sm.getSprite("Start")->getSize().width, sm.getSprite("Start")->getSize().height));
	sm.draw("Start", mt, drawRect, color);

    // Operating(操作説明)
    mt       = got::Matrix4x4<float>::translate(static_cast<float>(WINDOW_WIDTH / 2 - sm.getSprite("Operating")->getSize().width / 2), 600.0f);
	drawRect = got::Rectangle<int>(got::Vector2<int>(sm.getSprite("Operating")->getSize().width, sm.getSprite("Operating")->getSize().height));
	sm.draw("Operating", mt, drawRect, color);

    // Exit(終了)
    mt       = got::Matrix4x4<float>::translate(static_cast<float>(WINDOW_WIDTH / 2 - sm.getSprite("Exit")->getSize().width / 2), 700.0f);
    drawRect = got::Rectangle<int>(got::Vector2<int>(sm.getSprite("Exit")->getSize().width, sm.getSprite("Exit")->getSize().height));
    sm.draw("Exit", mt, drawRect, color);
}
// 終了
void TitleScene::end()
{
    background->end();
}
