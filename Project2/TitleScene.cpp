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
	return false;
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
}
// 終了
void TitleScene::end()
{
}
