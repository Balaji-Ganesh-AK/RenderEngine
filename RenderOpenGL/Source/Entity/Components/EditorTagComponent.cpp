#include "EditorTagComponent.h"

#include "utility/File/Logger.h"
#include "GameManager.h"



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
		for (FEntityHandle entity : EntityHandles)
		{
			auto& fName = EntityManager::GetComponent<FName>(entity);
			
			ImGui::BulletText("%s", fName.Name.c_str());
		}
		
	}

	void FEditorTagSystem::Run()
	{
		
		
	}


	
}
