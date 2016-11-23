﻿//////////////////////////////////////////////////
// 作成日:2016/10/28
// 更新日:2016/11/23
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include <list>
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
	void end() override;

    void setEnemy(const float _bornTime, const int _hp, const float _initX, const float _initY, const int _movePattern, const float _dx, const float _dy, const int _shotPattern, const float _bulletSpeed, const float _shotInterval);

private:
    got::Time time;

    struct EnemyData {
        float bornTime;     // 出現までの時間
        int   hp;           // ヒットポイント
        float initX;        // 初期位置
        float initY;        // 初期位置
        int   movePattern;  // 移動パターン
        float dx;
        float dy;
        int   shotPattern;  // 発射パターン
        float bulletSpeed;  // 弾速
        float shotInterval; // 発射間隔
    };
    std::list<EnemyData> dataList;
};
