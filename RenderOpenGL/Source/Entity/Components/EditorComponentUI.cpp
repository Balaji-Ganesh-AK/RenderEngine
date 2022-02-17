#include "EditorComponentUI.h"

#include "GameManager.h"
#include "TransformComponent.h"
#include "ImGUI/imgui.h"
#include "RenderingSystem/FRenderingSystem.h"
#include "RenderingSystem/Materials.h"
#include "Systems/TextureSystem/TextureManager.h"

namespace KREngine
{
	void FEditorComponentPanelSystem::GUIInit()
	{
	}

	void FEditorComponentPanelSystem::GUIRun()
	{



		{
			if (ImGui::CollapsingHeader("Transform"))
			{
				auto& transformcomponent = EntityManager::GetComponent<FTransformComponent>(0);

				IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Translation", &transformcomponent.Transform.GetLocation().x), "Translation", );


				IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Rotation", &transformcomponent.Transform.GetRotation().x, 1, -360000, 360000), "Rotation", );
				IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Scale", &transformcomponent.Transform.GetScale().x, 1, -360000, 360000), "Scale", );
			}
			ImGui::Separator();


		}


		{
			SCOPED_TIMER("Materials update");
			
			{
				if (ImGui::CollapsingHeader("Material Component"))
				{
					FMaterials& material = EntityManager::GetComponent<FMaterialComponent>(0).Material;
					TextureName = material.DiffuseTexture;
					if (ImGui::BeginCombo("##Texture", TextureName.c_str()))
					{
						std::vector<std::string >TextureNames;
						FApplication::GetTextureManager().GetTextureNames(TextureNames);
						for (const std::string& textureName : TextureNames)
						{
							bool is_selected = FApplication::GetTextureManager().HasTextureName(TextureName);
							if(ImGui::Selectable(textureName.c_str(), is_selected))
							{
								TextureName = textureName;
								material.TextureMap["material.Diffuse"] = FApplication::GetTextureManager().GetTexture(TextureName);
							}
							if (is_selected)
							{

								ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
							}

						}
						ImGui::EndCombo();
					}


				}
				ImGui::Separator();


			}

		}

	}

	void FEditorComponentPanelSystem::GUIStop()
	{
	}
}
