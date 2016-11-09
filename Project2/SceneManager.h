//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/11/9
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include<unordered_map>
#include"Singleton.h"
#include"Scene.h"

// シーンのマネージャークラス（シングルトンを継承）
class SceneManager : public got::Singleton<SceneManager>
{
public:
	enum class SCENE_NAME
	{
		TITLE,
		MAIN,
		RESULT,
	};

	~SceneManager();
	void changeScene(SCENE_NAME name, bool init = true); // シーンの遷移
	bool init();
	void move();
	void draw() const; // シーンの描画
	void end();
	void createScene();

private:
	friend class got::Singleton<SceneManager>;
	SceneManager();

	std::shared_ptr<Scene> nowScene; // シーンオブジェクト
	std::unordered_map<SCENE_NAME, std::shared_ptr<Scene>> sceneMap;
};