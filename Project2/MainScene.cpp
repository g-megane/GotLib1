//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/1/11
// 制作者:got
//////////////////////////////////////////////////
#include "MainScene.h"
#include "Game.h"
#include "Information.h"
#include "MyDirectInput.h"
#include "SceneManager.h"
#include "Fade.h"
#include "XAudio2.h"
#include "EffectManager.h"
#include "Boss.h"
#include "Player.h"

// コンストラクタ
MainScene::MainScene()
{
	rootActor  = Game::getInstance().getRootActor();
    backGround = std::make_shared<BackGround>("Background");
   
    //TODO:とりあえず10体を使いまわし
    //enemyManager = std::make_shared<EnemyManager>(10);
    std::shared_ptr<Actor> info = std::make_shared<Information>();

    // ここの順番大事！！
    //rootActor->addChild(enemyManager);
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
    em->readFile("Resources\\Data\\DebugData.csv");
    
    //TODO:仮データ
    //TODO:出現位置は定数にするのが有かも？
    // ・出現時間を0にするとひとつ前の敵と同時に出現する
    // ・移動パターンの6と7は移動量(X)を0にしてやる必要がある
    //------------------------------------------------ [エネミーデータのセット] ----------------------------------------------------------------------------------------------------
    //-------- {出現時間} - {スプライト名} - {HP} --- {スプライトの色｝--- {出現座標(x)} ------- {出現座標(y)} -- {移動パターン} -{移動量(x)} - {移動量(y)} - {攻撃パターン} -- {弾速} -- {発射間隔} - {持ち点}
    //em->setEnemy(3000.0f,    "Enemy",       3,        color,            STAGE_WIDTH - 128.0f,  50.0f,           0,            0.2f,         0.15f,        0,            0.3f,      500.0f,     100);
    //em->setEnemy(1000.0f,    "Enemy",       3,        color,            STAGE_WIDTH - 128.0f,  50.0f,           0,            0.2f,         0.15f,        0,            0.3f,      500.0f,     100);
    //em->setEnemy(1000.0f,    "Enemy",       3,        color,            STAGE_WIDTH - 128.0f,  50.0f,           0,            0.2f,         0.15f,        0,            0.3f,      500.0f,     100);
    //em->setEnemy(2000.0f,    "Enemy",       3,        color,                    20.0f,         50.0f,           0,            0.2f,         0.15f,        0,            0.3f,      500.0f,     100);
    //em->setEnemy(1000.0f,    "Enemy",       3,        color,                    20.0f,         50.0f,           0,            0.2f,         0.15f,        0,            0.3f,      500.0f,     100);
    //em->setEnemy(1000.0f,    "Enemy",       3,        color,                    20.0f,         50.0f,           0,            0.2f,         0.15f,        0,            0.3f,      500.0f,     100);
    //em->setEnemy(3000.0f,    "Enemy",       3,        color,            STAGE_WIDTH - 128.0f,  50.0f,           6,            0.0f,         0.15f,        0,            0.3f,      500.0f,     100);
    //em->setEnemy(1000.0f,    "Enemy",       3,        color,            STAGE_WIDTH - 128.0f,  50.0f,           6,            0.0f,         0.15f,        0,            0.3f,      500.0f,     100);
    //em->setEnemy(1000.0f,    "Enemy",       3,        color,            STAGE_WIDTH - 128.0f,  50.0f,           6,            0.0f,         0.15f,        0,            0.3f,      500.0f,     100);
    //em->setEnemy(2000.0f,    "Enemy",       3,        color,                    20.0f,         50.0f,           7,            0.0f,         0.15f,        0,            0.3f,      500.0f,     100);
    //em->setEnemy(1000.0f,    "Enemy",       3,        color,                    20.0f,         50.0f,           7,            0.0f,         0.15f,        0,            0.3f,      500.0f,     100);
    //em->setEnemy(1000.0f,    "Enemy",       3,        color,                    20.0f,         50.0f,           7,            0.0f,         0.15f,        0,            0.3f,      500.0f,     100);
    //em->setEnemy(3000.0f,    "Enemy",       3,        color,            STAGE_WIDTH - 128.0f,  50.0f,           4,            0.1f,         0.15f,        0,            0.3f,      500.0f,     100);
    //em->setEnemy(1000.0f,    "Enemy",       3,        color,            STAGE_WIDTH - 128.0f,  50.0f,           4,            0.1f,         0.15f,        0,            0.3f,      500.0f,     100);
    //em->setEnemy(1000.0f,    "Enemy",       3,        color,            STAGE_WIDTH - 128.0f,  50.0f,           4,            0.1f,         0.15f,        0,            0.3f,      500.0f,     100);
    //em->setEnemy(2000.0f,    "Enemy",       3,        color,                    20.0f,         50.0f,           5,            0.1f,         0.15f,        0,            0.3f,      500.0f,     100);
    //em->setEnemy(1000.0f,    "Enemy",       3,        color,                    20.0f,         50.0f,           5,            0.1f,         0.15f,        0,            0.3f,      500.0f,     100);
    //em->setEnemy(1000.0f,    "Enemy",       3,        color,                    20.0f,         50.0f,           5,            0.1f,         0.15f,        0,            0.3f,      500.0f,     100);
    //em->setEnemy(3000.0f,    "Enemy",       5,        color,                    20.0f,         50.0f,           3,            0.1f,         0.15f,        2,            0.2f,      750.0f,     100);
    //em->setEnemy(1000.0f,    "Enemy",       3,        color,            STAGE_WIDTH / 2.0f,    50.0f,           1,            0.1f,         0.15f,        0,            0.2f,      500.0f,     100);
    //em->setEnemy(1000.0f,    "Enemy",       3,        color,            STAGE_WIDTH / 2.0f,    50.0f,           1,            0.1f,         0.15f,        0,            0.2f,      500.0f,     100);
    //em->setEnemy(1000.0f,    "Enemy",       3,        color,            STAGE_WIDTH / 2.0f,    50.0f,           1,            0.1f,         0.15f,        0,            0.2f,      500.0f,     100);
    //em->setEnemy(3000.0f,    "Enemy",       10,       color,            STAGE_WIDTH - 128.0f,  50.0f,           3,            0.1f,         0.15f,        2,            0.2f,      250.0f,     100);
    //em->setEnemy(4000.0f,    "Enemy",       3,        color,            STAGE_WIDTH / 2.0f,    50.0f,           2,            0.1f,         0.15f,        0,            0.2f,      500.0f,     100);
    //em->setEnemy(1000.0f,    "Enemy",       3,        color,            STAGE_WIDTH / 2.0f,    50.0f,           2,            0.1f,         0.15f,        0,            0.2f,      500.0f,     100);
    //em->setEnemy(1000.0f,    "Enemy",       3,        color,            STAGE_WIDTH / 2.0f,    50.0f,           2,            0.1f,         0.15f,        0,            0.2f,      500.0f,     100,       true);
    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
    got::XAudio2::getInstance().playBGM("Stage");
    EffectManager::getInstance().init();

    return true;
}

// 更新
void MainScene::move()
{
    // Pキーが押された
    auto &input = got::MyDirectInput::getInstance();
    auto &game = Game::getInstance();
    if (input.keyPressed(DIK_P) || input.buttonPressed(7)) {
        game.setIsPause(true);
        got::Fade::getInstance().setIsFadeOut(true);
    }

    if (got::Fade::getInstance().getIsFadeOut()) {
        // 次のシーンへの遷移の場合
        if (game.getIsNextScene()) {
            // プレイヤーが死んでいる場合
            if (std::dynamic_pointer_cast<Player>(game.getRootActor()->getChild(L"Player"))->getHp() <= 0) {
                got::XAudio2::getInstance().stopBGM();
                got::Fade::getInstance().fadeOut(SceneManager::SCENE_NAME::RESULT);
                // EnemyManagerのchildからBossを削除
                std::dynamic_pointer_cast<EnemyManager>(game.getRootActor()->getChild(L"EnemyManager"))->eraseBoss();
                return;
            }
            // クリアの場合
            else {
                got::XAudio2::getInstance().stopBGM();
                got::Fade::getInstance().fadeOut(SceneManager::SCENE_NAME::MAIN2);
                // EnemyManagerのchildからBossを削除
                std::dynamic_pointer_cast<EnemyManager>(game.getRootActor()->getChild(L"EnemyManager"))->eraseBoss();
                return;
            }
        }
        // ポーズシーンへの遷移の場合
        else {
            got::Fade::getInstance().fadeOut(SceneManager::SCENE_NAME::PAUSE);
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
