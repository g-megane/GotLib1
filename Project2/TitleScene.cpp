//////////////////////////////////////////////////
// 作成日:2016/10/18
// 更新日:2016/10/18
// 制作者:got
//////////////////////////////////////////////////
#include "TitleScene.h"
#include "MyDirectInput.h"
#include "SceneManager.h"

// コンストラクタ
TitleScene::TitleScene()
{
}
// デストラクタ
TitleScene::~TitleScene()
{
}
// 初期化
bool TitleScene::init()
{
	auto spriteSize = got::SpriteManager::getInstance().getSprite("Title")->getSize();
	position.move(STAGE_WIDTH / 2.0f - spriteSize.width / 2.0f, STAGE_HEIGHT / 4);
	return true;
}
// 更新
void TitleScene::move()
{
	// シーン遷移(TITLE->MAIN)
	if (got::MyDirectInput::getInstance().keyTrigger(DIK_RETURN)) {
		SceneManager::getInstance().changeScene(SceneManager::getInstance().MAIN, true);
	}
}
// 描画
void TitleScene::draw() const
{
	auto &spriteManager = got::SpriteManager::getInstance();
	auto mt = got::Matrix4x4<float>::translate(position);
	auto color = got::Color<float>();
	auto drawRect = got::Rectangle<int>(got::Vector2<int>(spriteManager.getSprite("Result")->getSize().width, spriteManager.getSprite("Result")->getSize().height));

	got::SpriteManager::getInstance().draw("Result", mt, drawRect, color);

	auto mt2 = got::Matrix4x4<float>::translate(STAGE_WIDTH / 2 - spriteManager.getSprite("PushEnter")->getSize().width / 2, 500.0f);
	//auto mt3 = got::Matrix4x4<float>::translate(position) * mt2;
	auto drawRect2 = got::Rectangle<int>(got::Vector2<int>(spriteManager.getSprite("PushEnter")->getSize().width, spriteManager.getSprite("PushEnter")->getSize().height));

	got::SpriteManager::getInstance().draw("PushEnter", mt2, drawRect2, color);
}
// 終了
void TitleScene::end()
{
}
