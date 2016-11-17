//////////////////////////////////////////////////
// 作成日:2016/10/27
// 更新日:2016/11/16
// 制作者:got
//////////////////////////////////////////////////
#include "Enemy.h"
#include "SpriteManager.h"
#include "Game.h"

// コンストラクタ
Enemy::Enemy()
	: Actor(), time(), time2()
{
}
// デストラクタ
Enemy::~Enemy()
{
}
// 初期化
bool Enemy::init()
{
	auto &root = Game::getInstance().getRootActor();
	enemyBulletManager = std::dynamic_pointer_cast<EnemyBulletManager>(root->getChild(L"EnemyBulletManager"));
   
	auto spriteSize = got::SpriteManager::getInstance().getSprite("Enemy")->getSize();
	position.move(STAGE_WIDTH / 2, static_cast<float>(-spriteSize.height));
    
	//TODO:仮の移動量
    hp = 0;
	dx = 0.1f;
	dy = 0.1f;
    bulletSpeed = 0.0f;
    shotInterval = 0.0f;

    //TODO:timeの初期化は必要？
	time.reset();
	time2.reset();

	state = STATE::UN_USE; //TODO:UN_USEにしておいてEnemyManagerがUSEにする
	
    collisionRect = got::Rectangle<int>(position, spriteSize.width, spriteSize.height);

	return true;
}
// 更新
void Enemy::move()
{
	if (state == STATE::UN_USE) { return; }

	auto spriteSize = got::SpriteManager::getInstance().getSprite("Enemy")->getSize();
	
    dTime = Game::getInstance().getDeltaTime();

	// 移動
    this->moveFunc();

	// 弾の発射
	if (time2.timeOver(shotInterval)) {
		this->shotFunc();
		time2.reset();
	}
	// ステージ外に出たら消す(Enemyが画面外に完全に出たら)
    //TODO:仮の値
	if (position.x /*spriteSize.width*/ < -100)   { setState(STATE::UN_USE); }
	if (position.x > STAGE_WIDTH + 100)           { setState(STATE::UN_USE); }
	if (position.y + 100/*spriteSize.height*/< 0) { setState(STATE::UN_USE); }
	if (position.y > STAGE_HEIGHT + 100)          { setState(STATE::UN_USE); }

}
// 描画
void Enemy::draw() const
{
	if (state == STATE::UN_USE) { return; }
	//TODO:テスト
	auto mt				 = got::Matrix4x4<float>::translate(position);
	auto & spriteManager = got::SpriteManager::getInstance();
	auto color			 = got::Color<float>();
	auto drawRect	     = got::Rectangle<int>(got::Vector2<int>(spriteManager.getSprite("Enemy")->getSize().width, spriteManager.getSprite("Enemy")->getSize().height));

	spriteManager.draw("Enemy", mt, drawRect, color);
}
// 終了
void Enemy::end()
{
}
// ヒットポイントを返す
int Enemy::getHp() const
{
	return hp;
}
// ダメージ処理を行う
void Enemy::setDamage(const int damage)
{
	hp -= damage;
    // 死んでいる場合
	if (hp <= 0) {
		state = STATE::UN_USE;
	}
}
// EnemyManagerがEnemyを動かすのに必要なデータをセットする
void Enemy::setData(const int _hp, const float _initX, const float _initY, const int _movePattern, const int _shotPattern, const float _bulletSpeed, const float _shotInterval)
{
    // データのセット
    hp = _hp;
    position.move(_initX, _initY);
    setMovePattern(_movePattern);
    setShotPattern(_shotPattern);
    bulletSpeed  = _bulletSpeed;
    shotInterval = _shotInterval;

    //TODO:移動量の初期化
    dx = 0.1f;
    dy = 0.1f;

    auto spriteSize = got::SpriteManager::getInstance().getSprite("Enemy")->getSize();
    collisionRect = got::Rectangle<int>(position, spriteSize.width, spriteSize.height);
    
    state = STATE::USE;
}
// 移動処理を行う関数オブジェクトに関数をセット
void Enemy::setMovePattern(const int pattern)
{
    switch (pattern)
    {
    case 0:
        moveFunc = [&]()
        {
            auto spriteSize = got::SpriteManager::getInstance().getSprite("Enemy")->getSize();

            position.translate(0, dy * dTime);
            collisionRect = got::Rectangle<int>(position, spriteSize.width, spriteSize.height);
        };
        break;
    case 1:
        moveFunc = [&]()
        {
            auto spriteSize = got::SpriteManager::getInstance().getSprite("Enemy")->getSize();

            position.translate(dx * dTime, dy * dTime);
            collisionRect = got::Rectangle<int>(position, spriteSize.width, spriteSize.height);

            if (time.timeOver(1000.0f)) {
                dx = -dx;
                time.reset();
            }
        };
        break;
    case 2:
        moveFunc = [&]()
        {
            auto spriteSize = got::SpriteManager::getInstance().getSprite("Enemy")->getSize();

            position.translate(0, dy * dTime);
            collisionRect = got::Rectangle<int>(position, spriteSize.width, spriteSize.height);

            if (position.y >= STAGE_HEIGHT / 2 - spriteSize.height) { dy = -dy; }
        };
        break;
    }
}
// 弾の発射処理を行う関数オブジェクトに関数をセット
void Enemy::setShotPattern(const int pattern)
{
    switch (pattern)
    {
    case 0:
        shotFunc = [&]() { enemyBulletManager->shot1(getShotPosition(), bulletSpeed); };
        break;
    case 1:
        shotFunc = [&]() { enemyBulletManager->shot2(getShotPosition(), bulletSpeed); };
        break;
    case 2:
        //TODO:マジックナンバーをやめる
        shotFunc = [&]() { enemyBulletManager->shot3(getShotPosition(), 36, bulletSpeed); };
        break;
    case 3:
        //TODO:マジックナンバーをやめる
        shotFunc = [&]() { enemyBulletManager->shot4(getShotPosition(), 7, bulletSpeed); };
        break;
    default:
        break;
    }
}
// 弾の発射位置を返す
got::Vector2<float> Enemy::getShotPosition() const
{
	auto spriteSize = got::SpriteManager::getInstance().getSprite("Enemy")->getSize();
	return got::Vector2<float>(position.x + (spriteSize.width / 2), position.y + spriteSize.height);
}
