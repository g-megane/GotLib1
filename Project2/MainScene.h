//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/10/11
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include"Scene.h"

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

};
