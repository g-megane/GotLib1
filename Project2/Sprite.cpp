//////////////////////////////////////////////////
// 作成日:2016/10/12
// 更新日:2016/10/12
// 制作者:got
//////////////////////////////////////////////////
#include "Sprite.h"

namespace got
{
	Sprite::Sprite(const std::wstring & path)
	{
		create(path);
	}

	bool Sprite::create(const std::wstring & path)
	{
		if (path.size() == 0) {
			return true;
		}

		texture = std::make_shared<Texture>();
		texture->create(path);

		size = texture->getTextureSize();
		return true;
	}

	Dimention<int> Sprite::getSize() const
	{
		return size;
	}
}