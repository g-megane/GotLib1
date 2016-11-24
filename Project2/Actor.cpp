//////////////////////////////////////////////////
// 作成日:2016/10/26
// 更新日:2016/11/24
// 制作者:got
//////////////////////////////////////////////////
#include "Actor.h"
#include "Game.h"
#include "SpriteManager.h"

// デフォルトコンストラクタ(名無し)
Actor::Actor()
{
	wcscpy_s(name, L"NO_NAME");
}
// コンストラクタ(名前有)
Actor::Actor(const LPCWSTR _name)
{
	// wcspyを使うとコピー先のバッファの容量が指定されないが
	// wcspy_sだと第二引数が確保確保しているバッファの大きさ
	// 分を渡すようになっているこれにより,コピーをする前にコ
	// ピー先に十分な領域があるかどうかをチェックすることが
	// でき、バッファーオーバーランを未然に防ぐことができる
	wcscpy_s(name, _name);
}
// デストラクタ
Actor::~Actor()
{
}
// 初期化
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
// 更新
void Actor::move()
{
	for (auto & child : children) {
		child->move();
	}
}
// 描画
void Actor::draw() const
{
	for (auto & child : children) {
		child->draw();
	}
}
// 終了
void Actor::end()
{
}

// 子要素を追加
void Actor::addChild(std::shared_ptr<Actor>& newChild)
{
	children.emplace_back(newChild);
}
// 子要素の取得
std::shared_ptr<Actor> Actor::getChild(const LPCWSTR _name) const
{
	//TODO:引数がの名前が自分と一致した場合自分を返す
	//if (wcscmp(_name, name) == 0) {
	//	return ;
	//}
	std::shared_ptr<Actor> ActorTmp = nullptr;
	for (auto & child : children) {
		if (lstrcmpW(_name, child->getName()) == 0) {
			return child;
		}
	}
	
	return nullptr;
}
std::vector<std::shared_ptr<Actor>>& Actor::getChildren()
{
	return children;
}
// 名前の取得
LPCWSTR Actor::getName() const
{
	return name;
}

// Actorに名前をセットする
// ※名前を上書きできてしまうので注意！！
void Actor::setName(const LPCWSTR _name)
{
	wcscpy_s(name, _name);
}

void Actor::setState(const STATE _state)
{
	state = _state;
}

Actor::STATE Actor::getState() const
{
	return state;
}

const got::Rectangle<int>& Actor::getRect() const
{
	return collisionRect;
}

const got::Vector2<float>& Actor::getPosition() const 
{
    return position;
}

const got::Vector2<float> Actor::getCenter() const
{
    auto spriteSize = got::SpriteManager::getInstance().getSprite(spriteName)->getSize();
   return got::Vector2<float>(position.x + spriteSize.width / 2, position.y + spriteSize.height / 2);
}

