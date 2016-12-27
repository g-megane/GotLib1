//////////////////////////////////////////////////
// 作成日:2016/10/21
// 更新日:2016/11/30
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include <string>
#include "Actor.h"

class Bullet : public Actor
{
public:
	Bullet(const std::string& _spriteName);
	~Bullet() override;

	bool init() override;
	void move() override;
	void draw() const override;
	void end() override;

	void shot(const got::Vector2<float>& vec, const float _dx, const float _dy);
    void shot(const float _x, const float _y, const float _dx, const float _dy);
    void chaseShot(const got::Vector2<float>& startPos, std::shared_ptr<Actor> _target);

private:
	float dx;
	float dy;
    bool isChase;
    float beforeAngle;
    const std::string defaultBulletName;
    got::Vector2<float>  targetPos;
    std::weak_ptr<Actor> target;
    got::Color<float>    color;

};