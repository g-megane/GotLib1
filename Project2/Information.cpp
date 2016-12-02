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
	auto mt = got::Matrix4x4<float>::translate(position);
	auto spriteSize = got::SpriteManager::getInstance().getSprite("Info")->getSize();
	auto color = got::Color<float>::WHITE;
	auto drawRect = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));

	got::SpriteManager::getInstance().draw("Info", mt, drawRect, color);

	std::ostringstream oss;
	float nowTime = elapsedTime / 1000.0f;
	oss << std::fixed << std::setprecision(1) << std::setfill('0') << std::setw(6) << nowTime;
	int length = oss.str().length();
	
	//auto str = oss.str();

    // タイムの表示
	for (int i = length - 1; i > 0; --i) {
		auto str = oss.str().substr(i, 1);
        if (str == ".") {
            str = "comma";
            spriteSize = got::SpriteManager::getInstance().getSprite(str)->getSize();
            mt = got::Matrix4x4<float>::translate(got::Vector2<float>(STAGE_WIDTH + spriteSize.width * i, 125));
            color = got::Color<float>::WHITE;
            drawRect = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
        }
        else {
            spriteSize = got::SpriteManager::getInstance().getSprite(str)->getSize();
            mt = got::Matrix4x4<float>::translate(got::Vector2<float>(STAGE_WIDTH + spriteSize.width * i, 125));
            color = got::Color<float>::WHITE;
            drawRect = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
        }
		got::SpriteManager::getInstance().draw(str, mt, drawRect, color);

	}

    // スコア表示
    int b = Game::getInstance().getScore();
    std::ostringstream oss2;
    oss2 << std::setfill('0') << std::setw(6) << b;
    length = oss2.str().length();

    for (int i = length - 1; i > 0; --i) {
        const auto c = oss2.str().substr(i, 1);
        spriteSize = got::SpriteManager::getInstance().getSprite(c)->getSize();
        mt = got::Matrix4x4<float>::translate(got::Vector2<float>(STAGE_WIDTH + spriteSize.width * i, 310));
        drawRect = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
    
        got::SpriteManager::getInstance().draw(c, mt, drawRect, color);
    }

//	std::string str;
//	for (int i = length; i > 0; --i) {
//		str = oss.str().substr(i, 1);
//		int num = atoi(str.c_str());
//		mt = got::Matrix4x4<float>::translate(got::Vector2<float>(STAGE_WIDTH + 50 * i, 100));
//		spriteSize = got::SpriteManager::getInstance().getSprite(std::to_string(num))->getSize();
//		color = got::Color<float>::WHITE;
//		drawRect = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
//
//		got::SpriteManager::getInstance().draw(std::to_string(num), mt, drawRect, color);
	
}
// 終了
void Information::end()
{
}
