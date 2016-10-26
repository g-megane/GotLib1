#include "Actor.h"
//////////////////////////////////////////////////
// 作成日:2016/10/26
// 更新日:2016/10/26
// 制作者:got
//////////////////////////////////////////////////

Actor::Actor()
{
	wcscpy_s(name, L"NO_NAME");
}

Actor::Actor(const LPCWSTR _name)
{
	// wcspyを使うとコピー先のバッファの容量が指定されないが
	// wcspy_sだと第二引数が確保確保しているバッファの大きさ
	// 分を渡すようになっているこれにより,コピーをする前にコ
	// ピー先に十分な領域があるかどうかをチェックすることが
	// でき、バッファーオーバーランを未然に防ぐことができる
	wcscpy_s(name, _name);
}

Actor::~Actor()
{
}

bool Actor::init()
{
	for (auto & child : children) {
		if (!child->init()) {
			//TODO:初期化に失敗した時の処理
			continue;
		}
	}

	return true;
}

void Actor::move()
{
	for (auto & child : children) {
		child->move();
	}
}

void Actor::draw() const
{
	for (auto & child : children) {
		child->draw();
	}
}

void Actor::end()
{
}

void Actor::addChild(std::shared_ptr<Actor>& newChild)
{
	children.emplace_back(newChild);
}

std::shared_ptr<Actor> Actor::getChild(const LPCWSTR _name) const
{
	//TODO:引数がの名前が自分と一致した場合自分を返す
	//if (wcscmp(_name, name) == 0) {
	//	return ;
	//}
	std::shared_ptr<Actor> ActorTmp = nullptr;
	for (auto & child : children) {
		if (_name == child->getName()) {
			return child;
		}
	}
	
	return nullptr;
}

LPCWSTR Actor::getName() const
{
	return name;
}

//const Actor * Actor::getRootActor() const
//{
//	if()
//	return ;
//}
