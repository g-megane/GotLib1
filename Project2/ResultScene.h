//////////////////////////////////////////////////
// 作成日:2016/10/18
// 更新日:2016/10/18
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Scene.h"

// リザルトシーン(Sceneを継承)
class ResultScene : public Scene
{
public:
	ResultScene();
	~ResultScene();

	bool init() override;
	void move() override;
	void draw() const override;
	void end()  override;

};