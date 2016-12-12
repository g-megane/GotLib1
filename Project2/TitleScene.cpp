//////////////////////////////////////////////////
// 作成日:2016/10/18
// 更新日:2016/11/9
// 制作者:got
//////////////////////////////////////////////////
#include "TitleScene.h"
#include "MyDirectInput.h"
#include "Fade.h"
#include "Game.h"
#include "XAudio2.h"

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
	position.move(WINDOW_WIDTH / 2.0f - spriteSize.width / 2.0f, WINDOW_HEIGHT / 4);
    got::XAudio2::getInstance().play();
	return true;
}
// 更新
void TitleScene::move()
{
	// シーン遷移(TITLE->MAIN)
	if (got::MyDirectInput::getInstance().keyTrigger(DIK_RETURN)) {
        got::Fade::getInstance().setIsFadeOut(true);
    }
    //TODO:fadeOutに変更する
    if (got::Fade::getInstance().getIsFadeOut()) {
        got::Fade::getInstance().fadeOut(SceneManager::SCENE_NAME::MAIN);
    }
}
// 描画
void TitleScene::draw() const
{
	auto &spriteManager = got::SpriteManager::getInstance();
	auto mt = got::Matrix4x4<float>::translate(position);
	auto color = got::Color<float>();
	auto drawRect = got::Rectangle<int>(got::Vector2<int>(spriteManager.getSprite("Title")->getSize().width, spriteManager.getSprite("Result")->getSize().height));

	got::SpriteManager::getInstance().draw("Title", mt, drawRect, color);

	auto mt2 = got::Matrix4x4<float>::translate(static_cast<float>(WINDOW_WIDTH / 2 - spriteManager.getSprite("PushEnter")->getSize().width / 2), 500.0f);
	//auto mt3 = got::Matrix4x4<float>::translate(position) * mt2;
	auto drawRect2 = got::Rectangle<int>(got::Vector2<int>(spriteManager.getSprite("PushEnter")->getSize().width, spriteManager.getSprite("PushEnter")->getSize().height));

	got::SpriteManager::getInstance().draw("PushEnter", mt2, drawRect2, color);
}
// 終了
void TitleScene::end()
{
}
