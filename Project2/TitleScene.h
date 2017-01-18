//////////////////////////////////////////////////
// 作成日:2016/10/18
// 更新日:2016/10/18
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Scene.h"
#include "BackGround.h"

// タイトルシーンクラス(Sceneを継承)
class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene();

	bool init() override;
	void move() override;
	void draw() const override;
	void end()  override;

private:
    got::Vector2<float> choosePos;
    
};

