//////////////////////////////////////////////////
// 作成日:2016/11/30
// 更新日:2016/11/30
// 制作者:got
//////////////////////////////////////////////////
#include "PauseScene.h"
#include "SceneManager.h"
#include "MyDirectInput.h"
#include "Game.h"

// コンストラクタ
PauseScene::PauseScene()
{
}
// デストラクタ
PauseScene::~PauseScene()
{
}
// 初期化
bool PauseScene::init()
{

    return true;
}
// 更新
void PauseScene::move()
{
    //TODO: 特定のボタンが押されたらポーズシーンを呼んだシーンに戻る
    //      またはタイトルに戻る
    if (got::MyDirectInput::getInstance().keyTrigger(DIK_P)) {
        Game::getInstance().setIsPause(false);
        SceneManager::getInstance().changeScene(SceneManager::getInstance().getBeforeSceneName(), false);
    }
}
// 描画
void PauseScene::draw() const
{

}
// 終了
void PauseScene::end()
{
}
