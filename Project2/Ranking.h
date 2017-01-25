//////////////////////////////////////////////////
// 作成日:2016/1/25
// 更新日:2016/1/25
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include <Windows.h>
#include <list>
#include "Singleton.h"

class Ranking : public got::Singleton<Ranking>
{
public:
    struct RankingData
    {
        SYSTEMTIME time;
        int score;
    };

    ~Ranking();
    void readRanking();
    void writeRanking(const int newScore);
    std::ostringstream getRankingsString();


private:
    friend class got::Singleton<Ranking>;
    Ranking();

    std::list<RankingData> rankings;
    
};