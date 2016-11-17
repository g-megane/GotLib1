//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/11/16
// 制作者:got
//////////////////////////////////////////////////
#include "MainScene.h"
#include "Game.h"

// コンストラクタ
MainScene::MainScene()
{
	rootActor  = Game::getInstance().getRootActor();
    backGround = std::make_shared<BackGround>();

    enemyManager = std::make_shared<EnemyManager>(10);
    rootActor->addChild(enemyManager);
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
    // --------------------------------- [エネミーデータのセット] -----------------------------------------------
    // -------- {HP} -- {出現座標(x)} ------- {出現座標(y)} -- {移動パターン} -- {攻撃パターン} -- {弾速} -- {発射間隔}
    em->setEnemy(5,      STAGE_WIDTH / 2.0f,   50.0f,           0,              2,              5.0f,     500.0f);
    em->setEnemy(5,      STAGE_WIDTH / 4.0f,   50.0f,           1,              0,              5.0f,     500.0f);
    em->setEnemy(5,      STAGE_WIDTH / 3.0f,   50.0f,           2,              1,              5.0f,     500.0f);
    em->setEnemy(5,      STAGE_WIDTH / 4.0f,   50.0f,           2,              2,              5.0f,     500.0f);
    em->setEnemy(5,      STAGE_WIDTH / 3.0f,   50.0f,           1,              0,              5.0f,     500.0f);
    em->setEnemy(5,      STAGE_WIDTH / 5.0f,   50.0f,           0,              1,              5.0f,     500.0f);
    // --------------------------------------------------------------------------------------------------------
    
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
