//////////////////////////////////////////////////
// 作成日:2016/10/11
// 更新日:2016/11/30
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include <memory>
#include <vector>
#include "..\..\got\Utility\Texture.h"
#include "..\..\got\Math\Vector2.h"
#include "..\..\got\Utility\Rectangle.h"

class Game;
class Actor
{
public:
    // Actorの状態
	enum class STATE 
	{
		USE,
		UN_USE,
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
    const got::Vector2<float>& getPosition() const;
    //TODO: 参照に変えれるかも？受け取る側がconst Vector2<float>& なら
    const got::Vector2<float> getCenter() const;
    const float getRad() const;

protected:
	WCHAR name[256];
	std::vector<std::shared_ptr<Actor>> children;
	got::Vector2<float> position;
    float rad;
	STATE state;
    std::string spriteName;

};
