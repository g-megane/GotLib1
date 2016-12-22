//////////////////////////////////////////////////
// 作成日:2016/11/2
// 更新日:2016/11/30
// 制作者:got
//////////////////////////////////////////////////
#include <sstream>
#include <stdlib.h>
#include <iomanip>
#include "Information.h"
#include "GV.h"
#include "Game.h"
#include "Player.h"

// コンストラクタ
Information::Information()
{
}
// デストラクタ
Information::~Information()
{
}
// 初期化
bool Information::init()
{
	position.move(STAGE_WIDTH-2, -1.0f);
	for (int i = 0; i < 5; ++i) {
		poses[i].move(STAGE_WIDTH + 50 * i, 100);
	}
	elapsedTime = 0.0f;
	return true;
}
// 更新
void Information::move()
{
    if (!Game::getInstance().getIsPause()) {
	    elapsedTime += Game::getInstance().getDeltaTime();
    }
}
// 描画
void Information::draw() const
{
    // 情報表示エリアの背景
	auto mt         = got::Matrix4x4<float>::translate(position);
	auto spriteSize = got::SpriteManager::getInstance().getSprite("Board")->getSize();
	auto color      = got::Color<float>::WHITE;
	auto drawRect   = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
	got::SpriteManager::getInstance().draw("Board", mt, drawRect, color);

    // タイムの表示
    // 文字
    spriteSize = got::SpriteManager::getInstance().getSprite("Time")->getSize();
    mt         = got::Matrix4x4<float>::translate(got::Vector2<float>(STAGE_WIDTH + 20.0f, 80.0f));
    drawRect   = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
    got::SpriteManager::getInstance().draw("Time", mt, drawRect, color);

    std::ostringstream oss;
	float nowTime = elapsedTime / 1000.0f;
	oss << std::fixed << std::setprecision(1) << std::setfill('0') << std::setw(6) << nowTime;
	int length = oss.str().length();
	
    // 数字
	for (int i = length - 1; i > 0; --i) {
		auto str = oss.str().substr(i, 1);
        if (str == ".") {
            str = "comma";
            spriteSize = got::SpriteManager::getInstance().getSprite(str)->getSize();
            mt         = got::Matrix4x4<float>::translate(got::Vector2<float>(STAGE_WIDTH + spriteSize.width * i, 125.0f));
            drawRect   = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
        }
        else {
            spriteSize = got::SpriteManager::getInstance().getSprite(str)->getSize();
            mt         = got::Matrix4x4<float>::translate(got::Vector2<float>(STAGE_WIDTH + spriteSize.width * i, 125.0f));
            drawRect   = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
        }
		got::SpriteManager::getInstance().draw(str, mt, drawRect, color);
	}

    // スコア表示
    // 文字
    spriteSize = got::SpriteManager::getInstance().getSprite("Score")->getSize();
    mt = got::Matrix4x4<float>::translate(got::Vector2<float>(STAGE_WIDTH + 20.0f, 260.0f));
    drawRect = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
    got::SpriteManager::getInstance().draw("Score", mt, drawRect, color);

    // 数字
    int b = Game::getInstance().getScore();
    std::ostringstream oss2;
    oss2 << std::setfill('0') << std::setw(6) << b;
    length = oss2.str().length();

    for (int i = length - 1; i > 0; --i) {
        const auto c = oss2.str().substr(i, 1);
        spriteSize = got::SpriteManager::getInstance().getSprite(c)->getSize();
        mt         = got::Matrix4x4<float>::translate(got::Vector2<float>(STAGE_WIDTH + spriteSize.width * i, 310.0f));
        drawRect   = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
    
        got::SpriteManager::getInstance().draw(c, mt, drawRect, color);
    }

    // プレイヤーのショットレベルの表示
    // 文字
    spriteSize = got::SpriteManager::getInstance().getSprite("ShotLevel")->getSize();
    mt = got::Matrix4x4<float>::translate(got::Vector2<float>(STAGE_WIDTH + 20.0f, 450.0f));
    drawRect = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
    got::SpriteManager::getInstance().draw("ShotLevel", mt, drawRect, color);

    // 数字
    int shotLevel = std::dynamic_pointer_cast<Player>(Game::getInstance().getRootActor()->getChild(L"Player"))->getHp();
    std::ostringstream oss3;
    oss3 << std::setfill('0') << std::setw(2) << shotLevel;
    length = oss3.str().length();

    for (int i = length - 1; i > 0; --i) {
        const auto c = oss3.str().substr(i, 1);
        spriteSize = got::SpriteManager::getInstance().getSprite(c)->getSize();
        mt = got::Matrix4x4<float>::translate(got::Vector2<float>(STAGE_WIDTH + spriteSize.width * i, 500.0f));
        drawRect = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));

        got::SpriteManager::getInstance().draw(c, mt, drawRect, color);
    }
}

// 終了
void Information::end()
{
}
