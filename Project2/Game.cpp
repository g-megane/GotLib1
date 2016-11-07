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
#include "EnemyBulletManager.h"
#include "EnemyManager.h"
#include "Information.h"

// コンストラクタ
Game::Game() : time()
{
	window    = std::make_shared<got::Window>(L"gotLib"); // Windowの生成
	rootActor = std::make_shared<Actor>(L"RootActor");    // RootActorの生成

	// rootActorに追加したいActorを継承したオブジェクト(MainScene)
	std::shared_ptr<Actor> player = std::make_shared<Player>();
	std::shared_ptr<Actor> em	  = std::make_shared<EnemyManager>(1);
	std::shared_ptr<Actor> pbm	  = std::make_shared<PlayerBulletManager>(100);
	std::shared_ptr<Actor> ebm    = std::make_shared<EnemyBulletManager>(1);

	std::shared_ptr<Actor> info = std::make_shared<Information>();

	// rootActorへの追加
	rootActor->addChild(player);
	rootActor->addChild(em);
	rootActor->addChild(pbm);
	rootActor->addChild(ebm);

	rootActor->addChild(info); // 最前面に表示したいので最後にadd
}
// デストラクタ
Game::~Game()
{
}
// 初期化
bool Game::init()
{
	auto hr = got::DirectX11::getInstance().initialize(window);
	if (FAILED(hr)) { // DirectXの初期化	
		return false;
	}
	hr = got::MyDirectInput::getInstance().init();
	if (FAILED(hr)) {		 // DirectInputの初期化
		return false;
	}
	auto &spriteManager = got::SpriteManager::getInstance();
	//TODO:Font(仮)
	spriteManager.addMap("0", L"Resources\\0.png");
	spriteManager.addMap("1", L"Resources\\1.png");
	spriteManager.addMap("2", L"Resources\\2.png");
	spriteManager.addMap("3", L"Resources\\3.png");
	spriteManager.addMap("4", L"Resources\\4.png");
	spriteManager.addMap("5", L"Resources\\5.png");
	spriteManager.addMap("6", L"Resources\\6.png");
	spriteManager.addMap("7", L"Resources\\7.png");
	spriteManager.addMap("8", L"Resources\\8.png");
	spriteManager.addMap("9", L"Resources\\9.png");

	//TODO:フェードとスコア表示に使う四角(仮)
	spriteManager.addMap("Board", L"Resources\\Board.png");

	//TODO:Titlecene用画像(仮)
	spriteManager.addMap("Title"	, L"Resources\\TitleSample.png");
	spriteManager.addMap("PushEnter", L"Resources\\PushEnterSample.png");

	//TODO:MainScene用画像(仮)
	//spriteManager.addMap("Player", L"Resources\\player.png");
	spriteManager.addMap("Player", L"Resources\\player1.png");
	spriteManager.addMap("Bullet", L"Resources\\Boul.png");
	spriteManager.addMap("Enemy" , L"Resources\\EnemySample.png");
	
	//TODO:ResultScene用画像(仮)
	spriteManager.addMap("Result", L"Resources\\ResultSample.png");

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
