//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/11/2
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "..\..\got\Math\Matrix4x4.h"
#include "..\..\got\Utility\SpriteManager.h"
#include "..\..\got\Utility\Rectangle.h"
#include "..\..\got\Utility\Color.h"
#include "..\Common\GV.h"
#include "..\Common\BackGround.h"

class Scene {
public:
	Scene() {}
	virtual ~Scene() {}
	// シーンの描画
	virtual bool init() = 0;
	virtual void move() = 0;
	virtual void draw() const = 0;
	virtual void end() = 0;
	
protected:
	got::Vector2<float> position;
    got::Color<float> color;
    std::shared_ptr<BackGround> background;

};
