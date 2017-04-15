//////////////////////////////////////////////////
// 作成日:2016/12/27
// 更新日:2016/12/27
// 制作者:got
//////////////////////////////////////////////////
#include "Effect.h"

Effect::Effect(std::string _name)
{
    name = _name;
	position.ZERO;
	color.WHITE;
	state = STATE::UN_USE;
}

Effect::~Effect()
{

}

const std::string & Effect::getName() const
{
    return name;
}

const Effect::STATE Effect::getState() const
{
    return state;
}
