//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/12/14
// 制作者:got
//////////////////////////////////////////////////
#include "SceneManager.h"
#include "MainScene.h"
#include "MainScene2.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "PauseScene.h"
#include "OperatingScene.h"

// コンストラクタ
SceneManager::SceneManager()
{

}
// デストラクタ
SceneManager::~SceneManager()
{
	nowScene = nullptr;
}
// 各シーンの作成と登録
void SceneManager::createScene()
{
	std::shared_ptr<Scene> scene;

	scene = std::make_shared<ResultScene>();
	sceneMap[SCENE_NAME::RESULT] = scene;

	scene = std::make_shared<MainScene>();
	sceneMap[SCENE_NAME::MAIN] = scene;

    scene = std::make_shared<MainScene2>();
    sceneMap[SCENE_NAME::MAIN2] = scene;

    scene = std::make_shared<PauseScene>();
    sceneMap[SCENE_NAME::PAUSE] = scene;

    scene = std::make_shared<OperatingScene>();
    sceneMap[SCENE_NAME::OPERATING] = scene;

	scene = std::make_shared<TitleScene>();
	sceneMap[SCENE_NAME::TITLE] = scene;

    nowSceneName = SCENE_NAME::TITLE;
	nowScene = scene;
    nowScene->init();
}

// 前のシーンの名前を取得する
SceneManager::SCENE_NAME SceneManager::getBeforeSceneName()
{
    return beforeSceneName;
}

SceneManager::SCENE_NAME SceneManager::getNowSceneName()
{
    return nowSceneName;
}

// シーン遷移
void SceneManager::changeScene(SCENE_NAME name, bool init/*= true*/)
{
	beforeSceneName = nowSceneName; // 今のシーン名を前のシーン名に
    nowSceneName    = name;         // 遷移先のシーン名を今のシーン名に

	if (init) {
		sceneMap[name]->init();
	}

	nowScene = sceneMap[name];
}
// 初期化
bool SceneManager::init()
{
	if (!nowScene->init()) {
		return false;
	}

	return true;
}
// 更新
void SceneManager::move()
{
	nowScene->move();
}
// 描画
void SceneManager::draw() const
{
	nowScene->draw();
}
// 終了
void SceneManager::end()
{
	nowScene->end();
}
