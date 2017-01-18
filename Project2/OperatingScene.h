//////////////////////////////////////////////////
// 作成日:2016/12/14
// 更新日:2016/1/18
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Scene.h"


class OperatingScene : public Scene
{
public:
    OperatingScene();
    ~OperatingScene();

    bool init() override;
    void move() override;
    void draw() const override;
    void end()  override;

private:
    got::Color<float> color;
};
