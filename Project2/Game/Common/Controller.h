//////////////////////////////////////////////////
// 作成日:2017/6/4
// 更新日:2017/6/4
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "../../got/Math/Vector2.h"
#include "../../got/Utility/Singleton.h"
#include "../../got/Input/MyDirectInput.h"
#include "../../got/Input/MyXInput.h"

class Controller : public got::Singleton<Controller>
{
public:
    ~Controller();
    
    bool shot();
    bool speedDown();
    got::Vector2<float> move();
    bool pause();

private:
    friend class got::Singleton<Controller>;
    Controller();

};