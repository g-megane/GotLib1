//////////////////////////////////////////////////
// 作成日:2016/11/2
// 更新日:2016/11/2
// 制作者:got
//////////////////////////////////////////////////
#include <sstream>
#include <stdlib.h>
#include <iomanip>
#include "Information.h"
#include "GV.h"

// コンストラクタ
Information::Information()
	: time()
{
}
// デストラクタ
Information::~Information()
{
}
// 初期化
bool Information::init()
{
	position.move(WINDOW_WIDTH - WINDOW_WIDTH / 3, 0);
	for (int i = 0; i < 5; ++i) {
		poses[i].move(STAGE_WIDTH + 50 * i, 100);
	}
	elapsedTime = 0.0f;
	time.reset();
	return true;
}
// 更新
void Information::move()
{
	elapsedTime += time.getDeltaTime();
	time.reset();
}
// 描画
void Information::draw() const
{
	auto mt = got::Matrix4x4<float>::translate(position);
	auto spriteSize = got::SpriteManager::getInstance().getSprite("Board")->getSize();
	auto color = got::Color<float>::BLACK;
	auto drawRect = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));

	got::SpriteManager::getInstance().draw("Board", mt, drawRect, color);

	
	std::ostringstream oss;
	float a = elapsedTime / 1000.0f;
	oss << std::fixed << std::setprecision(1) << std::setfill('0') << std::setw(6) << a;
	int length = oss.str().length();
	
	{
		auto str = oss.str();

		for (int i = length - 1; i > 0; --i) {
			const auto c = oss.str().substr(i, 1);
			if (c == ".") continue;
			mt = got::Matrix4x4<float>::translate(got::Vector2<float>(STAGE_WIDTH + 50 * i, 100));
			spriteSize = got::SpriteManager::getInstance().getSprite(c)->getSize();
			color = got::Color<float>::WHITE;
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
}
// 終了
void Information::end()
{
}
