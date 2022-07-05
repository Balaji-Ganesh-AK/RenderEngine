#pragma once

namespace KREngine
{
	class ISystem
	{
	public:
		virtual ~ISystem() = default;
		virtual void Init() = 0;
		virtual void Run() = 0;
		virtual void End() = 0;
		virtual void GUIInit() = 0;
		virtual void GUIRun() = 0;
		virtual void GUIEnd() = 0;
	};
}
