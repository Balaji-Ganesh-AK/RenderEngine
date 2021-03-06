#include "EditorTagComponent.h"

#include "utility/File/Logger.h"
#include "GameManager.h"
#include "ImGUI/imgui.h"


namespace KREngine
{
	void FEditorTagSystem::Init()
	{
	}

	void FEditorTagSystem::GUIInit()
	{
	}

	void FEditorTagSystem::GUIRun() const
	{
		{
			SCOPED_TIMER("Editor Gui ");

			for (FEntityHandle entity : EntityHandles)
			{
				auto& fName = EntityManager::GetComponent<FName>(entity);

				ImGui::BulletText("%s", fName.Name.c_str());
			}
		}
		
	}

	void FEditorTagSystem::Run()
	{
		
		
	}


	
}
