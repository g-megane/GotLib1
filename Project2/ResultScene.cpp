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
#include "XAudio2.h"

// コンストラクタ
ResultScene::ResultScene()
{
    background = std::make_shared<BackGround>("Background");
}
// デストラクタ
ResultScene::~ResultScene()
{
}
// 初期化
bool ResultScene::init()
{
    if (!background->init()) {
        return false;
    }

	auto spriteSize = got::SpriteManager::getInstance().getSprite("Result")->getSize();
	position.move(WINDOW_WIDTH / 2.0f - spriteSize.width / 2.0f, WINDOW_HEIGHT / 4.0f);
    color.WHITE;

	return true;
}
// 更新
void ResultScene::move()
{
    background->move();

	// シーン遷移(TITLE->MAIN)
	if (got::MyDirectInput::getInstance().keyTrigger(DIK_RETURN)) {
        got::XAudio2::getInstance().play("Enter");
		SceneManager::getInstance().changeScene(SceneManager::SCENE_NAME::TITLE);
	}
}
// 描画
void ResultScene::draw() const
{
    background->draw();

    // 情報表示エリアの背景
    auto &spriteManager = got::SpriteManager::getInstance();
    auto mt		    = got::Matrix4x4<float>::translate(position);
    auto drawRect	= got::Rectangle<int>(got::Vector2<int>(spriteManager.getSprite("Result")->getSize().width, spriteManager.getSprite("Result")->getSize().height));

    spriteManager.draw("Result", mt, drawRect, color);

	auto mt2		 = got::Matrix4x4<float>::translate(static_cast<float>(WINDOW_WIDTH / 2 - spriteManager.getSprite("PushEnter")->getSize().width / 2), 500.0f);
	auto mt3		 = got::Matrix4x4<float>::translate(position) * mt2;
	auto drawRect2	 = got::Rectangle<int>(got::Vector2<int>(spriteManager.getSprite("PushEnter")->getSize().width, spriteManager.getSprite("PushEnter")->getSize().height));

    spriteManager.draw("PushEnter", mt2, drawRect2, color);

    // スコア表示
    // 文字
    auto spriteSize = spriteManager.getSprite("Score")->getSize();
    mt = got::Matrix4x4<float>::translate(got::Vector2<float>(STAGE_WIDTH + 25.0f, 260.0f));
    drawRect = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
    spriteManager.draw("Score", mt, drawRect, color);

    // 数字
    int b = Game::getInstance().getScore();
    std::ostringstream oss2;
    oss2 << std::setfill('0') << std::setw(6) << b;
    int length = oss2.str().length();

    for (int i = length - 1; i > 0; --i) {
        const auto c = oss2.str().substr(i, 1);
        spriteSize = spriteManager.getSprite(c)->getSize();
        mt = got::Matrix4x4<float>::translate(got::Vector2<float>(STAGE_WIDTH + spriteSize.width * i, 310.0f));
        drawRect = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));

        spriteManager.draw(c, mt, drawRect, color);
    }
}
// 終了
void ResultScene::end()
{
    background->end();
}
