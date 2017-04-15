//////////////////////////////////////////////////
// 作成日:2016/12/27
// 更新日:2016/12/27
// 制作者:got
//////////////////////////////////////////////////
#include "EffectManager.h"

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

bool EffectManager::init()
{
    for (auto& effect : effects) {
        if (!effect->init()) {
            return false;
        }
    }

    return true;
}

void EffectManager::move()
{
    for (auto& effect : effects) {
        effect->move();
    }
}

void EffectManager::draw() const
{
    for (auto& effect : effects) {
        effect->draw();
    }
}

void EffectManager::end()
{
    for (auto& effect : effects) {
        effect->end();
    }
}

void EffectManager::addEffecr(const std::shared_ptr<Effect> newEffect)
{
    effects.emplace_back(newEffect);
}

void EffectManager::startEffect(const std::string& effectName, const got::Vector2<float>& effectPos)
{
    for (auto& effect : effects) {
        if (effect->getName() != effectName)          { continue; }
        if (effect->getState() == Effect::STATE::USE) { continue; }
        effect->startEffect(effectPos);
        return;
    }
}
