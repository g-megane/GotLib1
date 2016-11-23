//////////////////////////////////////////////////
// 作成日:2016/10/28
// 更新日:2016/11/23

// 制作者:got
//////////////////////////////////////////////////
#include "EnemyManager.h"

// コンストラクタ
// 引数: Enemyの生成数
EnemyManager::EnemyManager(const int _num)
	: Actor(L"EnemyManager"), time()
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
    for (auto & child : children) {
        child->move();
    }
 
    auto itr = dataList.begin();
    if (!time.timeOver(itr->bornTime)) { return; }
    for (auto & child : children) {
        if (child->getState() == STATE::UN_USE) {
            std::dynamic_pointer_cast<Enemy>(child)->setData(itr->hp, itr->spriteName, itr->initX, itr->initY, itr->movePattern, itr->dx, itr->dy, itr->shotPattern, itr->bulletSpeed, itr->shotInterval, itr->score);
            //EnemyData e(*itr);
            dataList.emplace_back(*itr);
            dataList.pop_front();
            time.reset();
            break;
        }
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

void EnemyManager::setEnemy(const float _bornTime, const std::string& _spriteName, const int _hp, const float _initX, const float _initY, const int _movePattern, const float _dx, const float _dy, const int _shotPattern, const float _bulltSpeed, const float _shotInterval, const int _score)
{
    EnemyData data;
    data.bornTime     = _bornTime;
    data.spriteName   = _spriteName;
    data.hp           = _hp;
    data.initX        = _initX;
    data.initY        = _initY;
    data.movePattern  = _movePattern;
    data.dx           = _dx;
    data.dy           = _dy;
    data.shotPattern  = _shotPattern;
    data.bulletSpeed  = _bulltSpeed;
    data.shotInterval = _shotInterval;
    data.score        = _score;

    dataList.emplace_back(data);
}
