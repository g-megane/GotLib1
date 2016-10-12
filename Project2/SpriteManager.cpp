//////////////////////////////////////////////////
// 作成日:2016/10/12
// 更新日:2016/10/12
// 制作者:got
//////////////////////////////////////////////////
#include"SpriteManager.h"

namespace got
{
	SpriteManager::SpriteManager()
	{
	}

	void SpriteManager::addMap(const std::string& key, const std::shared_ptr<Sprite>& sprite)
	{
		spriteMap[key] = sprite;
	}
	void SpriteManager::addMap(const std::string& key, const std::wstring& path)
	{
		spriteMap[key] = std::make_shared<Sprite>(path);
	}
	std::shared_ptr<Sprite> SpriteManager::getSprite(std::string key)
	{
		return spriteMap[key];
	}
}