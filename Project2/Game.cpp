//////////////////////////////////////////////////
// 作成日:2016/10/10
// 更新日:2016/10/11
// 制作者:got
//////////////////////////////////////////////////
#include <chrono>
#include <sstream>
#include "Game.h"
#include "SceneManager.h"
#include "SpriteManager.h"
#include "MyDirectInput.h"

// コンストラクタ
Game::Game() : time()
{
	window = std::make_shared<got::Window>(L"gotLib");
	rootActor = std::make_shared<Actor>(L"RootActor");
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
	int fps = 0;
	float countTime = 0.0f;
	std::wstringstream stream;
	
	while (run) {

		msg = window->Update();
		if (msg.message == WM_QUIT) {
			break;
		}
		if (!time.timeOver(1000.0f / 60.0f)) {
			continue;
		}
		countTime += time.getDeltaTime();
		if (countTime > 1000.0f) {
			stream << fps << std::endl;// std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
			OutputDebugString(stream.str().c_str());
			fps = 0;
			countTime = 0.0f;
		}
		time.reset();
		fps++;
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

//std::shared_ptr<Actor> Game::getRootActor()
//{
//	return rootActor;
//}
