//////////////////////////////////////////////////
// 作成日:2016/10/27
// 更新日:2016/12/19
// 制作者:got
//////////////////////////////////////////////////
#include "Enemy.h"
#include "SpriteManager.h"
#include "ItemManager.h"
#include "Game.h"
#include "EffectManager.h"

// コンストラクタ
Enemy::Enemy()
	: Actor(), time(), time2(), time3()
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
       
	hp = 0;
	dx = 0.1f;
	dy = 0.1f;
    bulletSpeed  = 0.0f;
    shotInterval = 0.0f;

    //TODO:timeの初期化は必要？
	time.reset();
	time2.reset();
    time3.reset();

	state = STATE::UN_USE; 
	
	return true;
}
// 更新
void Enemy::move()
{
	if (state == STATE::UN_USE) { return; }

	auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();
	
    dTime = Game::getInstance().getDeltaTime();

	// 移動
    this->moveFunc();

    // ダメージ表現
    damageEffect();

	// 弾の発射
	if (time2.timeOver(shotInterval)) {
		this->shotFunc();
		time2.reset();
	}
    if (isBoss) {
        if (time3.timeOver(500)) {
            enemyBulletManager->shot4(getShotPosition(), 7, 0.15f);
            time3.reset();
        }
    }
	// ステージ外に出たら消す(Enemyが画面外に完全に出たら)
    //TODO:仮の値
	if (position.x /*spriteSize.width*/ < -100)   { outOfStage(); return; }
	if (position.x > STAGE_WIDTH + 100)           { outOfStage(); return; }
	if (position.y + 100/*spriteSize.height*/< 0) { outOfStage(); return; }
	if (position.y > STAGE_HEIGHT + 100)          { outOfStage(); return; }

}
// 描画
void Enemy::draw() const
{
	if (state == STATE::UN_USE) { return; }
	//TODO:テスト
	auto mt				 = got::Matrix4x4<float>::translate(position);
	auto & spriteManager = got::SpriteManager::getInstance();
	color.RED;
	auto drawRect	     = got::Rectangle<int>(got::Vector2<int>(spriteManager.getSprite(spriteName)->getSize().width, spriteManager.getSprite(spriteName)->getSize().height));

	spriteManager.draw(spriteName, mt, drawRect, color);
}
// 終了
void Enemy::end()
{
}
// ヒットポイントを返す
const int Enemy::getHp() const
{
	return hp;
}
// ダメージ処理を行う
void Enemy::setDamage(const int damage)
{
	hp -= damage;
    color.a = 0.0f;
    // 死んでいる場合
    if (hp <= 0) {
        auto &game = Game::getInstance();

        state = STATE::UN_USE;
        game.addScore(score);
        EffectManager::getInstance().startEffect("Explosion", position);
        std::dynamic_pointer_cast<ItemManager>(game.getRootActor()->getChild(L"ItemManager"))->itemDrop(position);

        // ステージ最後の敵か？
        if (!isBoss) { return; }
        got::Fade::getInstance().setIsFadeOut(true);
        game.setIsNextScene(true);
    }
}
// EnemyManagerがEnemyを動かすのに必要なデータをセットする
void Enemy::setData(const int _hp, const got::Color<float> _color, const std::string& _spriteName, const float _initX, const float _initY, const int _movePattern, const float _dx, const float _dy, const int _shotPattern, const float _bulletSpeed, const float _shotInterval, const int _score, const bool _isBoss)
{
    // データのセット
    hp         = _hp;
    color      = _color;
    spriteName = _spriteName;
    spriteName = _spriteName;
    position.move(_initX, _initY);
    setMovePattern(_movePattern);
    dx = _dx;
    dy = _dy;
    setShotPattern(_shotPattern);
    bulletSpeed  = _bulletSpeed;
    shotInterval = _shotInterval;
    score = _score;
    isBoss = _isBoss;
    rad = static_cast<float>(got::SpriteManager::getInstance().getSprite(spriteName)->getSize().width) / 2;

    auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();
    
    state = STATE::USE;
}
const bool Enemy::getIsBoss() const
{
    return isBoss;
}
void Enemy::outOfStage()
{
    state = STATE::UN_USE;
    // ステージの最後の敵(モブ)の場合
    //TODO:ボスを出現させる
    //if (isBoss) {
    //    //TODO:とりあえずリザルトシーンへ
    //    got::Fade::getInstance().setIsFadeOut(true);
    //    Game::getInstance().setIsNextScene(true);
    //}
}
// 移動処理を行う関数オブジェクトに関数をセット
void Enemy::setMovePattern(const int pattern)
{
    switch (pattern)
    {
    case 0: // 直線移動
        moveFunc = [&]()
        {
            auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();

            position.translate(0.0f, dy * dTime);
        };
        break;
    case 1: // ジグザグ移動
        moveFunc = [&]()
        {
            auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();

            position.translate(dx * dTime, dy * dTime);

            if (time.timeOver(1000.0f)) {
                dx = -dx;
                time.reset();
            }
        };
        break;
    case 2: // ステージの真ん中で折り返し
        moveFunc = [&]()
        {
            auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();

            position.translate(0, dy * dTime);

            if (position.y >= STAGE_HEIGHT / 2 - spriteSize.height) { dy = -dy; }
        };
        break;
    case 3: // 定位置まで移動しその後静止
        moveFunc = [&]()
        {
            auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();

            position.translate(0.0f, dy * dTime);

            if (position.y >= STAGE_HEIGHT / 3 - spriteSize.height) { dy = 0; }
        };
        break;
    case 4: // 左斜め移動
        moveFunc = [&]()
        {
            auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();

            position.translate(-dx * dTime, dy * dTime);
        };
        break;
    case 5: // 右斜め移動
        moveFunc = [&]()
        {
            auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();

            position.translate(dx * dTime, dy * dTime);
        };
        break;
    case 6: // 直進後定位置で左斜めに折り返し
        moveFunc = [&]()
        {
            auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();

            position.translate(dx * dTime, dy * dTime);

            if (position.y >= STAGE_HEIGHT / 2 - spriteSize.height) {
                dx = -0.1f;
                dy = -dy; 
            }
        };
        break;
    case 7: // 直進後定位置で右斜めに折り返し
        moveFunc = [&]()
        {
            auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();

            position.translate(dx * dTime, dy * dTime);

            if (position.y >= STAGE_HEIGHT / 2 - spriteSize.height) {
                dx = 0.1f;
                dy = -dy;
            }
        };
        break;
    }
}
// 弾の発射処理を行う関数オブジェクトに関数をセット
void Enemy::setShotPattern(const int pattern)
{
    switch (pattern)
    {
    case 0: // 直進弾
        shotFunc = [&]() { enemyBulletManager->shot1(getShotPosition(), bulletSpeed); };
        break;
    case 1: // 自機狙い
        shotFunc = [&]() { enemyBulletManager->shot2(getShotPosition(), bulletSpeed); };
        break;
    case 2: // 円形弾
        //TODO:マジックナンバーをやめる
        shotFunc = [&]() { enemyBulletManager->shot3(getShotPosition(), 36, bulletSpeed); };
        break;
    case 3: // 奇数way弾
        //TODO:マジックナンバーをやめる
        shotFunc = [&]() { enemyBulletManager->shot4(getShotPosition(), 7, bulletSpeed); };
        break;
    case 4:
        shotFunc = [&]() { enemyBulletManager->shot5(getCenter(), bulletSpeed); };
        break;
    default:
        break;
    }
}
// 弾の発射位置を返す
got::Vector2<float> Enemy::getShotPosition() const
{
    auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();
    return got::Vector2<float>(position.x + (spriteSize.width / 2), position.y + spriteSize.height);
}

// damage表現
void Enemy::damageEffect()
{
    color.a += 0.1f;
}
