#pragma once
#include "Entity/Entity.h"


namespace KREngine
{
	class FEditorComponentPanelSystem: public FSystem
	{
	public:
		void GUIInit();
		void GUIRun();
		void GUIStop();


	private:

		std::string TextureName;
	};
}
