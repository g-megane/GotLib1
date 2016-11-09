//////////////////////////////////////////////////
// 作成日:2016/10/18
// 更新日:2016/11/9
// 制作者:got
//////////////////////////////////////////////////
#include "ResultScene.h"
#include "SceneManager.h"
#include "MyDirectInput.h"

// コンストラクタ
ResultScene::ResultScene()
{
}
// デストラクタ
ResultScene::~ResultScene()
{
}
// 初期
bool ResultScene::init()
{
	auto spriteSize = got::SpriteManager::getInstance().getSprite("Result")->getSize();
	position.move(WINDOW_WIDTH / 2.0f - spriteSize.width / 2.0f, WINDOW_HEIGHT / 4.0f);

	return true;
}
// 更新
void ResultScene::move()
{
	// シーン遷移(TITLE->MAIN)
	if (got::MyDirectInput::getInstance().keyTrigger(DIK_RETURN)) {
		SceneManager::getInstance().changeScene(SceneManager::SCENE_NAME::TITLE);
	}
}
// 描画
void ResultScene::draw() const
{
	auto &spriteManager = got::SpriteManager::getInstance();
	auto mt		    = got::Matrix4x4<float>::translate(position);
	auto color		= got::Color<float>();
	auto drawRect	= got::Rectangle<int>(got::Vector2<int>(spriteManager.getSprite("Result")->getSize().width, spriteManager.getSprite("Result")->getSize().height));

	got::SpriteManager::getInstance().draw("Result", mt, drawRect, color);

	auto mt2		 = got::Matrix4x4<float>::translate(static_cast<float>(WINDOW_WIDTH / 2 - spriteManager.getSprite("PushEnter")->getSize().width / 2), 500.0f);
	auto mt3		 = got::Matrix4x4<float>::translate(position) * mt2;
	auto drawRect2	 = got::Rectangle<int>(got::Vector2<int>(spriteManager.getSprite("PushEnter")->getSize().width, spriteManager.getSprite("PushEnter")->getSize().height));

	got::SpriteManager::getInstance().draw("PushEnter", mt2, drawRect2, color);
}
// 終了
void ResultScene::end()
{
}
