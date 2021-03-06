﻿//////////////////////////////////////////////////
// 作成日:2016/12/27
// 更新日:2016/12/27
// 制作者:got
//////////////////////////////////////////////////
#include "Explosion.h"
#include "..\..\got\Math\Matrix4x4.h"
#include "..\..\got\Utility\SpriteManager.h"
#include "..\..\got\Audio\XAudio2.h"
#include "..\Common\Game.h"

Explosion::Explosion(std::string name)
    : Effect(name)
{

}

Explosion::~Explosion()
{
}

bool Explosion::init()
{
    scale = 0.0f;
    dy    = 0.1f;

    return true;
}

void Explosion::move()
{
    if(state == Effect::STATE::UN_USE) { return; }
    
    position.y += dy * Game::getInstance().getDeltaTime();

    if(scale < 1.0f) { 
        scale += 0.05f;
        return; 
    }
    color.a -= 0.05f;
    if (color.a < 0) {
        state = Effect::STATE::UN_USE;
    }
}

void Explosion::draw() const
{
    if (state == STATE::UN_USE) { return; }

    auto & spriteManager = got::SpriteManager::getInstance();
    auto mt              = got::Matrix4x4<float>::translate(position);
    auto mt1             = got::Matrix4x4<float>::translate(got::Vector2<float>(static_cast<float>(-spriteManager.getSprite(name)->getSize().width / 2), static_cast<float>(-spriteManager.getSprite(name)->getSize().height / 2)));
    auto ms              = got::Matrix4x4<float>::scale(scale);
    auto mt2             = got::Matrix4x4<float>::translate(got::Vector2<float>(position.x + spriteManager.getSprite(name)->getSize().width / 2, position.y + spriteManager.getSprite(name)->getSize().height / 2));

    mt = mt1 * ms * mt2;
    auto drawRect        = got::Rectangle<int>(got::Vector2<int>(spriteManager.getSprite(name)->getSize().width, spriteManager.getSprite(name)->getSize().height));

    got::SpriteManager::getInstance().draw(name, mt, drawRect, color);
}

void Explosion::end()
{
}

void Explosion::startEffect(const got::Vector2<float>& effectPos)
{
    color.a  = 1.0f;
    scale    = 0.0f;
    auto spriteSize = got::SpriteManager::getInstance().getSprite(name)->getSize();
    position.move(effectPos.x - spriteSize.width / 2, effectPos.y - spriteSize.height / 2);
    state    = Effect::STATE::USE;
    got::XAudio2::getInstance().play("Explosion");
}
