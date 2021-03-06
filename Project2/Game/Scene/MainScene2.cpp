﻿//////////////////////////////////////////////////
// 作成日:2016/1/30
// 更新日:2016/1/30
// 制作者:got
//////////////////////////////////////////////////
#include "MainScene2.h"
#include "SceneManager.h"
#include "..\UI\Information.h"
#include "..\Actor\Boss.h"
#include "..\Common\Game.h"
#include "..\Common\Fade.h"
#include "..\Effect\EffectManager.h"
#include "..\..\got\Input\MyDirectInput.h"
#include "..\..\got\Input\MyXInput.h"
#include "..\..\got\Audio\XAudio2.h"

// コンストラクタ
MainScene2::MainScene2()
{
    rootActor = Game::getInstance().getRootActor();
    backGround = std::make_shared<BackGround>("Background1");

    //TODO:とりあえず10体を使いまわし
    //enemyManager = std::make_shared<EnemyManager>(10);
    //std::shared_ptr<Actor> info = std::make_shared<Information>();

    // ここの順番大事！！
    //rootActor->addChild(enemyManager);
    //rootActor->addChild(info);
}
// デストラクタ
MainScene2::~MainScene2()
{
}
// 初期化
bool MainScene2::init()
{
    // 先頭のメインシーンだけでいい(Stage1のこと)
    //Game::getInstance().resetScore();
    Game::getInstance().setIsNextScene(false);

    auto em = std::dynamic_pointer_cast<EnemyManager>(Game::getInstance().getRootActor()->getChild(L"EnemyManager"));
    em->init();

    if (!backGround->init()) {
        return false;
    }

    if (!rootActor->init()) {
        return false;
    }

    // Enemyのデータの読み込み
    em->readFile("Resources\\Data\\EnemyData2.csv");

    got::XAudio2::getInstance().playBGM("Stage");
    EffectManager::getInstance().init();

    return true;
}

// 更新
void MainScene2::move()
{
    // Pキーが押された
    auto &di = got::MyDirectInput::getInstance();
    auto &xi = got::MyXInput::getInstance();
    auto &game  = Game::getInstance();
    auto &fade  = got::Fade::getInstance();

    if (!fade.getIsFadeOut() && !fade.getIsFadeIn()) {
        if (di.keyPressed(DIK_P) || xi.isButtonPressed(0, XINPUT_GAMEPAD_START)) {
            got::XAudio2::getInstance().play("Enter");
            game.setIsPause(true);
            fade.setIsFadeOut(true);
        }
    }

    if (fade.getIsFadeOut()) {
        // 次のシーンへの遷移の場合
        if (game.getIsNextScene()) {
            got::XAudio2::getInstance().stopBGM();
            fade.fadeOut(SceneManager::SCENE_NAME::RESULT);
            std::dynamic_pointer_cast<EnemyManager>(Game::getInstance().getRootActor()->getChild(L"EnemyManager"))->eraseBoss();
            return;
        }
        // ポーズシーンへの遷移の場合
        else {
            fade.fadeOut(SceneManager::SCENE_NAME::PAUSE);
            return;
        }
    }

    backGround->move();
    rootActor->move();
    EffectManager::getInstance().move();

}
// 描画
void MainScene2::draw() const
{
    backGround->draw();
    rootActor->draw();
    EffectManager::getInstance().draw();
}
// 終了
void MainScene2::end()
{
    backGround->end();
    rootActor->end();
}
