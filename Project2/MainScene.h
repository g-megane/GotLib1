//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/11/16
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include <list>
#include <memory>
#include "Scene.h"
#include "Actor.h"
#include "BackGround.h"
#include "EnemyManager.h"

// メインシーンクラス(Sceneを継承)
class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();

	bool init() override;
	void move() override;
	void draw() const override;
	void end()  override;

private:
	std::shared_ptr<Actor>      rootActor;
    std::shared_ptr<BackGround> backGround;
    std::shared_ptr<Actor>      enemyManager;
};
