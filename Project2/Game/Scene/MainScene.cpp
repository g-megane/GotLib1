//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/1/11
// 制作者:got
//////////////////////////////////////////////////
#include "MainScene.h"
#include "SceneManager.h"
#include "..\Actor\Boss.h"
#include "..\Actor\Player.h"
#include "..\UI\Information.h"
#include "..\Common\Game.h"
#include "..\Common\Fade.h"
#include "..\Effect\EffectManager.h"
#include "..\Common\Controller.h"
#include "..\..\got\Audio\XAudio2.h"

// コンストラクタ
MainScene::MainScene()
{
	rootActor  = Game::getInstance().getRootActor();
    backGround = std::make_shared<BackGround>("Background");
   
    std::shared_ptr<Actor> info = std::make_shared<Information>();

    rootActor->addChild(info);
}
// デストラクタ
MainScene::~MainScene()
{
}
// 初期化
bool MainScene::init()
{
    // 先頭のメインシーンだけでいい(Stage1のこと)
    Game::getInstance().resetScore();
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
    em->readFile("Resources\\Data\\EnemyData1.csv");
   
    got::XAudio2::getInstance().playBGM("Stage");
    EffectManager::getInstance().init();

    return true;
}

// 更新
void MainScene::move()
{
    // Pキーが押された
    auto &input = Controller::getInstance();
    auto &game  = Game::getInstance();
    auto &fade  = got::Fade::getInstance();

    if (!fade.getIsFadeOut() && !fade.getIsFadeIn()) {
        if (input.pause()) {
            got::XAudio2::getInstance().play("Enter");
            game.setIsPause(true);
            fade.setIsFadeOut(true);
        }
    }

    if (fade.getIsFadeOut()) {
        // 次のシーンへの遷移の場合
        if (game.getIsNextScene()) {
            // プレイヤーが死んでいる場合
            if (std::dynamic_pointer_cast<Player>(game.getRootActor()->getChild(L"Player"))->getHp() <= 0) {
                got::XAudio2::getInstance().stopBGM();
                fade.fadeOut(SceneManager::SCENE_NAME::RESULT);
                // EnemyManagerのchildからBossを削除
                std::dynamic_pointer_cast<EnemyManager>(game.getRootActor()->getChild(L"EnemyManager"))->eraseBoss();
                return;
            }
            // クリアの場合
            else {
                got::XAudio2::getInstance().stopBGM();
                fade.fadeOut(SceneManager::SCENE_NAME::MAIN2);
                // EnemyManagerのchildからBossを削除
                std::dynamic_pointer_cast<EnemyManager>(game.getRootActor()->getChild(L"EnemyManager"))->eraseBoss();
                return;
            }
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
void MainScene::draw() const
{
    backGround->draw();
    rootActor->draw();
    EffectManager::getInstance().draw();
}
// 終了
void MainScene::end()
{
   backGround->end();
   rootActor->end();
}
