//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/10/26
// 制作者:got
//////////////////////////////////////////////////
#include "MainScene.h"
#include "Game.h"

// コンストラクタ
MainScene::MainScene()
{
	rootActor = Game::getInstance().getRootActor();
}
// デストラクタ
MainScene::~MainScene()
{
}
// 初期化
bool MainScene::init()
{	
	if (!rootActor->init()) {
		return false;
	}

	return true;
}
// 更新
void MainScene::move()
{
	rootActor->move();
}
// 描画
void MainScene::draw() const
{
	rootActor->draw();
}
// 終了
void MainScene::end()
{
}
