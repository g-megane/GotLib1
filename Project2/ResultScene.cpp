//////////////////////////////////////////////////
// 作成日:2016/10/18
// 更新日:2016/10/18
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
	return false;
}
// 更新
void ResultScene::move()
{
	// シーン遷移(TITLE->MAIN)
	if (got::MyDirectInput::getInstance().keyTrigger(DIK_RETURN)) {
		SceneManager::getInstance().changeScene(SceneManager::TITLE);
	}
}
// 描画
void ResultScene::draw() const
{
}
// 終了
void ResultScene::end()
{
}
