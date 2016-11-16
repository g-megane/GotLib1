//////////////////////////////////////////////////
// 作成日:2016/10/28
// 更新日:2016/11/16
// 制作者:got
//////////////////////////////////////////////////
#include "EnemyManager.h"

// コンストラクタ
// 引数: Enemyの生成数
EnemyManager::EnemyManager(const int _num)
	: Actor(L"EnemyManager"), time()//, dataList()
{
	std::shared_ptr<Actor> enemy;
	for (int i = 0; i < _num; ++i) {
		enemy = std::make_shared<Enemy>();
		addChild(enemy);
	}
}
// デストラクタ
EnemyManager::~EnemyManager()
{
}
// 初期化
bool EnemyManager::init()
{
	for (auto & child : children) {
		child->init();
	}

    time.reset();

	return true;
}
// 更新
void EnemyManager::move()
{
    auto itr = dataList.begin();
    if (time.timeOver(2000.0f)) {
        for (auto & child : children) {
            if (child->getState() == STATE::UN_USE){// && time.timeOver(2000.0f)) {
                std::dynamic_pointer_cast<Enemy>(child)->setData(itr->hp, itr->initX, itr->initY, itr->movePattern, itr->shotPattern, itr->bulletSpeed);
                //EnemyData e(*itr);
                dataList.push_back(*itr);
                dataList.pop_front();
                time.reset();
                break;
            }
        }
    }
    for (auto & child : children) {
        child->move();
    }
}
// 描画
void EnemyManager::draw() const
{
	for (auto & child : children) {
		child->draw();
	}
}
// 終了
void EnemyManager::end()
{
	for (auto & child : children) {
		child->end();
	}
}

void EnemyManager::setEnemy(const int _hp, const float _initX, const float _initY, const int _movePattern, const int _shotPattern, const float _bulltSpeed)
{
    EnemyData data;
    data.hp = _hp;
    data.initX = _initX;
    data.initY = _initY;
    data.movePattern = _movePattern;
    data.shotPattern = _shotPattern;
    data.bulletSpeed = _bulltSpeed;

    dataList.emplace_back(data);
}
