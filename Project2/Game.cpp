//////////////////////////////////////////////////
// 作成日:2016/10/10
// 更新日:2016/10/11
// 制作者:got
//////////////////////////////////////////////////
#include "Game.h"
#include "SceneManager.h"
#include "SpriteManager.h"
#include "MyDirectInput.h"

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
	got::DirectX11::getInstance().initialize(window); // DirectXの初期化	
	got::MyDirectInput::getInstance().init();		  // DirectInputの初期化

	//TODO:test用スプライト
	//got::SpriteManager::getInstance().addMap("Player", L"plane2.png");
	got::SpriteManager::getInstance().addMap("Player", L"player.png");
	got::SpriteManager::getInstance().addMap("Bullet", L"Boul.png");

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
	//TODO:runを上手く実装する
	bool run = true;

	while (run) {
		msg = window->Update();
		if (msg.message == WM_QUIT) {
			break;
		}

		// シーンのアップデート
		sm.move();

		got::DirectX11::getInstance().begineFrame();
		// シーンの描画
		sm.draw();

		got::DirectX11::getInstance().endFrame();
	}
}
// 終了
void Game::end()
{
}
