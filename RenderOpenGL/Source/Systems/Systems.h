#pragma once
#include <string>

namespace KREngine
{
	

	class System
	{
	public:
		virtual ~System() = default;
		virtual void Init() = 0;
		virtual void Run() = 0;
		virtual void Stop() = 0;

		const std::string& GetName()
		{ return Name; }
	private:
		const std::string Name;
	};
}
