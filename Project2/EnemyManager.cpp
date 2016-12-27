//////////////////////////////////////////////////
// 作成日:2016/10/28
// 更新日:2016/12/19
// 制作者:got
//////////////////////////////////////////////////
#include "EnemyManager.h"
#include "Game.h"

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
    dataList.clear();

	for (auto & child : children) {
		child->init();
	}

    elapsedTime    = 0.0f;
	return true;
}
// 更新
void EnemyManager::move()
{
    for (auto & child : children) {
        child->move();
    } 
    
    auto itr = dataList.begin();
    if (itr == dataList.end()) {
        return;
    }
    // ポーズ中かどうかの確認
    if (!Game::getInstance().getIsPause()) {
        elapsedTime += Game::getInstance().getDeltaTime();
    }
    // 出現時間かどうか？
    if(itr->bornTime > elapsedTime) { return; }
    for (auto & child : children) {
        // 空いている敵を探してデータをセット
        if (child->getState() == STATE::UN_USE) {
           //TODO:vectorに変更して繰り返しをなくす
            std::dynamic_pointer_cast<Enemy>(child)->setData(itr->hp, itr->color, itr->spriteName, itr->initX, itr->initY, itr->movePattern, itr->dx, itr->dy, itr->shotPattern, itr->bulletSpeed, itr->shotInterval, itr->score, itr->isStageLastEnemy);
            //dataList.emplace_back(*itr); // 繰り返しのための処理
            dataList.erase(itr);
            elapsedTime = 0.0f;
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

const bool EnemyManager::getIsEnemiesUnUse() const
{
    unsigned int unUseCount = 0;
    for (auto & child : children) {
        if (child->getState() == STATE::UN_USE) {
            ++unUseCount;
        }
    }
    if (unUseCount == children.size()) {
        return true;
    }
    return false;
}

void EnemyManager::setEnemy(const float _bornTime, const std::string& _spriteName, const int _hp, got::Color<float> _color, const float _initX, const float _initY, const int _movePattern, const float _dx, const float _dy, const int _shotPattern, const float _bulltSpeed, const float _shotInterval, const int _score, const bool _isStageLastEnemy/*=fasle*/)
{
    EnemyData data;
    data.bornTime         = _bornTime;
    data.spriteName       = _spriteName;
    data.hp               = _hp;
    data.color            = _color;
    data.initX            = _initX;
    data.initY            = _initY;
    data.movePattern      = _movePattern;
    data.dx               = _dx;
    data.dy               = _dy;
    data.shotPattern      = _shotPattern;
    data.bulletSpeed      = _bulltSpeed;
    data.shotInterval     = _shotInterval;
    data.score            = _score;
    data.isStageLastEnemy = _isStageLastEnemy;

    dataList.emplace_back(data);
}
