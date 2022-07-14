#include "LevelSystem.h"

#include "Entity/Components/EditorTagComponent.h"
#include "Entity/Components/TransformComponent.h"
#include "Material/DefaultMateirals.h"
#include "Material/DefaultUnlitMaterial.h"

/*TODO Saving and loading system needs to be re-worked.*/

namespace  KREngine
{
	FJson operator<<(FJson::reference lhs, const std::string& rhs)
	{
		lhs = rhs;
		return lhs;
	}
	/*TODO This function needs to be re-worked.*/
	FJson FLevel::ToJson()
	{
		FJson json;
		json["FormatVersion"] =  FormatVersion;
		json["LevelName"] <<  MapName;
		json["EntityCount"] = EntityHandles.size();

		
		FJson Entities;
		for (FEntityHandle entity_handle : EntityHandles)
		{
			FJson Entity;
			Entity["EntityID"] = entity_handle;
			if (EntityManager::HasComponent<FName>(entity_handle))
			{
				auto& entity_name = EntityManager::GetComponent<FName>(entity_handle);
				Entity["Name"] = entity_name.Name;
			}


			if (EntityManager::HasComponent<FTransformComponent>(entity_handle))
			{
				auto& transform = EntityManager::GetComponent<FTransformComponent>(entity_handle);
				Entity["TransformComponent"] = transform.ToJson();
			}

			if (EntityManager::HasComponent<DefaultLitMaterialComponent>(entity_handle))
			{
				auto& default_lit_component = EntityManager::GetComponent<DefaultLitMaterialComponent>(entity_handle);
				Entity["DefaultLitMaterialComponent"] = default_lit_component.ToJson();
				
			}
			if (EntityManager::HasComponent<DefaultUnLitMaterialComponent>(entity_handle))
			{
				auto& default_lit_component = EntityManager::GetComponent<DefaultUnLitMaterialComponent>(entity_handle);
				Entity["DefaultUnLitMaterialComponent"] = default_lit_component.ToJson();

			}
		/*	if (EntityManager::HasComponent<DefaultUnLitMaterialComponent>(entity_handle))
			{
				auto& default_lit_component = EntityManager::GetComponent<DefaultUnLitMaterialComponent>(entity_handle);
				Entity["DefaultUnLitMaterialComponent"] = default_lit_component.ToJson();

			}*/
			if (EntityManager::HasComponent<FCameraComponent>(entity_handle))
			{
				auto& component = EntityManager::GetComponent<FCameraComponent>(entity_handle);
				Entity["FCameraComponent"] = component.ToJson();

			}
			Entities += Entity;
		}
		json["Entities"] = Entities;
		return json;
	}

	void FLevel::FromJson(FJson json)
	{
		const FJson& level_data = json["LevelData"];

		if(level_data.contains("FormatVersion"))
		{
			if(FormatVersion != level_data["FormatVersion"])
			{
				Logger::Error("Unsupported format version for map!");
			}
			else
			{
				MapName = level_data["LevelName"];
				const uint32 entity_count	= level_data["EntityCount"];

				for(uint32 i=0; i < entity_count; i++)
				{
					FJson entity_data = level_data["Entities"][i];
					FEntityHandle entity_handle  = 0;
					if(entity_data.contains("EntityID"))
					{
						entity_handle = entity_data["EntityID"];
					}
					else
					{
						Logger::Error("No entity id? something is wrong with the saving data");
					}

					if(entity_data.contains("Name") )
					{

						if(EntityManager::HasComponent<FName>(entity_handle))
						{
							auto& name_component = EntityManager::GetComponent<FName>(entity_handle);
							name_component.FromJson(entity_data);
						}
						else
						{
							Logger::Warning("Missing entity name in map name");
						}
					}

					if (entity_data.contains("TransformComponent"))
					{
						FJson transform_data = entity_data["TransformComponent"];
						if (EntityManager::HasComponent<FTransformComponent>(entity_handle))
						{
							auto& component = EntityManager::GetComponent<FTransformComponent>(entity_handle);
							component.FromJson(transform_data);
						}
						else
						{
							EntityManager::AddComponent(entity_handle, FTransformComponent{});
							auto& component = EntityManager::GetComponent<FTransformComponent>(entity_handle);
							component.FromJson(transform_data);

						}
					}

					if (entity_data.contains("DefaultLitMaterialComponent"))
					{
						FJson default_material_component_json = entity_data["DefaultLitMaterialComponent"];
						if (EntityManager::HasComponent<DefaultLitMaterialComponent>(entity_handle))
						{
							auto& component = EntityManager::GetComponent<DefaultLitMaterialComponent>(entity_handle);
							component.FromJson(default_material_component_json);
						}
						else
						{
							EntityManager::AddComponent(entity_handle, DefaultLitMaterialComponent{});
							auto& component = EntityManager::GetComponent<DefaultLitMaterialComponent>(entity_handle);
							component.FromJson(default_material_component_json);

						}
					}

					if (entity_data.contains("DefaultUnLitMaterialComponent"))
					{
						FJson default_material_component_json = entity_data["DefaultUnLitMaterialComponent"];
						if (EntityManager::HasComponent<DefaultUnLitMaterialComponent>(entity_handle))
						{
							auto& component = EntityManager::GetComponent<DefaultUnLitMaterialComponent>(entity_handle);
							component.FromJson(default_material_component_json);
						}
						else
						{
							EntityManager::AddComponent(entity_handle, DefaultUnLitMaterialComponent{});
							auto& component = EntityManager::GetComponent<DefaultUnLitMaterialComponent>(entity_handle);
							component.FromJson(default_material_component_json);

						}
					}

					if (entity_data.contains("FCameraComponent"))
					{
						FJson component_json = entity_data["FCameraComponent"];
						if (EntityManager::HasComponent<FCameraComponent>(entity_handle))
						{
							auto& component = EntityManager::GetComponent<FCameraComponent>(entity_handle);
							component.FromJson(component_json);
						}
						else
						{
							EntityManager::AddComponent(entity_handle, FCameraComponent{});
							auto& component = EntityManager::GetComponent<FCameraComponent>(entity_handle);
							component.FromJson(component_json);

						}
					}
				}
			}
		}

	}

	void FLevel::AddEntity(FEntityHandle handle)
	{
		EntityHandles.emplace(handle);
	}

	void FLevel::RemoveEntity(FEntityHandle handle)
	{
		EntityHandles.erase(handle);
	}

	std::ostream& operator<<(std::ostream& out, const FLevel& obj)
	{
			return out;
		
	}
}
