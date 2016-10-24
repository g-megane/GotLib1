//////////////////////////////////////////////////
// 作成日:2016/10/24
// 更新日:2016/10/24
// 制作者:got
//////////////////////////////////////////////////
#pragma once
#include <chrono>

namespace got
{
	class Time
	{
	public:
		Time();
		float getDeltaTime() const;
		float getCurrentTime() const;
		bool  timeOver(const float limit);
		void  reset();

	private:
		std::chrono::time_point<std::chrono::system_clock> start;
		//float deltaTime;
	};
}