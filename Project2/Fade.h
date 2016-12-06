﻿//////////////////////////////////////////////////
// 作成日:2016/12/2
// 更新日:2016/12/2
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include "Singleton.h"
#include "Color.h"
#include "Vector2.h"
#include "SceneManager.h"

namespace got
{
    class Fade : public Singleton<Fade>
    {
    public:
        ~Fade();

        bool fadeIn();
        bool fadeOut(SceneManager::SCENE_NAME nextScene, bool isnextSceneInit = true);
        void draw();
        const bool getIsFade() const;
        void setIsFade(const bool _isFade);
        const bool getIsFadeOut() const;
        void setIsFadeOut(const bool _isFadeOut);
        const bool getIsFadeIn() const;

    private:
        friend class Singleton<Fade>;
        Fade();

        float alpha;
        bool  isFade;
        bool  isFadeOut;
        bool  isFadeIn;
        Color<float> color;
        Vector2<float> position;

    };
}