//////////////////////////////////////////////////
// 作成日:2016/10/21
// 更新日:2016/11/30
// 制作者:got
//////////////////////////////////////////////////
#include "Bullet.h"
#include "SpriteManager.h"
#include "Game.h"

// コンストラクタ
//TODO:使う弾のスプライトを引数で呼べるように
Bullet::Bullet(const std::string& _spriteName)
	:Actor(), color()
{
    spriteName = _spriteName;
}

// デストラクタ
Bullet::~Bullet()
{
}
// 初期化
bool Bullet::init()
{
	auto &spriteManager = got::SpriteManager::getInstance();
	state               = STATE::UN_USE;
	position.move(STAGE_WIDTH / 2, STAGE_HEIGHT - 100);
	
    // 半径を画像幅の半分で初期化
    rad = spriteManager.getSprite(spriteName)->getSize().width / 2.0f;

    dx = 0.0f;
	dy = 0.0f;
	
    return true;
}
// 更新
void Bullet::move()
{
	if (state == STATE::UN_USE) { return; }

	auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();

    auto dTime = Game::getInstance().getDeltaTime();

    position.translate(dx * dTime, dy * dTime);

    // 画面外に出た弾のStateをUN_USEに変更
	if (position.x < 0)								   { setState(STATE::UN_USE); }
	if (position.x > STAGE_WIDTH - spriteSize.width)   { setState(STATE::UN_USE); }
	if (position.y < 0)								   { setState(STATE::UN_USE); }
	if (position.y > STAGE_HEIGHT - spriteSize.height) { setState(STATE::UN_USE); }
}
// 描画
void Bullet::draw() const
{
	if (state == STATE::UN_USE) { return; }
	
	auto mt = got::Matrix4x4<float>::translate(position);
	auto & spriteManager = got::SpriteManager::getInstance();
	auto drawRect = got::Rectangle<int>(got::Vector2<int>(spriteManager.getSprite(spriteName)->getSize().width, spriteManager.getSprite(spriteName)->getSize().height));

	got::SpriteManager::getInstance().draw(spriteName, mt, drawRect, color);
	
}
// 終了
void Bullet::end()
{
}

void Bullet::shot(const got::Vector2<float>& vec, const float _dx, const float _dy)
{
	dx = _dx;
	dy = _dy;
	auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();
	position = got::Vector2<float>(vec.x - spriteSize.width / 2, vec.y - spriteSize.height / 2);
	state = STATE::USE;
}

void Bullet::shot(const float _x, const float _y, const float _dx, const float _dy)
{
    dx = _dx;
    dy = _dy;
    auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();
    position = got::Vector2<float>(_x - spriteSize.width / 2, _y - spriteSize.height / 2);
    state = STATE::USE;
}
