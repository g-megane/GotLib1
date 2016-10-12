//////////////////////////////////////////////////
// 作成日:2016/10/10
// 更新日:2016/10/11
// 制作者:got
//////////////////////////////////////////////////
#include "Game.h"
#include "SceneManager.h"
#include "SpriteManager.h"

// コンストラクタ
Game::Game()
{
	window = std::make_shared<got::Window>(L"gotLib");
}
// デストラクタ
Game::~Game()
{
}
// 初期化
bool Game::init()
{
	got::DirectX11::getInstance().initialize(window);

	//TODO:test用
	got::SpriteManager::getInstance().addMap("Player", L"plane2.png");

	auto & sm = SceneManager::getInstance();
	sm.createScene();
	
	if (!sm.init()) {
		return false;
	}

	return true;
}
// 更新
void Game::update()
{
	auto & sm = SceneManager::getInstance();
	bool run = true;

	while (run) {
		msg = window->Update();
		if (msg.message == WM_QUIT) {
			break;
		}

		sm.move();

		got::DirectX11::getInstance().begineFrame();

		sm.draw();

		got::DirectX11::getInstance().endFrame();
	}
}
// 終了
void Game::end()
{
}
