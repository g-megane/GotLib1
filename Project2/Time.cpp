﻿//////////////////////////////////////////////////
// 作成日:2016/10/24
// 更新日:2016/10/24
// 制作者:got
//////////////////////////////////////////////////
#include "Time.h"

namespace got
{
	Time::Time()
	{
		start = std::chrono::system_clock::now();
	}

	float Time::getDeltaTime() const
	{
		auto end = std::chrono::system_clock::now();
		return std::chrono::duration<float, std::milli>(end - start).count();
	}

	float Time::getCurrentTime() const
	{
		return std::chrono::duration<float, std::milli>(start.time_since_epoch()).count();
	}

	bool Time::timeOver(const float limit)
	{
		if (limit <= getDeltaTime()) {
			return true;
		}
		return false;
	}
	void Time::reset()
	{
		start = std::chrono::system_clock::now();
	}
}