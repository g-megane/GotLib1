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
	//rootActor = std::make_shared<Actor>(L"RootActor");
	rootActor = Game::getInstance().getRootActor();

//	// rootActorに追加したいActorを継承したオブジェクト
//	std::shared_ptr<Actor> player = std::make_shared<Player>();
//	std::shared_ptr<Actor> bm	  = std::make_shared<BulletManager>(100);
//
//	// rootActorへの追加
//	rootActor->addChild(player);
//	rootActor->addChild(bm);
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
