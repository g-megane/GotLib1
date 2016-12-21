//////////////////////////////////////////////////
// 作成日:2016/12/21
// 更新日:2016/12/21
// 制作者:got
//////////////////////////////////////////////////
#include "ItemManager.h"
#include "Item.h"
#include "Game.h"
#include "Collision.h"

// コンストラクタ
ItemManager::ItemManager(const int num)
    : Actor(L"ItemManager")
{
    std::shared_ptr<Actor> item;
    for (int i = 0; i < num; ++i) {
       item = std::make_shared<Item>();
       addChild(item);
    }
}
// デストラクタ
ItemManager::~ItemManager()
{
}
// 初期化
bool ItemManager::init()
{
    for (auto &item : children) {
        item->init();
    }

    //player = std::dynamic_pointer_cast<Player>(Game::getInstance().getRootActor()->getChild(L"Player"));

    return true;
}
// 更新
void ItemManager::move()
{
    for (auto &item : children) {
        item->move();
    }

    for (auto &item : children) {
        if(item->getState() == STATE::UN_USE) { continue; }
        auto player = Game::getInstance().getRootActor()->getChild(L"Player");
        if (got::Collison::circleToCircle(item->getPosition(), item->getRad(), player->getPosition(), player->getRad())) {
            //TODO: PlayerとItemのあたり判定
            //      PlayerのHPを増やす
            item->setState(STATE::UN_USE);
        }
    }
}
// 描画
void ItemManager::draw() const
{
    for (auto &item : children) {
        item->draw();
    }
}
// 終了
void ItemManager::end()
{
    for (auto &item : children) {
        item->end();
    }
}
// アイテムのドロップ
void ItemManager::itemDrop(const got::Vector2<float>& dropPos)
{
    for (auto &item : children) {
        if (item->getState() == STATE::UN_USE) {
            std::dynamic_pointer_cast<Item>(item)->drop(dropPos);
            return;
        }
    }
}
