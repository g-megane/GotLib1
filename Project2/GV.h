//////////////////////////////////////////////////
// 作成日:2016/9/27
// 更新日:2016/11/16
// 制作者:got
//////////////////////////////////////////////////
#pragma once
// グローバル変数群

//TODO:無名名前空間に変える

namespace
{
    // ウィンドウ関係
    constexpr int WINDOW_WIDTH  = 1024;
    constexpr int WINDOW_HEIGHT = 768;

    // 円周率
    constexpr float PI = 3.14159265358979323846f;

    // 画面のゲーム部分のサイズ
    constexpr float STAGE_WIDTH  = static_cast<float>(WINDOW_WIDTH - WINDOW_WIDTH / 3);
    constexpr float STAGE_HEIGHT = static_cast<float>(WINDOW_HEIGHT);
}
