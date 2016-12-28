//////////////////////////////////////////////////
// 作成日:2016/12/27
// 更新日:2016/12/27
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include <vector>
#include "Singleton.h"
#include "Effect.h"

class EffectManager : public got::Singleton<EffectManager>
{
public:
    EffectManager();
    ~EffectManager();

    bool init();
    void move();
    void draw() const;
    void end();

    void addEffecr(const std::shared_ptr<Effect> newEffect);
    void startEffect(const std::string& effectName, const got::Vector2<float>& effectPos);

private:
    friend class got::Singleton<EffectManager>;
    std::vector<std::shared_ptr<Effect>> effects;

};
