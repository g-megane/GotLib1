//////////////////////////////////////////////////
// 作成日:2016/10/18
// 更新日:2016/12/14
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
	auto &sm = got::SpriteManager::getInstance();
	position.ZERO;
    choosePos.move(static_cast<float>(WINDOW_WIDTH / 2 - sm.getSprite("ChooseBar")->getSize().width / 2), 500.0f);
    return true;
}
// 更新
void TitleScene::move()
{
    auto &di   = got::MyDirectInput::getInstance();
    auto &fade = got::Fade::getInstance();

    // 選択
    if (di.keyTrigger(DIK_UP)) {
        auto spriteSize = got::SpriteManager::getInstance().getSprite("ChooseBar")->getSize();
        choosePos.move(static_cast<float>(WINDOW_WIDTH / 2 - spriteSize.width / 2), 500.0f);
        return;
    }
    else if (di.keyTrigger(DIK_DOWN)) {
        auto spriteSize = got::SpriteManager::getInstance().getSprite("ChooseBar")->getSize();
        choosePos.move(static_cast<float>(WINDOW_WIDTH / 2 - spriteSize.width / 2), 600.0f);
        return;
    }

	// シーン遷移(TITLE->MAIN or TITLE->OPERATING)
	if (di.keyTrigger(DIK_RETURN)) {
        fade.setIsFadeOut(true);
    }
    if (fade.getIsFadeOut()) {
        fade.fadeOut(choosePos.y <= 550.0f ? SceneManager::SCENE_NAME::MAIN : SceneManager::SCENE_NAME::OPERATING);
    }
}
// 描画
void TitleScene::draw() const
{
	auto &sm = got::SpriteManager::getInstance();
	auto color          = got::Color<float>();
	
    //TODO: 仮背景
    position.ZERO;
    auto mt             = got::Matrix4x4<float>::translate(position);
	auto drawRect       = got::Rectangle<int>(got::Vector2<int>(sm.getSprite("Board")->getSize().width, sm.getSprite("Board")->getSize().height));
	sm.draw("Board", mt, drawRect, color);

    //TODO: タイトルロゴを作って表示
    //mt = got::Matrix4x4<float>::translate(position);
    //drawRect = got::Rectangle<int>(got::Vector2<int>(sm.getSprite("Title")->getSize().width, sm.getSprite("Title")->getSize().height));
    //got::SpriteManager::getInstance().draw("Title", mt, drawRect, color);

    // 選択しているメニューを強調するバー
    mt       = got::Matrix4x4<float>::translate(choosePos);
    drawRect = got::Rectangle<int>(got::Vector2<int>(sm.getSprite("ChooseBar")->getSize().width, sm.getSprite("ChooseBar")->getSize().height));
    sm.draw("ChooseBar", mt, drawRect, color);

    // スタート
	mt       = got::Matrix4x4<float>::translate(static_cast<float>(WINDOW_WIDTH / 2 - sm.getSprite("Start")->getSize().width / 2), 500.0f);
	drawRect = got::Rectangle<int>(got::Vector2<int>(sm.getSprite("Start")->getSize().width, sm.getSprite("Start")->getSize().height));
	sm.draw("Start", mt, drawRect, color);

    // 操作説明
    mt       = got::Matrix4x4<float>::translate(static_cast<float>(WINDOW_WIDTH / 2 - sm.getSprite("Operating")->getSize().width / 2), 600.0f);
	drawRect = got::Rectangle<int>(got::Vector2<int>(sm.getSprite("Operating")->getSize().width, sm.getSprite("Operating")->getSize().height));
	sm.draw("Operating", mt, drawRect, color);
}
// 終了
void TitleScene::end()
{
}
