#pragma once
#include "Entity/Entity.h"


namespace KREngine
{
	class FEditorTagSystem: public FSystem
	{
		public:
			void Init();
			void GUIInit();
			void Run();
			void GUIRun() const;
		private:

	};

	struct FName
	{
	public:
		std::string Name{ "Entity" };
	};
}
