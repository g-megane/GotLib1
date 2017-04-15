//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/11/23
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "..\..\got\Window\Window.h"
#include "..\..\got\Utility\Singleton.h"
#include "..\..\got\Utility\Time.h"
#include "..\Actor\Actor.h"
#include "..\..\got\Utility\Fade.h"

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
    void resetScore();
    const bool getIsPause() const;
    void setIsPause(const bool _isPause);
    const bool getIsNextScene() const;
    void setIsNextScene(const bool _isNextScene);

private:
	friend class got::Singleton<Game>;

    float deltaTime;
    int   score;
    bool  isPause;
    bool  isNextScene;
	Game();
	std::shared_ptr<Actor> rootActor;
	std::shared_ptr<got::Window> window;
	MSG msg;
	got::Time time;
};
