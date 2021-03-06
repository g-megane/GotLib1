﻿//////////////////////////////////////////////////
// 作成日:2016/10/10
// 更新日:2016/1/18
// 制作者:got
//////////////////////////////////////////////////
#include <chrono>
#include <sstream>
#include "Game.h"
#include "Controller.h"
#include "..\Effect\Explosion.h"
#include "..\Effect\EffectManager.h"
#include "..\Actor\EnemyManager.h"
#include "..\UI\Information.h"
#include "..\Scene\SceneManager.h"
#include "..\Actor\Player.h"
#include "..\Actor\PlayerBulletManager.h"
#include "..\Actor\EnemyBulletManager.h"
#include "..\..\got\Utility\SpriteManager.h"
#include "..\..\got\Input\MyDirectInput.h"
#include "..\..\Game\Item\ItemManager.h"
#include "..\..\got\Audio\XAudio2.h"
#include "..\..\got\Utility\Ranking.h"
#include "..\..\got\Input\MyXInput.h"

// コンストラクタ
Game::Game() : time()
{
	window    = std::make_shared<got::Window>("gotLib"); // Windowの生成
	rootActor = std::make_shared<Actor>(L"RootActor");    // RootActorの生成

    // rootActorにaddChildするための一時変数
    std::shared_ptr<Actor> tmp;
	// rootActorに追加したいActorを継承したオブジェクト(MainScene)
	tmp = std::make_shared<Player>();
	rootActor->addChild(tmp);
	

    tmp = std::make_shared<PlayerBulletManager>(100);
    rootActor->addChild(tmp);

    tmp= std::make_shared<EnemyBulletManager>(1000);
    rootActor->addChild(tmp);

    tmp = std::make_shared<ItemManager>(10);
    rootActor->addChild(tmp);

    tmp = std::make_shared<EnemyManager>(20);
    rootActor->addChild(tmp);

    Ranking::getInstance().readRanking();

    auto& effectManager = EffectManager::getInstance();
    for (int i = 0; i < 10; ++i) {
        effectManager.addEffecr(std::make_shared<Explosion>("Explosion"));
    }
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
	if (FAILED(hr)) { // DirectInputの初期化(キーボード)
		return false;
	}

    hr = got::MyDirectInput::getInstance().initGamepad();
    if (FAILED(hr)) { // DirectInputの初期化(GamePad)
        return false;
    }
    
    setResources();

    isPause     = false;
    isNextScene = false;
    isRun       = true;	

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
	int fps = 0;
	float countTime = 0.0f;
	std::ostringstream oss;
	
	while (isRun) {
		msg = window->Update();
		if (msg.message == WM_QUIT) {
			break;
		}
		if (!time.timeOver(1000.0f / 60.0f)) { // FPSの固定
			continue;
		}
        deltaTime  = time.getDeltaTime();
		countTime += deltaTime; // 経過時間を数える
		// FPSの表示
		if (countTime > 1000.0f) {
			oss << fps << std::endl;
			OutputDebugString(oss.str().c_str());
			fps = 0;
			countTime = 0.0f;
		}
		time.reset();
		++fps;
		// シーンのアップデート
		sm.move();
        got::MyDirectInput::getInstance().update();
        got::MyDirectInput::getInstance().updateGamepad();
        got::MyXInput::getInstance().updateControllerState();
        
        got::XAudio2::getInstance().update();

        if (got::Fade::getInstance().getIsFadeIn()) {
            got::Fade::getInstance().fadeIn();
        }

		got::DirectX11::getInstance().begineFrame();
		// シーンの描画
		sm.draw();
        // フェードの描画
        if (got::Fade::getInstance().getIsFade()) {
            got::Fade::getInstance().draw();
        }
		got::DirectX11::getInstance().endFrame();	
	}
}
// 終了
void Game::end()
{
    SendMessage(window->getHWND(), WM_CLOSE, 0, 0);
}

// 木構造のルートアクターを取得
std::shared_ptr<Actor> & Game::getRootActor()
{
	return rootActor;
}

// DeltaTime
const float Game::getDeltaTime() const
{
    return deltaTime;
}

// スコアを加算
void Game::addScore(const int addValue)
{
    score += addValue;
    if (score < 0) {
        score = 0;
    }
}

// スコアを取得
const int Game::getScore() const
{
    return score;
}

// スコアを０にリセット
void Game::resetScore()
{
    score = 0;
}

// 現在ポーズ中かどうかを取得
const bool Game::getIsPause() const
{
    return isPause;
}

// ポーズ状態を設定
void Game::setIsPause(const bool _isPause)
{
    isPause = _isPause;
}

// シーン遷移可能かどうかを取得
const bool Game::getIsNextScene() const
{
    return isNextScene;
}

// 次のシーンに遷移可能かを設定
void Game::setIsNextScene(const bool _isNextScene)
{
    isNextScene = _isNextScene;
}

// ゲームループを動かすかどうかを設定
void Game::setIsRun(const bool _isRun)
{
    isRun = _isRun;
}

// 使用するリソースの登録
void Game::setResources()
{
    // 使用するAudioの登録
    auto& xAudio2 = got::XAudio2::getInstance();
    xAudio2.openWave("Stage",        "Resources\\Sound\\Stage.wav");
    xAudio2.openWave("Shot1",        "Resources\\Sound\\Shot.wav");
    xAudio2.openWave("Explosion",    "Resources\\Sound\\Explosion.wav");
    xAudio2.openWave("Item",         "Resources\\Sound\\Item.wav");
    xAudio2.openWave("LevelUp",      "Resources\\Sound\\LevelUp.wav");
    xAudio2.openWave("MenuSelect",   "Resources\\Sound\\MenuSelect.wav");
    xAudio2.openWave("Enter",        "Resources\\Sound\\Enter.wav");
    xAudio2.openWave("EnemyDamage",  "Resources\\Sound\\EnemyDamage.wav");
    xAudio2.openWave("PlayerDamage", "Resources\\Sound\\PlayerDamage.wav");


    // 使用する画像の登録
    auto &spriteManager = got::SpriteManager::getInstance();
	// Font
    spriteManager.addMap("comma", L"Resources\\comma.png");
	spriteManager.addMap("0",     L"Resources\\0.png");
	spriteManager.addMap("1",     L"Resources\\1.png");
	spriteManager.addMap("2",     L"Resources\\2.png");
	spriteManager.addMap("3",     L"Resources\\3.png");
	spriteManager.addMap("4",     L"Resources\\4.png");
	spriteManager.addMap("5",     L"Resources\\5.png");
	spriteManager.addMap("6",     L"Resources\\6.png");
	spriteManager.addMap("7",     L"Resources\\7.png");
	spriteManager.addMap("8",     L"Resources\\8.png");
	spriteManager.addMap("9",     L"Resources\\9.png");

	// フェードとスコア表示に使う四角
	spriteManager.addMap("Board", L"Resources\\Board.png");

	// Titlecene用画像
	spriteManager.addMap("TitleName" , L"Resources\\TitleName.png");
	spriteManager.addMap("PushEnter" , L"Resources\\PushEnterSample.png");
    spriteManager.addMap("Start"     , L"Resources\\Start.png");
    spriteManager.addMap("Operating" , L"Resources\\Operating.png");
    spriteManager.addMap("Exit"      , L"Resources\\Exit.png");
    spriteManager.addMap("ChooseBar" , L"Resources\\ChooseBar.png");
    spriteManager.addMap("Background", L"Resources\\Background.png");

    // OperatingScene用画像
    spriteManager.addMap("OperatingMenu", L"Resources\\Operating3.png");

	// MainScene用画像
	spriteManager.addMap("Player"      , L"Resources\\Player.png");
	spriteManager.addMap("Bullet"      , L"Resources\\Boul.png");
    spriteManager.addMap("Bullet1"     , L"Resources\\Bullet1.png");
    spriteManager.addMap("Bullet2"     , L"Resources\\Bullet2.png");
    spriteManager.addMap("Bullet3"     , L"Resources\\Bullet3.png");
    spriteManager.addMap("ChaseBullet" , L"Resources\\ChaseBullet.png");
	spriteManager.addMap("Enemy"       , L"Resources\\EnemyBase2.png");
    spriteManager.addMap("Boss"        , L"Resources\\EnemySample.png");
    spriteManager.addMap("Background1" , L"Resources\\Background1.png");
    spriteManager.addMap("Item"        , L"Resources\\PowerUpItem.png");
    spriteManager.addMap("Cloud"       , L"Resources\\Cloud.png");
    spriteManager.addMap("Explosion"   , L"Resources\\Explosion1.png");
    spriteManager.addMap("FixedBattery", L"Resources\\FixedBattery.png");

    // PauseScene用画像
    spriteManager.addMap("Title", L"Resources\\Title.png");

    // Infomationクラスで使用する画像
	spriteManager.addMap("Time"     , L"Resources\\Time.png");
    spriteManager.addMap("Score"    , L"Resources\\Score.png");
    spriteManager.addMap("ShotLevel", L"Resources\\ShotLevel.png");

	// ResultScene用画像
	spriteManager.addMap("Result" , L"Resources\\ResultSample.png");
    spriteManager.addMap("Ranking", L"Resources\\ranking.png");
    spriteManager.addMap("Sra"    , L"Resources\\sra.png");
}
