//////////////////////////////////////////////////
// 作成日:2016/10/10
// 更新日:2016/12/14
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
#include "ItemManager.h"
#include "EnemyManager.h"
#include "Information.h"
#include "XAudio2.h"

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
	//std::shared_ptr<Actor> pbm	  = 
    tmp = std::make_shared<PlayerBulletManager>(100);
    rootActor->addChild(tmp);
	//std::shared_ptr<Actor> ebm    
    tmp= std::make_shared<EnemyBulletManager>(500);
    rootActor->addChild(tmp);

    tmp = std::make_shared<ItemManager>(10);
    rootActor->addChild(tmp);

	// rootActorへの追加
	//rootActor->addChild(player);
	//rootActor->addChild(pbm);
	//rootActor->addChild(ebm);
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

    got::XAudio2::getInstance().openWave("Stage", "Stage.wav");
    got::XAudio2::getInstance().openWave("Shot1", "Shot1.wav");

    isPause = false;
    isNextScene = false;

	auto &spriteManager = got::SpriteManager::getInstance();
	//TODO:Font(仮)
    spriteManager.addMap("comma", L"Resources\\comma.png");
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
    spriteManager.addMap("Start"    , L"Resources\\Start.png");
    spriteManager.addMap("Operating", L"Resources\\Operating.png");
    spriteManager.addMap("ChooseBar", L"Resources\\ChooseBar.png");

    // OperatingScene用画像
    spriteManager.addMap("OperatingMenu", L"Resources\\OperatingMenu.png");

	//TODO:MainScene用画像(仮)
	spriteManager.addMap("Player"     , L"Resources\\Player.png");
	spriteManager.addMap("Bullet"     , L"Resources\\Boul.png");
    spriteManager.addMap("Bullet1"    , L"Resources\\Bullet1.png");
    spriteManager.addMap("Bullet2"    , L"Resources\\Bullet2.png");
    spriteManager.addMap("Bullet3"    , L"Resources\\Bullet3.png");
    spriteManager.addMap("ChaseBullet", L"Resources\\ChaseBullet.png");
	spriteManager.addMap("Enemy"      , L"Resources\\EnemyBase2.png");
    spriteManager.addMap("BackGround" , L"Resources\\Background1.png");
    spriteManager.addMap("Item"       , L"Resources\\PowerUpItem.png");

    // Infomationクラスで使用する画像
    //spriteManager.addMap("Info"      , L"Resources\\Info.png");
	spriteManager.addMap("Time", L"Resources\\Time.png");
    spriteManager.addMap("Score", L"Resources\\Score.png");
    spriteManager.addMap("ShotLevel", L"Resources\\ShotLevel.png");

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
	std::ostringstream oss;
	
	while (run) {

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
		fps++;
		// シーンのアップデート
		sm.move();
        got::MyDirectInput::getInstance().update();
        //TODO:動作確認
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
}

std::shared_ptr<Actor> & Game::getRootActor()
{
	return rootActor;
}

const float Game::getDeltaTime() const
{
    return deltaTime;
}

void Game::addScore(const int addValue)
{
    score += addValue;
}

const int Game::getScore() const
{
    return score;
}

void Game::resetScore()
{
    score = 0;
}

const bool Game::getIsPause() const
{
    return isPause;
}

void Game::setIsPause(const bool _isPause)
{
    isPause = _isPause;
}

const bool Game::getIsNextScene() const
{
    return isNextScene;
}

void Game::setIsNextScene(const bool _isNextScene)
{
    isNextScene = _isNextScene;
}
