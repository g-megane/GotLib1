//////////////////////////////////////////////////
// 作成日:2016/10/28
// 更新日:2016/10/28
// 制作者:got
//////////////////////////////////////////////////
#include "EnemyManager.h"

// コンストラクタ
// 引数: Enemyの生成数
EnemyManager::EnemyManager(const int _num)
	: Actor(L"EnemyManager")
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
	return true;
}
// 更新
void EnemyManager::move()
{
	for (auto & child : children) {
		if(child->getState() == UN_USE) {
			child->init();
		}
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
