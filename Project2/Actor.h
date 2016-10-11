//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/10/11
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include<memory>
#include"Texture.h"
#include"Vector2.h"

class Actor
{
public:
	virtual bool init() = 0;
	virtual void move() = 0;
	virtual void draw() const = 0;

protected:
	std::shared_ptr<got::Texture> texture;
	got::Vector2<float> position;

};