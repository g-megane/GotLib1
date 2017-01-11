//////////////////////////////////////////////////
// 作成日:2016/10/28
// 更新日:2016/12/19
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Actor.h"
#include "Enemy.h"

class EnemyManager : public Actor
{
public:


	EnemyManager(const int _num);
	~EnemyManager() override;

	bool init() override;
	void move() override;
	void draw() const override;
	void end()  override;

    void setEnemy(const float             _bornTime,
                  const std::string&      _spriteName,
                  const int               _hp, 
                  const got::Color<float> _color,
                  const float             _initX, 
                  const float             _initY, 
                  const int               _movePattern,
                  const float             _dx, 
                  const float             _dy, 
                  const int               _shotPattern, 
                  const float             _bulletSpeed, 
                  const float             _shotInterval,
                  const int               _score,
                  const bool              _isBoss = false);

    void readFile(const std::string &filename);

private:
    void split(const std::string &source, const std::string &delimiter, std::vector<std::string>& destination);

    float elapsedTime;    // Enemyの生成に使う経過時間

    struct EnemyData {
        float             bornTime;         // 出現までの時間
        std::string       spriteName;       // spriteの名前
        int               hp;               // ヒットポイント
        got::Color<float> color;            // スプライトの色
        float             initX;            // 初期位置
        float             initY;            // 初期位置
        int               movePattern;      // 移動パターン
        float             dx;               // 移動量(x)
        float             dy;               // 移動量(y)
        int               shotPattern;      // 発射パターン
        float             bulletSpeed;      // 弾速
        float             shotInterval;     // 発射間隔
        int               score;            // 持ち点
        bool              isBoss;           // Bossか？
    };
    std::vector<EnemyData> dataList;

};
