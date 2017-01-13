﻿//////////////////////////////////////////////////
// 作成日:2016/10/28
// 更新日:2016/1/13
// 制作者:got
//////////////////////////////////////////////////
#include <fstream>
#include "EnemyManager.h"
#include "Game.h"
#include "Boss.h"


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

    elapsedTime = 0.0f;
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
        //TODO:一度だけボスを出現させる
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
            std::dynamic_pointer_cast<Enemy>(child)->setData(itr->hp, itr->color, itr->spriteName, itr->initX, itr->initY, itr->movePattern, itr->dx, itr->dy, itr->shotPattern, itr->bulletSpeed, itr->shotInterval, itr->score, itr->isBoss);
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
// EnemyData構造体に値をセット
void EnemyManager::setEnemy(const float _bornTime, const std::string& _spriteName, const int _hp, got::Color<float> _color, const float _initX, const float _initY, const int _movePattern, const float _dx, const float _dy, const int _shotPattern, const float _bulltSpeed, const float _shotInterval, const int _score, const bool _isBoss/*=fasle*/)
{
    EnemyData data;
    data.bornTime     = _bornTime;
    data.spriteName   = _spriteName;
    data.hp           = _hp;
    data.color        = _color;
    data.initX        = _initX;
    data.initY        = _initY;
    data.movePattern  = _movePattern;
    data.dx           = _dx;
    data.dy           = _dy;
    data.shotPattern  = _shotPattern;
    data.bulletSpeed  = _bulltSpeed;
    data.shotInterval = _shotInterval;
    data.score        = _score;
    data.isBoss       = _isBoss;

    dataList.emplace_back(data);
}
// ファイルからEnemyのデータを読み込む
void EnemyManager::readFile(const std::string & filename)
{
    std::ifstream ifs;
    ifs.open(filename.c_str());

    std::string source;                   // 読み込んだ一行
    const std::string delimiter(",");     // splitで分割する単位
    std::vector<std::string> destination; // 分割後の一行

    while (!std::getline(ifs, source).eof()) {
        // 読み込んだ一行を分割
        split(source, delimiter, destination);
        // 分割された一行をEnemyData構造体にセット
        for (std::vector<std::string>::size_type i = 0; i < destination.size(); i += 13) {
            EnemyData eData;
            eData.bornTime     = std::stof(destination[i]);
            eData.spriteName   =           destination[i +  1];
            eData.hp           = std::stoi(destination[i +  2]);
            eData.color        = got::Color<float>::RED;
            eData.initX        = std::stof(destination[i +  3]);
            eData.initY        = std::stof(destination[i +  4]);
            eData.movePattern  = std::stoi(destination[i +  5]);
            eData.dx           = std::stof(destination[i +  6]);
            eData.dy           = std::stof(destination[i +  7]);
            eData.shotPattern  = std::stoi(destination[i +  8]);
            eData.bulletSpeed  = std::stof(destination[i +  9]);
            eData.shotInterval = std::stof(destination[i + 10]);
            eData.score        = std::stoi(destination[i + 11]);
            eData.isBoss       = std::stoi(destination[i + 12]) == 1 ? true : false;

            dataList.push_back(eData);
        }
    }
    ifs.close();
}
// 引数で指定した
void EnemyManager::split(const std::string & source, const std::string & delimiter, std::vector<std::string>& destination)
{
    destination.clear();
    std::string::size_type pos = 0;

    while (pos != std::string::npos) {
        // delimiterが最初に見つかる位置
        std::string::size_type p = source.find(delimiter, pos);
        if (p == std::string::npos) { // 何も見つからなかった
            destination.push_back(source.substr(pos));
            break;
        }
        else {                        // 見つかった
            destination.push_back(source.substr(pos, p - pos));
        }
        pos = p + delimiter.size();
    }
}
