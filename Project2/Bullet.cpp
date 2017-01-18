//////////////////////////////////////////////////
// 作成日:2016/10/21
// 更新日:2016/12/27
// 制作者:got
//////////////////////////////////////////////////
#include "Bullet.h"
#include "SpriteManager.h"
#include "Game.h"
#include "GV.h"

// コンストラクタ
//TODO:使う弾のスプライトを引数で呼べるように
Bullet::Bullet(const std::string& _spriteName)
	:Actor(), color(), defaultBulletName(_spriteName)
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
    
    angle = 0.0f;
    beforeAngle = 0.0f;

    changeMoveFunc(0);

    return true;
}
// 更新
void Bullet::move()
{
	if (state == STATE::UN_USE) { return; }

    this->moveFunc();
	auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();
    // 画面外に出た弾のStateをUN_USEに変更
    //TODO: 範囲を広げる
	if (position.x < -100.0f)				{ setState(STATE::UN_USE); return; }
	if (position.x > STAGE_WIDTH + 100.0f)  { setState(STATE::UN_USE); return; }
	if (position.y < -500.0f)				{ setState(STATE::UN_USE); return; }
	if (position.y > STAGE_HEIGHT + 100.0f) { setState(STATE::UN_USE); return; }
}
// 描画
void Bullet::draw() const
{
	if (state == STATE::UN_USE) { return; }

    auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();
    auto mt = got::Matrix4x4<float>::translate(position);

    if (angle != 0.0f) {
        auto mt1 = got::Matrix4x4<float>::translate(got::Vector2<float>(-spriteSize.width / 2.0f, -spriteSize.height / 2.0f));
        auto mr  = got::Matrix4x4<float>::rotate(angle);
        auto mt2 = got::Matrix4x4<float>::translate(got::Vector2<float>(position.x + spriteSize.width / 2.0f, position.y + spriteSize.height / 2.0f));

        mt = mt1 * mr * mt2;
    }

	auto drawRect = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));

	got::SpriteManager::getInstance().draw(spriteName, mt, drawRect, color);
}
// 終了
void Bullet::end()
{
}
// 通常弾
void Bullet::shot(const got::Vector2<float>& vec, const float _dx, const float _dy)
{
    changeMoveFunc(0);

	dx = _dx;
	dy = _dy;
	auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();
	position = got::Vector2<float>(vec.x - spriteSize.width / 2.0f, vec.y - spriteSize.height / 2.0f);
	state = STATE::USE;
    spriteName = defaultBulletName;
}
// 変速弾
void Bullet::changeVelocityShot(const got::Vector2<float>& vec, const float _dx, const float _dy, const float _maxVelocity, const float _dVelocity)
{
    changeMoveFunc(2);

    maxVelocity = _maxVelocity;
    dVelocity   = _dVelocity;
    dx = _dx;
    dy = _dy;
    auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();
    position        = got::Vector2<float>(vec.x - spriteSize.width / 2.0f, vec.y - spriteSize.height / 2.0f);
    state           = STATE::USE;
    spriteName      = defaultBulletName;
}
// 追尾弾
void Bullet::chaseShot(const got::Vector2<float>& startPos, std::shared_ptr<Actor> _target)
{
    changeMoveFunc(1);

    auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();
    position        = got::Vector2<float>(startPos.x - spriteSize.width / 2.0f, startPos.y - spriteSize.height / 2.0f);
    target          = _target;
    state           = STATE::USE;
    spriteName      = "ChaseBullet";
    angle           = 0.0f;
}

void Bullet::changeMoveFunc(const int num)
{
    switch (num) {
    case 0: // 通常の移動
        moveFunc = [&]() {
            auto dTime = Game::getInstance().getDeltaTime();

            position.translate(dx * dTime, dy * dTime);
        };
        break;
    case 1: // 追尾
        moveFunc = [&]() {
            auto dTime = Game::getInstance().getDeltaTime();

            if (target.lock()->getState() == STATE::USE) {
                got::Vector2<float> shotVec(target.lock()->getCenter().x - position.x, target.lock()->getCenter().y - position.y);
                got::Vector2<float> shotVec2(shotVec.normalize());

                
                angle = shotVec2.toAngle() + PI / 2;

                dx = shotVec2.x * 0.25f;
                dy = shotVec2.y * 0.25f;
            }
            else {
                changeMoveFunc(0);
            }

            position.translate(dx * dTime, dy * dTime);
        };
        break;
    case 2:
        moveFunc = [&]() {
            auto dTime = Game::getInstance().getDeltaTime();
            if (dy < 0.5f) {
                dy += 0.0005f;
            }
            
          
            position.translate(dx * dTime, dy * dTime);
        };
        break;
    }

}
