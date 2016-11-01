//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/10/26
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include <memory>
#include <vector>
#include "Texture.h"
#include "Vector2.h"
#include "Rectangle.h"

class Game;
class Actor
{
public:
	enum State 
	{
		USE,
		UN_USE,
		DEAD,
	};

	Actor();
	Actor(const LPCWSTR name);
	virtual ~Actor();
	virtual bool init();
	virtual void move();
	virtual void draw() const;
	virtual void end();

	void addChild(std::shared_ptr<Actor>& newChild);
	std::shared_ptr<Actor> getChild(const LPCWSTR _name) const;
	std::vector<std::shared_ptr<Actor>>& getChildren();
	LPCWSTR getName() const;
	void setName(const LPCWSTR _name);
	void setState(const State _state);
	State getState() const;
	got::Rectangle<int> getRect() const;

protected:
	WCHAR name[256];
	std::vector<std::shared_ptr<Actor>> children;
	//std::shared_ptr<got::Texture> texture;
	got::Vector2<float> position;
	got::Rectangle<int> rect;
	State state;

};
