//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/10/26
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include <memory>
#include <list>
#include "Texture.h"
#include "Vector2.h"
//#include "Game.h"

class Game;
class Actor
{
public:
	Actor();
	Actor(const LPCWSTR name);
	virtual ~Actor();
	virtual bool init();
	virtual void move();
	virtual void draw() const;
	virtual void end();
	//got::Vector2<float> getCenter() const;

	void addChild(std::shared_ptr<Actor>& newChild);
	std::shared_ptr<Actor> getChild(const LPCWSTR _name) const;
	LPCWSTR getName() const;

protected:
	WCHAR name[256];
	std::list<std::shared_ptr<Actor>> children;
	//std::shared_ptr<got::Texture> texture;
	got::Vector2<float> position;

};
