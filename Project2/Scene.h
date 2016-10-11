//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/10/11
// 制作者:got
//////////////////////////////////////////////////
#pragma once

class Scene {
public:
	Scene() {}
	virtual ~Scene() {}
	// シーンの描画
	virtual bool init() = 0;
	virtual void move() = 0;
	virtual void draw()const = 0;
	virtual void end() = 0;
};