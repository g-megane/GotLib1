//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/10/11
// 制作者:got
//////////////////////////////////////////////////
#include "MainScene.h"

MainScene::MainScene()
{
	player = std::make_shared<Player>();
}

MainScene::~MainScene()
{
}

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

void MainScene::move()
{
	for (auto &actor : actors) {
		actor->move();
	}
}

void MainScene::draw() const
{
	for (auto &actor : actors) {
		actor->draw();
	}
}

void MainScene::end()
{
}
