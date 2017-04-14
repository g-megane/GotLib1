//////////////////////////////////////////////////
// 作成日:2016/12/27
// 更新日:2016/12/27
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include <string>
#include "Vector2.h"
#include "Color.h"

class Effect
{
public:
    enum class STATE
    {
        USE,
        UN_USE,
    };

    Effect(std::string _name);
    virtual ~Effect();
    virtual bool init() = 0;
    virtual void move() = 0;
    virtual void draw() const = 0;
    virtual void end() = 0;
    virtual void startEffect(const got::Vector2<float>& effectPos) = 0;

    const std::string& getName() const;
    const STATE getState() const;

protected:
    got::Vector2<float> position;
    got::Color<float>   color;
    std::string name;
    STATE state;

};