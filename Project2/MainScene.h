//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/10/11
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include<list>
#include<memory>
#include"Scene.h"
#include"Actor.h"
#include"Player.h"

class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();

	bool init() override;
	void move() override;
	void draw() const override;
	void end() override;

private:
	std::list<std::shared_ptr<Actor>> actors;
	std::shared_ptr<Actor> player;
};
