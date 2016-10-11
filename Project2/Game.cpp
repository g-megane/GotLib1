//////////////////////////////////////////////////
// 作成日:2016/10/10
// 更新日:2016/10/11
// 制作者:got
//////////////////////////////////////////////////
#include "Game.h"
#include "SceneManager.h"

// コンストラクタ
Game::Game()
{
	window = std::make_shared<got::Window>(L"GotLib");
}
// デストラクタ
Game::~Game()
{
}
// 初期化
void Game::init()
{
	got::DirectX11::getInstance().initialize(window);
	auto & sm = SceneManager::getInstance();
	sm.createScene();
	sm.init();
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
