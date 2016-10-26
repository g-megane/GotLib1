//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/10/11
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Window.h"
#include "Singleton.h"
#include "Time.h"
#include "Actor.h"

// ゲームを動かすクラス
class Game : public got::Singleton<Game>
{
public:
	~Game();
	bool init();
	void update();
	void end();
	std::shared_ptr<Actor> getRootActor();

private:
	friend class got::Singleton<Game>;
	Game();
	std::shared_ptr<Actor> rootActor;
	std::shared_ptr<got::Window> window;
	MSG msg;
	got::Time time;
};
