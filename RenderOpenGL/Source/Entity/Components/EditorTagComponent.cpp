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

	void FEditorTagSystem::GUIRun(FEntityHandle& currentSelectedEntity) const
	{
		{
			SCOPED_TIMER("Editor Gui ");

			for (FEntityHandle entity : EntityHandles)
			{
				auto& fName = EntityManager::GetComponent<FName>(entity);

				/*ImGui::Selectable gives a hover highlight for free, returns true when clicked, and
				 *draws the row highlighted while it is the selected entity. The id in the label keeps
				 *the row unique (entities often share the default name) and is informative.*/
				const bool bSelected = (entity == currentSelectedEntity);
				const std::string label = fName.Name + " (id " + std::to_string(entity) + ")";
				if (ImGui::Selectable(label.c_str(), bSelected))
				{
					currentSelectedEntity = entity;
				}
			}
		}

	}

	void FName::FromJson(FJson json)
	{
		if(json.contains("Name"))
		{
			Name = json["Name"];
		}
		else
		{
			Name = "FailedToReadFile";
			Logger::Error("Error reading name from map file");
		}
	}


	void FEditorTagSystem::Run()
	{
		
		
	}


	
}
