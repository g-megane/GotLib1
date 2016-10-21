//////////////////////////////////////////////////
// 作成日:2016/10/12
// 更新日:2016/10/12
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include<unordered_map>

#include"Singleton.h"
#include"Sprite.h"

namespace got
{
	class SpriteManager : public Singleton<SpriteManager>
	{
	public:
		void addMap(const std::string& key, const std::shared_ptr<Sprite>& sprite);
		void addMap(const std::string& key, const std::wstring& path);

		std::shared_ptr<Sprite> getSprite(std::string key);

		template<class T = float>
		void draw(const std::string& key, const Matrix4x4<float>& matrix, const Rectangle<int>& rect, const Color<T>& color = Color<T>::WHITE)
		{
			spriteMap[key]->draw(matrix, rect, color);
		}

	private:
		friend class Singleton<SpriteManager>;
		SpriteManager();
		
		std::unordered_map<std::string, std::shared_ptr<Sprite>> spriteMap;

	};
}