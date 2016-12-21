//////////////////////////////////////////////////
// 作成日:2016/10/18
// 更新日:2016/11/9
// 制作者:got
//////////////////////////////////////////////////
#include <sstream>
#include <iomanip>
#include "ResultScene.h"
#include "SceneManager.h"
#include "MyDirectInput.h"
#include "Game.h"

// コンストラクタ
ResultScene::ResultScene()
{
}
// デストラクタ
ResultScene::~ResultScene()
{
}
// 初期化
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
    // 情報表示エリアの背景
    auto mt = got::Matrix4x4<float>::translate(position.ZERO);
    auto spriteSize = got::SpriteManager::getInstance().getSprite("Board")->getSize();
    auto color = got::Color<float>::WHITE;
    auto drawRect = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
    got::SpriteManager::getInstance().draw("Board", mt, drawRect, color);

    auto &spriteManager = got::SpriteManager::getInstance();
    mt		    = got::Matrix4x4<float>::translate(position);
    color		= got::Color<float>();
    drawRect	= got::Rectangle<int>(got::Vector2<int>(spriteManager.getSprite("Result")->getSize().width, spriteManager.getSprite("Result")->getSize().height));

	got::SpriteManager::getInstance().draw("Result", mt, drawRect, color);

	auto mt2		 = got::Matrix4x4<float>::translate(static_cast<float>(WINDOW_WIDTH / 2 - spriteManager.getSprite("PushEnter")->getSize().width / 2), 500.0f);
	auto mt3		 = got::Matrix4x4<float>::translate(position) * mt2;
	auto drawRect2	 = got::Rectangle<int>(got::Vector2<int>(spriteManager.getSprite("PushEnter")->getSize().width, spriteManager.getSprite("PushEnter")->getSize().height));

	got::SpriteManager::getInstance().draw("PushEnter", mt2, drawRect2, color);

    // スコア表示
    // 文字
    spriteSize = got::SpriteManager::getInstance().getSprite("Score")->getSize();
    mt = got::Matrix4x4<float>::translate(got::Vector2<float>(STAGE_WIDTH + 25.0f, 260.0f));
    drawRect = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
    got::SpriteManager::getInstance().draw("Score", mt, drawRect, color);

    // 数字
    int b = Game::getInstance().getScore();
    std::ostringstream oss2;
    oss2 << std::setfill('0') << std::setw(6) << b;
    int length = oss2.str().length();

    for (int i = length - 1; i > 0; --i) {
        const auto c = oss2.str().substr(i, 1);
        spriteSize = got::SpriteManager::getInstance().getSprite(c)->getSize();
        mt = got::Matrix4x4<float>::translate(got::Vector2<float>(STAGE_WIDTH + spriteSize.width * i, 310.0f));
        drawRect = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));

        got::SpriteManager::getInstance().draw(c, mt, drawRect, color);
    }
}
// 終了
void ResultScene::end()
{
}
