//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/11/24
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
	enum class STATE 
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

    // 木構造関係
	void addChild(std::shared_ptr<Actor>& newChild);
	std::shared_ptr<Actor> getChild(const LPCWSTR _name) const;
	std::vector<std::shared_ptr<Actor>>& getChildren();
	LPCWSTR getName() const;
    void setName(const LPCWSTR _name);
	
    void setState(const STATE _state);
	STATE getState() const;
	const got::Rectangle<int>& getRect() const;
    const got::Vector2<float>& getPosition() const;
    const got::Vector2<float> getCenter() const;

protected:
	WCHAR name[256];
	std::vector<std::shared_ptr<Actor>> children;
	got::Vector2<float> position;
	got::Rectangle<int> collisionRect;
	STATE state;
    std::string spriteName;

};
