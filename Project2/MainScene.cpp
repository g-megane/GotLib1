//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/10/26
// 制作者:got
//////////////////////////////////////////////////
#include "MainScene.h"

// コンストラクタ
MainScene::MainScene()
{
	rootActor = std::make_shared<Actor>(L"RootActor");
	
	// rootActorに追加したいActorを継承したオブジェクト
	std::shared_ptr<Actor> player = std::make_shared<Player>();
	std::shared_ptr<Actor> bm	  = std::make_shared<BulletManager>(100);

	// rootActorへの追加
	rootActor->addChild(player);
	rootActor->addChild(bm);
}
// デストラクタ
MainScene::~MainScene()
{
}
// 初期化
bool MainScene::init()
{	
	rootActor->init();
	//actors.emplace_back(player);
	//actors.emplace_back(bm);

	//for (auto &actor : actors) {
	//	if (!actor->init()) {
	//		continue;
	//	}
	//}

	return true;
}
// 更新
void MainScene::move()
{
	rootActor->move();
	//for (auto &actor : actors) {
	//	actor->move();
	//}
}
// 描画
void MainScene::draw() const
{
	rootActor->draw();
	//for (auto &actor : actors) {
	//	actor->draw();
	//}
}
// 終了
void MainScene::end()
{
}
