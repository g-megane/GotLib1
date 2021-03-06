﻿//////////////////////////////////////////////////
// 作成日:2016/10/18
// 更新日:2016/12/14
// 制作者:got
//////////////////////////////////////////////////
#include "TitleScene.h"
#include "..\Common\Fade.h"
#include "..\Common\Game.h"
#include "..\..\got\Input\MyDirectInput.h"
#include "..\..\got\Audio\XAudio2.h"
#include "..\..\got\Math\MyAlgorithm.h"
#include "..\..\got\Input\MyXInput.h"

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
    auto &xi   = got::MyXInput::getInstance();
    auto &fade = got::Fade::getInstance();

    // 背景の更新
    background->move();

    // メニューの更新
    if (!fade.getIsFadeOut() && !fade.getIsFadeIn()) {
        auto spriteSize = got::SpriteManager::getInstance().getSprite("ChooseBar")->getSize();
        // 上が押された
        if (di.keyPressed(DIK_UP) || xi.isPadUp(0)) {
            --menuNum;
            got::XAudio2::getInstance().play("MenuSelect");
        }
        // 下が押された
        else if (di.keyPressed(DIK_DOWN) || xi.isPadDown(0)) { 
            ++menuNum;
            got::XAudio2::getInstance().play("MenuSelect");
        }

        menuNum = got::MyAlgorithm::rollup(menuNum, 2);
        choosePos.move(static_cast<float>(WINDOW_WIDTH / 2 - spriteSize.width / 2), static_cast<float>(500.0f + menuNum * 100.0f));

        // 決定キー
        if (di.keyPressed(DIK_RETURN) || xi.isButtonPressed(0, XINPUT_GAMEPAD_A)) {
            got::XAudio2::getInstance().play("Enter");
            fade.setIsFadeOut(true);
        }
    }
    if (fade.getIsFadeOut()) {
        switch (menuNum) {
        // ゲームスタート
        case 0:
            fade.fadeOut(SceneManager::SCENE_NAME::MAIN);
            break;
        // 操作説明シーン
        case 1:
            fade.fadeOut(SceneManager::SCENE_NAME::OPERATING);
            break;
        // ゲームを終了
        case 2:
            Game::getInstance().setIsRun(false);
            break;
        // 存在しないメニュー番号が選択されている
        default:
            assert(!"TitleScene::move()で不正な値");
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
