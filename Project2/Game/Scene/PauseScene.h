//////////////////////////////////////////////////
// 作成日:2016/11/30
// 更新日:2016/11/30
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Scene.h"


class PauseScene : public Scene
{
public:
    PauseScene();
    ~PauseScene();

    bool init() override;
    void move() override;
    void draw() const override;
    void end()  override;

private:
    got::Vector2<float> choosePos;
    bool canSelectDown;

};
