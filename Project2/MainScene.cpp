//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/10/18
// 制作者:got
//////////////////////////////////////////////////
#include "MainScene.h"

// コンストラクタ
MainScene::MainScene()
{
	player = std::make_shared<Player>();
}
// デストラクタ
MainScene::~MainScene()
{
}
// 初期化
bool MainScene::init()
{
	actors.push_back(player);

	for (auto &actor : actors) {
		if (!actor->init()) {
			continue;
		}
	}

	return true;
}
// 更新
void MainScene::move()
{
	for (auto &actor : actors) {
		actor->move();
	}
}
// 描画
void MainScene::draw() const
{
	for (auto &actor : actors) {
		actor->draw();
	}
}
// 終了
void MainScene::end()
{
}
