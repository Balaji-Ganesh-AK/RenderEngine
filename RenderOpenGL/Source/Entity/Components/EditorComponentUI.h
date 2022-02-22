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
		FEntityHandle CurrentSelectedEntity {0};
		std::string CurrentDisplayedTexture;
	};
}
