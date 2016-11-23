//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/11/23
// 制作者:got
//////////////////////////////////////////////////
#include "MainScene.h"
#include "Game.h"
#include "Information.h"

// コンストラクタ
MainScene::MainScene()
{
	rootActor  = Game::getInstance().getRootActor();
    backGround = std::make_shared<BackGround>();
   
    //TODO:とりあえず10体を使いまわし
    enemyManager = std::make_shared<EnemyManager>(10);
    std::shared_ptr<Actor> info = std::make_shared<Information>();

    // ここの順番大事！！
    rootActor->addChild(enemyManager);
    rootActor->addChild(info);
}
// デストラクタ
MainScene::~MainScene()
{
}
// 初期化
bool MainScene::init()
{	
    auto em = std::dynamic_pointer_cast<EnemyManager>(enemyManager);
    //TODO:仮データ
    //TODO:出現位置は定数にするのが有かも？
    // ・出現時間を0にするとひとつ前の敵と同時に出現する
    // ・移動パターンの6と7は移動量(X)を0にしてやる必要がある
    //------------------------------------------------ [エネミーデータのセット] --------------------------------------------------------------------------
    //-------- {出現時間} - {HP} -- {出現座標(x)} ------- {出現座標(y)} -- {移動パターン} -{移動量(x)} - {移動量(y)} - {攻撃パターン} -- {弾速} -- {発射間隔}
    em->setEnemy(3000.0f,    5,     STAGE_WIDTH / 2.0f,   50.0f,           0,            0.1f,         0.1f,         0,              0.3f,      500.0f);
    em->setEnemy(   0.0f,    5,     STAGE_WIDTH / 4.0f,   50.0f,           1,            0.1f,         0.1f,         1,              0.3f,     1000.0f);
    em->setEnemy(3000.0f,    5,     STAGE_WIDTH / 3.0f,   50.0f,           2,            0.1f,         0.1f,         2,              0.3f,      500.0f);
    em->setEnemy(3000.0f,    5,     STAGE_WIDTH / 4.0f,   50.0f,           3,            0.1f,         0.1f,         3,              0.3f,     1000.0f);
    em->setEnemy(3000.0f,    5,     STAGE_WIDTH,          50.0f,           4,            0.1f,         0.1f,         0,              0.3f,      500.0f);
    em->setEnemy(3000.0f,    5,               0,          50.0f,           5,            0.1f,         0.1f,         0,              0.3f,      500.0f);
    em->setEnemy(3000.0f,    5,     STAGE_WIDTH - 200.0f, 50.0f,           6,            0.0f,         0.1f,         0,              0.3f,      500.0f);
    em->setEnemy(3000.0f,    5,               0,          50.0f,           7,            0.0f,         0.1f,         0,              0.3f,      500.0f);
    //---------------------------------------------------------------------------------------------------------------------------------------------------
    
    if (!backGround->init()) {
        return false;
    }
	if (!rootActor->init()) {
		return false;
	}

	return true;
}
// 更新
void MainScene::move()
{
    backGround->move();
	rootActor->move();
}
// 描画
void MainScene::draw() const
{
    backGround->draw();
	rootActor->draw();
}
// 終了
void MainScene::end()
{
   backGround->end();
   rootActor->end();
}
