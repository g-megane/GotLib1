//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/10/11
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include"Window.h"

// ゲームを動かすクラス
class Game
{
public:
	Game();
	~Game();
	bool init();
	void update();
	void end();

private:
	std::shared_ptr<got::Window> window;
	MSG msg;
};