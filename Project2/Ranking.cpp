//////////////////////////////////////////////////
// 作成日:2016/1/25
// 更新日:2016/1/25
// 制作者:got
//////////////////////////////////////////////////
#include <fstream>
#include <Shlwapi.h>
#include <sstream>
#include <iomanip>
#include "Ranking.h"
#pragma comment(lib, "ShLwApi.Lib")

Ranking::Ranking()
{

}
Ranking::~Ranking()
{
}

void Ranking::readRanking()
{
    rankings.clear();

    // ファイルが存在する場合
    if (PathFileExists("Resources\\Data\\Ranking.txt")) {
        std::ifstream ifs;
        ifs.open("Resources\\Data\\Ranking.txt");
        int size;
        ifs.read(reinterpret_cast<char*> (&size), sizeof(size));
        for (int i = 0; i < size; ++i) {
            RankingData rd;
            ifs.read(reinterpret_cast<char*> (&rd), sizeof(rd));
            rankings.push_back(rd);
        }
        ifs.close();
    }
    // ファイルが存在しない場合
    else {
        RankingData rd;
        ZeroMemory(&rd, sizeof(rd));
        rd.score = 0;
        for (int i = 0; i < 10; ++i) {
            rankings.push_back(rd);
        }
    }
    
}

void Ranking::writeRanking(const int newScore)
{
    for (auto itr = rankings.begin(); itr != rankings.end(); ++itr) {
        if (newScore >= itr->score) {
            SYSTEMTIME st;
            GetSystemTime(&st);
            itr = rankings.insert(itr, RankingData{ st, newScore});
            rankings.pop_back();
            break;
        }
    }

    std::ofstream ofs;
    ofs.open("Resources\\Data\\Ranking.txt");

    const int size = rankings.size();
    ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (auto itr = rankings.begin(); itr != rankings.end(); ++itr) {
        const RankingData rd(*itr);
        ofs.write(reinterpret_cast<const char*>(&rd), sizeof(rd));
    }

    ofs.close();
}

std::ostringstream Ranking::getRankingsString()
{
    std::ostringstream oss;

    oss.str("");
    oss.fill('0');
    
    int no = 0;
    for (auto rank : rankings) {
        //oss << "/" << std::setw(2) << no++ << "/";
        //if (rank.score >= 0) {
            oss << std::setw(2) << ++no << " " << std::setw(4) << rank.time.wYear << "." << std::setw(2) << rank.time.wMonth << "." << std::setw(2) << rank.time.wDay;
            oss << " " << std::setw(2) << rank.time.wHour + 9 << "." << std::setw(2) << rank.time.wMinute << "." << std::setw(2) << rank.time.wSecond;
            oss << " " << std::setw(5) << rank.score;
        //}
        oss << "n";
    }

    return oss;
}
