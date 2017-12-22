//////////////////////////////////////////////////
// ì¬“ú:2017/6/4
// XV“ú:2017/6/4
// §ìÒ:got
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