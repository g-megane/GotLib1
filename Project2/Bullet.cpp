//////////////////////////////////////////////////
// 作成日:2016/10/21
// 更新日:2016/10/21
// 制作者:got
//////////////////////////////////////////////////
#include "Bullet.h"
#include "SpriteManager.h"

#include <random>

// コンストラクタ
Bullet::Bullet()
{
	std::random_device rd;
	auto urd = std::uniform_real_distribution<float>(0.1f, 5.0f);
	dy = urd(rd);

}

// デストラクタ
Bullet::~Bullet()
{
}
// 初期化
bool Bullet::init()
{
	state = USE;
	position.move(STAGE_WIDTH / 2, STAGE_HEIGHT - 100);
	//dy = 0.1f;
	return true;
}
// 更新
void Bullet::move()
{
	if (state == USE) {
		position.y -= dy;
	}
}
// 描画
void Bullet::draw() const
{
	if (state == USE) {
		auto mt = got::Matrix4x4<float>::translate(position);
		auto & spriteManager = got::SpriteManager::getInstance();
		auto color = got::Color<float>();
		auto rect = got::Rectangle<int>(got::Vector2<int>(spriteManager.getSprite("Bullet")->getSize().width, spriteManager.getSprite("Bullet")->getSize().height));

		got::SpriteManager::getInstance().draw("Bullet", mt, rect, color);
	}
}

void Bullet::end()
{
}
