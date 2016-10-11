//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/10/11
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include"Window.h"

class Game
{
public:
	Game();
	~Game();
	void init();
	void update();
	void end();

private:
	std::shared_ptr<got::Window> window;
	MSG msg;
};