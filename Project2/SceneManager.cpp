//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/12/14
// 制作者:got
//////////////////////////////////////////////////
#include "SceneManager.h"
#include "MainScene.h"
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
// シーンの作成
void SceneManager::createScene()
{
	std::shared_ptr<Scene> scene;

	scene = std::make_shared<ResultScene>();
	sceneMap[SCENE_NAME::RESULT] = scene;
	//sceneMap.insert(std::pair<SCENE_NAME, std::shared_ptr<Scene>>(RESULT, scene));

	scene = std::make_shared<MainScene>();
	sceneMap[SCENE_NAME::MAIN] = scene;
	//sceneMap.insert(std::pair<SCENE_NAME, std::shared_ptr<Scene>>(MAIN,   scene));

    scene = std::make_shared<PauseScene>();
    sceneMap[SCENE_NAME::PAUSE] = scene;

    scene = std::make_shared<OperatingScene>();
    sceneMap[SCENE_NAME::OPERATING] = scene;

	scene = std::make_shared<TitleScene>();
	sceneMap[SCENE_NAME::TITLE] = scene;
	//sceneMap.insert(std::pair<SCENE_NAME, std::shared_ptr<Scene>>(TITLE,  scene));

    nowSceneName = SCENE_NAME::TITLE;
	nowScene = scene;
}

// 前のシーンの名前を取得する
SceneManager::SCENE_NAME SceneManager::getBeforeSceneName()
{
    return beforeSceneName;
}

// シーン遷移
void SceneManager::changeScene(SCENE_NAME name, bool init/*= true*/)
{
	//const std::unordered_map<SCENE_NAME, std::shared_ptr<Scene>>::const_iterator p = sceneMap.find(name);
    beforeSceneName = nowSceneName; // 今のシーン名を前のシーン名に
    nowSceneName    = name;         // 遷移先のシーン名を今のシーン名に

	if (init) {
		sceneMap[name]->init();
	}

	nowScene = sceneMap[name];
	//nowScene = p->second;
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
