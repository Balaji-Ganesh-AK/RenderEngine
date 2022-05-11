#include "EditorComponentUI.h"

#include "EditorTagComponent.h"
#include "GameManager.h"
#include "TransformComponent.h"
#include "ImGUI/imgui.h"
#include "Material/DefaultMateirals.h"
#include "Material/DefaultUnlitMaterial.h"
#include "RenderingSystem/FRenderingSystem.h"
#include "RenderingSystem/Material.h"
#include "Systems/TextureSystem/TextureManager.h"
#include "glm/gtx/transform.hpp"
#include <glm/glm.hpp>

#include "Editor/Gizmo.h"
#include "RenderingSystem/FRenderer.h"
#include "RenderingSystem/WindowsWindow.h"
#include "Runtime/Line/Line.h"

namespace KREngine
{
	void FEditorComponentPanelSystem::GUIInit()
	{
	
	}





	void FEditorComponentPanelSystem::GUIRun()
	{

		if ( EntityManager::EntityCount() > 0)
		{

			/*Needs to go when we have mouse picking.*/
			IMGUI_LEFT_LABEL(ImGui::InputInt("##Entity ID", &tempID), "Entity ID", );
			CurrentSelectedEntity = tempID;



			if (EntityManager::HasComponent<FName>(CurrentSelectedEntity))
			{
				if (ImGui::CollapsingHeader("Entity Name"))
				{

					auto& fName = EntityManager::GetComponent<FName>(CurrentSelectedEntity);

					ImGui::BulletText("%s", fName.Name.c_str());
				}
			}
			ImGui::Separator();
			if (EntityManager::HasComponent<FTransformComponent>(CurrentSelectedEntity) && !EntityManager::HasComponent<FGizmo>(CurrentSelectedEntity))
			{
				if (ImGui::CollapsingHeader("Transform"))
				{

					auto& transformcomponent = EntityManager::GetComponent<FTransformComponent>(CurrentSelectedEntity);

					IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Translation", &transformcomponent.Transform.GetLocation().x), "Translation", );


					IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Rotation", &transformcomponent.Transform.GetRotation().x, 1, -360000, 360000), "Rotation", );
					IMGUI_LEFT_LABEL(ImGui::DragFloat3("##Scale", &transformcomponent.Transform.GetScale().x, 1, -360000, 360000), "Scale", );
				}
			}
			ImGui::Separator();

			
			{
				SCOPED_TIMER("Materials update");
				if (EntityManager::HasComponent<DefaultLitMaterialComponent>(CurrentSelectedEntity))
				{
					if (ImGui::CollapsingHeader("Material Component"))
					{
						FDefaultLitMaterial& material = EntityManager::GetComponent<DefaultLitMaterialComponent>(CurrentSelectedEntity).Material;
						auto& name = EntityManager::GetComponent<FName>(CurrentSelectedEntity);
						CurrentDisplayedTexture = material.TextureRenderNameToTexturePath["material.Diffuse"];
						if (ImGui::BeginCombo("##Texture", CurrentDisplayedTexture.c_str()))
						{
							std::vector<std::string >TextureNames;
							FApplication::GetTextureManager().GetTextureNames(TextureNames);
							for (const std::string& textureName : TextureNames)
							{
								bool is_selected = FApplication::GetTextureManager().HasTextureName(CurrentDisplayedTexture);
								if (ImGui::Selectable(textureName.c_str(), is_selected))
								{
									CurrentDisplayedTexture = textureName;
									material.TextureRenderNameToTextureMap["material.Diffuse"] = FApplication::GetTextureManager().GetTexture(CurrentDisplayedTexture);
									material.TextureRenderNameToTexturePath["material.Diffuse"]= CurrentDisplayedTexture;
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


				if (EntityManager::HasComponent<DefaultUnLitMaterialComponent>(CurrentSelectedEntity))
				{
					if (ImGui::CollapsingHeader("Material Component"))
					{
						auto& material = EntityManager::GetComponent<DefaultUnLitMaterialComponent>(CurrentSelectedEntity).Material;
						CurrentDisplayedTexture = material.u_Texture;
						if (ImGui::BeginCombo("##Texture", CurrentDisplayedTexture.c_str()))
						{
							std::vector<std::string >TextureNames;
							FApplication::GetTextureManager().GetTextureNames(TextureNames);
							for (const std::string& textureName : TextureNames)
							{
								bool is_selected = FApplication::GetTextureManager().HasTextureName(CurrentDisplayedTexture);
								if (ImGui::Selectable(textureName.c_str(), is_selected))
								{
									CurrentDisplayedTexture = textureName;
									material.TextureRenderNameToTextureMap["Material.BaseTexture"] = FApplication::GetTextureManager().GetTexture(CurrentDisplayedTexture);
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


	}

	void FEditorComponentPanelSystem::GUIStop()
	{
	}

	
}
