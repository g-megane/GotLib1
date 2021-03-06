﻿//////////////////////////////////////////////////
// 作成日:2016/10/18
// 更新日:2016/11/9
// 制作者:got
//////////////////////////////////////////////////
#include <sstream>
#include <iomanip>
#include "ResultScene.h"
#include "SceneManager.h"
#include "..\..\got\Input\MyDirectInput.h"
#include "..\Common\Game.h"
#include "..\..\got\Audio\XAudio2.h"
#include "..\..\got\Utility\Ranking.h"
#include "..\..\got\Input\MyXInput.h"

// コンストラクタ
ResultScene::ResultScene()
{
    background = std::make_shared<BackGround>("Background");
}
// デストラクタ
ResultScene::~ResultScene()
{
}
// 初期化
bool ResultScene::init()
{
    if (!background->init()) {
        return false;
    }

    got::MyXInput::getInstance().setRightVibration(0, 0);

	auto spriteSize = got::SpriteManager::getInstance().getSprite("Result")->getSize();
	position.move(WINDOW_WIDTH / 2.0f - spriteSize.width / 2.0f, WINDOW_HEIGHT / 4.0f);
    color.WHITE;

    Ranking::getInstance().writeRanking(Game::getInstance().getScore());

    oss3 = Ranking::getInstance().getRankingsString();
	return true;
}
// 更新
void ResultScene::move()
{
    background->move();

	// シーン遷移(TITLE->MAIN)
    auto &input = got::MyDirectInput::getInstance();
    auto &fade  = got::Fade::getInstance();

    if (!fade.getIsFadeOut() && !fade.getIsFadeIn()) {
        if (input.keyPressed(DIK_RETURN) || input.buttonPressed(0)) {
            got::XAudio2::getInstance().play("Enter");
            fade.setIsFadeOut(true);
        }
    }

    if (fade.getIsFadeOut()) {
		fade.fadeOut(SceneManager::SCENE_NAME::TITLE);
    }
}
// 描画
void ResultScene::draw() const
{
    background->draw();

    // 情報表示エリアの背景
    auto &spriteManager = got::SpriteManager::getInstance();

    // スコア表示
    // 文字
    auto spriteSize = spriteManager.getSprite("Score")->getSize();
    auto mt = got::Matrix4x4<float>::translate(got::Vector2<float>(static_cast<float>(WINDOW_WIDTH) / 2.0f - spriteSize.width / 2.0f, 100.0f));
    auto drawRect = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
    spriteManager.draw("Score", mt, drawRect, color);

    // 数字
    int b = Game::getInstance().getScore();
    std::ostringstream oss2;
    oss2 << std::setfill('0') << std::setw(6) << b;
    int length = oss2.str().length();

    for (int i = length - 1; i > 0; --i) {
        const auto c = oss2.str().substr(i, 1);
        spriteSize = spriteManager.getSprite(c)->getSize();
        mt = got::Matrix4x4<float>::translate(got::Vector2<float>((STAGE_WIDTH / 2 + 64.0f) + spriteSize.width * i, 150.0f));
        drawRect = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));

        spriteManager.draw(c, mt, drawRect, color);
    }

    // ランキング
    // 文字
    spriteSize = spriteManager.getSprite("Ranking")->getSize();
    mt         = got::Matrix4x4<float>::translate(got::Vector2<float>(static_cast<float>(WINDOW_WIDTH) / 2.0f - spriteSize.width / 2.0f, 290.0f));
    drawRect   = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
    spriteManager.draw("Ranking", mt, drawRect, color);
    // 数字
    float y = 700.0f;
    float x = 900.0f;
    length = oss3.str().length();

    for (int i = length - 1; i >= 0; --i) {
        auto str = oss3.str().substr(i, 1);
        // null
        if (str == "") { continue; }
        // 改行
        else if (str == "n") {
            y -= 35.0f;
            x =  900.0f;
        }
        // スペース
        else if (str == " ") {
            x -= spriteSize.width + 5.0f;
        }
        else if (str == "/") {
            str = "Sra";
            spriteSize = got::SpriteManager::getInstance().getSprite(str)->getSize();
            mt = got::Matrix4x4<float>::translate(got::Vector2<float>(x, y));
            drawRect = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
            got::SpriteManager::getInstance().draw(str, mt, drawRect, color);
            x -= spriteSize.width;
        }
        // 「.」
        else if (str == ".") {
            str = "comma";
            spriteSize = got::SpriteManager::getInstance().getSprite(str)->getSize();
            mt         = got::Matrix4x4<float>::translate(got::Vector2<float>(x, y));
            drawRect   = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
            got::SpriteManager::getInstance().draw(str, mt, drawRect, color);
            x -= spriteSize.width;
        }
        // 「数字」
        else {
            spriteSize = got::SpriteManager::getInstance().getSprite(str)->getSize();
            mt = got::Matrix4x4<float>::translate(got::Vector2<float>(x, y));
            drawRect = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
            got::SpriteManager::getInstance().draw(str, mt, drawRect, color);
            x -= spriteSize.width;
        }
    }
}\
// 終了
void ResultScene::end()
{
    background->end();
}
