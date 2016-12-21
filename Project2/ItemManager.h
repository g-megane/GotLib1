//////////////////////////////////////////////////
// 作成日:2016/12/21
// 更新日:2016/12/21
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Actor.h"
#include "Player.h"

class ItemManager : public Actor
{
public:
    ItemManager(const int num);
    ~ItemManager();

    bool init() override;
    void move() override;
    void draw() const override;
    void end()  override;

    void itemDrop(const got::Vector2<float> &dropPos);

private:
   // std::shared_ptr<Player> player;

};
