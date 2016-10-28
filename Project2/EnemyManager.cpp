//////////////////////////////////////////////////
// 作成日:2016/10/28
// 更新日:2016/10/28
// 制作者:got
//////////////////////////////////////////////////
#include "EnemyManager.h"

// コンストラクタ
// 引数: Enemyの生成数
EnemyManager::EnemyManager(const int _num)
	: Actor(L"EnemyManager"), enemies(_num)
{
}
// デストラクタ
EnemyManager::~EnemyManager()
{
}
// 初期化
bool EnemyManager::init()
{
	for (auto & enemy : enemies) {
		enemy.init();
	}
	return true;
}
// 更新
void EnemyManager::move()
{
	for (auto & enemy : enemies) {
		enemy.move();
	}
}
// 描画
void EnemyManager::draw() const
{
	for (auto & enemy : enemies) {
		enemy.draw();
	}
}
// 終了
void EnemyManager::end()
{
	for (auto & enemy : enemies) {
		enemy.end();
	}
}
