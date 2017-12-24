//////////////////////////////////////////////////
// 作成日:2016/12/2
// 更新日:2016/12/2
// 制作者:got
//////////////////////////////////////////////////
#include "Fade.h"
#include "..\..\got\Utility\SpriteManager.h"
namespace got
{
    Fade::Fade()
    {
        isFade    = false;
        isFadeOut = false;
        isFadeIn  = false;
        color     = Color<float>::BLACK;   // 色を黒にセット
        alpha     = 0.0f;
        position.ZERO;
    }

    Fade::~Fade()
    {
    }

    bool Fade::fadeIn()
    {
        //if(!isFade) { alpha = 1.0f; }
        isFade = true;

        // ループさせてα値を255から一定時間ごとに下げていく
        alpha  -= 0.01f;
        color.a = alpha;

        // α値が0になったらループを抜けてフェードインの終了を通知
        if (alpha < 0.0f) {
            alpha    = 0.0f;
            isFade   = false;
            isFadeIn = false;
            return true;
        }

        return false;
    }

    bool Fade::fadeOut(SceneManager::SCENE_NAME nextScene, bool isNextSceneInit /*= true*/)
    {

        isFade    = true;
        

        // ループさせてα値を255から一定時間ごとに下げていく
        alpha += 0.01f;
        color.a = alpha;

        // α値が0になったらループを抜けてフェードインの終了を通知
        if (alpha > 1.0f) {
            alpha     = 1.0f;
            isFade    = false;
            isFadeOut = false;
            isFadeIn  = true;
            SceneManager::getInstance().changeScene(nextScene, isNextSceneInit);
            return true;
        }

        return false;
    }

    void Fade::draw()
    {
        auto mt         = got::Matrix4x4<float>::translate(position);
        auto spriteSize = got::SpriteManager::getInstance().getSprite("Board")->getSize();
        auto drawRect   = got::Rectangle<int>(got::Vector2<int>(spriteSize.width, spriteSize.height));
        got::SpriteManager::getInstance().draw("Board", mt, drawRect, color);
    }

    const bool Fade::getIsFade() const
    {
        return isFade;
    }
    void Fade::setIsFade(const bool _isFade)
    {
        isFade = _isFade;
    }
    const bool Fade::getIsFadeOut() const
    {
        return isFadeOut;
    }
    void Fade::setIsFadeOut(const bool _isFadeOut)
    {
        isFadeOut = _isFadeOut;
    }
    const bool Fade::getIsFadeIn() const
    {
        return isFadeIn;
    }
}