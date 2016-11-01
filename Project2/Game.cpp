//////////////////////////////////////////////////
// 作成日:2016/10/10
// 更新日:2016/10/28
// 制作者:got
//////////////////////////////////////////////////
#include <chrono>
#include <sstream>
#include "Game.h"
#include "SceneManager.h"
#include "SpriteManager.h"
#include "MyDirectInput.h"
#include "Player.h"
#include "PlayerBulletManager.h"
#include "Enemy.h"
#include "EnemyBulletManager.h"
#include "EnemyManager.h"

// コンストラクタ
Game::Game() : time()
{
	window    = std::make_shared<got::Window>(L"gotLib"); // Windowの生成
	rootActor = std::make_shared<Actor>(L"RootActor");    // RootActorの生成

	// rootActorに追加したいActorを継承したオブジェクト(MainScene)
	std::shared_ptr<Actor> player = std::make_shared<Player>();
	std::shared_ptr<Actor> pbm	  = std::make_shared<PlayerBulletManager>(100);
	std::shared_ptr<Actor> em	  = std::make_shared<EnemyManager>(1);
	//std::shared_ptr<Actor> enemy  = std::make_shared<Enemy>();
	std::shared_ptr<Actor> ebm    = std::make_shared<EnemyBulletManager>(100);

	// rootActorへの追加
	rootActor->addChild(player);
	rootActor->addChild(pbm);
	rootActor->addChild(em);
	//rootActor->addChild(enemy);
	rootActor->addChild(ebm);
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
	auto &spriteManager = got::SpriteManager::getInstance();
	spriteManager.addMap("Player", L"player.png");
	spriteManager.addMap("Bullet", L"Boul.png");
	spriteManager.addMap("Enemy", L"enemy.png");
	

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
		if (!time.timeOver(1000.0f / 60.0f)) { // FPSの固定
			continue;
		}
		countTime += time.getDeltaTime(); // 経過時間を数える
		// FPSの表示
		if (countTime > 1000.0f) {
			stream << fps << std::endl;
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

std::shared_ptr<Actor> & Game::getRootActor()
{
	return rootActor;
}
