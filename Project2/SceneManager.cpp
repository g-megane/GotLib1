//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/10/11
// 制作者:got
//////////////////////////////////////////////////
#include "SceneManager.h"
#include "MainScene.h"
#include "TitleScene.h"
#include "ResultScene.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
	nowScene = nullptr;
}

void SceneManager::createScene()
{
	std::shared_ptr<Scene> scene;

	scene = std::make_shared<ResultScene>();
	sceneMap[RESULT] = scene;
	//sceneMap.insert(std::pair<SCENE_NAME, std::shared_ptr<Scene>>(RESULT, scene));

	scene = std::make_shared<MainScene>();
	sceneMap[MAIN] = scene;
	//sceneMap.insert(std::pair<SCENE_NAME, std::shared_ptr<Scene>>(MAIN,   scene));

	scene = std::make_shared<TitleScene>();
	sceneMap[TITLE] = scene;
	//sceneMap.insert(std::pair<SCENE_NAME, std::shared_ptr<Scene>>(TITLE,  scene));

	nowScene = scene;
}

void SceneManager::changeScene(SCENE_NAME name, bool init)
{
	//const std::unordered_map<SCENE_NAME, std::shared_ptr<Scene>>::const_iterator p = sceneMap.find(name);

	if (init) {
		sceneMap[name]->init();
	}

	nowScene = sceneMap[name];
	//nowScene = p->second;
}

bool SceneManager::init()
{
	if (!nowScene->init()) {
		return false;
	}

	return true;
}

void SceneManager::move()
{
	nowScene->move();
}

void SceneManager::draw() const
{
	nowScene->draw();
}

void SceneManager::end()
{
	nowScene->end();
}
