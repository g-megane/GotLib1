//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/11/23
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Window.h"
#include "Singleton.h"
#include "Time.h"
#include "Actor.h"
#include "Fade.h"

// ゲームを動かすクラス
class Game : public got::Singleton<Game>
{
public:
	~Game();
	bool init();
	void update();
	void end();
	
    std::shared_ptr<Actor> & getRootActor();
    const float getDeltaTime() const;
    void addScore(const int addValue);
    const int getScore() const;
    const bool getIsPause() const;
    void setIsPause(const bool _isPause);

private:
	friend class got::Singleton<Game>;

    float deltaTime;
    int   score;
    bool  isPause;
	Game();
	std::shared_ptr<Actor> rootActor;
	std::shared_ptr<got::Window> window;
	MSG msg;
	got::Time time;
};
