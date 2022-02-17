#pragma once

#include <array>
#include <set>
#include <unordered_map>

#include "utility/Pch.h"
#include <map>


namespace KREngine
{

	/*TODO: Need optimization*/

	/*We can set all in the engine ini file*/
	using FEntityHandle = std::uint64_t;

	/*MAX ENTITY COUNT this also in engine ini*/
	constexpr FEntityHandle MAX_ENTITIES = 10000;



	/*We can set all in the engine ini file*/
	using ComponentType = std::uint8_t;

	/*MAX ENTITY COUNT this also in engine ini*/
	constexpr ComponentType MAX_COMPONENTS = 50;

	/*We can set all in the engine ini file*/
	/*Signature is used as a UID for the entities.*/
	using ComponentUID = std::bitset<MAX_COMPONENTS>;





	/*A custom Array for holding generic type of components*/
	/*This is a packed array*/
	/*Will only be used by the component manager*/

	class IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;
	};
	template <typename Component>
	class ComponentEntityArray: public IComponentArray
	{
	public:
		ComponentEntityArray(): Size(0)
		{
			
		}

		void Add(FEntityHandle entityHandle, Component component)
		{

			if( EntityToIndexMap.contains(entityHandle))
			{
				Logger::Error("Component Already Exist, not adding it again for %d", entityHandle);
			}
			else
			{
				size_t index = Size;
				EntityToIndexMap[entityHandle] = index;
				IndexToEntity[index] = entityHandle;
				ComponentTypeArray[index] = component;
				++Size;
			}

		}

		void Remove(FEntityHandle entityHandle)
		{
			if(EntityToIndexMap.contains(entityHandle))
			{
				size_t indexRemovedEntity = EntityToIndexMap[entityHandle];
				size_t indexLastEntity = Size - 1;
				ComponentTypeArray[indexRemovedEntity] = ComponentTypeArray[indexLastEntity];


				const FEntityHandle entityLastElement = IndexToEntity[indexLastEntity];
				EntityToIndexMap[entityLastElement] = indexRemovedEntity;
				IndexToEntity[indexRemovedEntity] = entityLastElement;


				EntityToIndexMap.erase(entityHandle);
				IndexToEntity.erase(indexLastEntity);

			}
			else
			{
				Logger::Error("Trying to delete a component which is not added for entity handle %d", entityHandle);
			}
		}
		Component& GetData(FEntityHandle entityHandle)
		{
			Component returnComponent;
			if(EntityToIndexMap.contains(entityHandle))
			{
				
				return  ComponentTypeArray[EntityToIndexMap[entityHandle]];
			}
			else
			{
				Logger::Error("Unknown entity %d", entityHandle);
			}

			return returnComponent;
		}

	public:
		~ComponentEntityArray() override
		{
			EntityToIndexMap.clear();
			
			IndexToEntity.clear();
		}
	private:
		std::array<Component, MAX_ENTITIES> ComponentTypeArray;

		std::unordered_map<FEntityHandle, size_t> EntityToIndexMap;
		std::unordered_map<size_t, FEntityHandle> IndexToEntity;

		size_t Size;

	};




	class FComponentManager
	{
		friend class IComponentArray;
	public:
		template<typename ComponentType>
		void RegisterComponent()
		{
			const char* type_name = typeid(ComponentType).name();

			if(ComponentTypes.contains(type_name))
			{
				Logger::Error("Trying to register a component %s again", type_name);
			}
			else
			{
				ComponentTypes.insert({ type_name, NextComponentTypes });
				++NextComponentTypes;

				ComponentArrayPointerMap.insert({ type_name, std::make_shared<ComponentEntityArray<ComponentType>>() });
			}
		}

		template <typename Component>
		ComponentType GetComponentType()
		{
			const char* type_name = typeid(Component).name();
			if (ComponentTypes.contains(type_name))
			{
				return ComponentTypes[type_name];
			}
			else
			{
				Logger::Fatal("Component not registered");
				return {};
			}
				
		}

		template <typename Component>
		void AddComponent(FEntityHandle entityHandle, Component component)
		{
			GetComponentArray<Component>()->Add(entityHandle, component);
		}

		template <typename Component>
		void RemoveComponent(FEntityHandle entityHandle)
		{
			GetComponentArray<Component>()->Remove(entityHandle);
		}

		template <typename Component>
		Component& GetComponent(FEntityHandle entityHandle)
		{
			return GetComponentArray<Component>()->GetData(entityHandle);
		} 
		

	private:

		std::unordered_map<const char*, ComponentType> ComponentTypes;
		std::unordered_map<const char*, std::shared_ptr<IComponentArray>> ComponentArrayPointerMap;


		ComponentType NextComponentTypes{};


		template<typename T>
		std::shared_ptr<ComponentEntityArray<T>> GetComponentArray()
		{
			const char* typeName = typeid(T).name();

			if(ComponentTypes.contains(typeName))
			{
				auto x = std::static_pointer_cast<ComponentEntityArray<T>>(ComponentArrayPointerMap[typeName]);
				return x;
			}
			else
			{
				Logger::Fatal("Component not registered");
				return nullptr;
			}
		}

	};

	class FSystem
	{
	public:
		std::set<FEntityHandle> EntityHandles;
	};


	class FSystemManager
	{
	public:
		template<typename SystemType>
		std::shared_ptr<SystemType> RegisterSystem()
		{
			const char* type_name = typeid(SystemType).name();
			if(SystemRegistry.contains(type_name))
			{
				Logger::Error("System already registered %d", type_name);
			
			}
			else
			{
				auto system_pointer = std::make_shared<SystemType>();
				SystemRegistry[type_name] =  system_pointer;
				return  system_pointer;
			}
			return nullptr;
		}
		template<typename SystemType>
		void RegisterSystem(ComponentUID uid)
		{
		
		
			if(const char* type_name = typeid(SystemType).name(); SystemRegistry.contains(type_name))
			{
				
				ComponentToComponentUID[type_name] = uid;
				
			}
			else
			{
				Logger::Error("Already register system");
			}
		}

		template<typename Component>
		void SetComponentUID(ComponentUID componentUid)
		{
			const char* type_name = typeid(Component).name();

			if(!ComponentToComponentUID.contains(type_name))
			{
				ComponentToComponentUID[type_name] = componentUid; 
			}
			else
			{
				Logger::Error("Component already exists, not adding it again");
			}
		}
		
		void OnEntitySignatureChanged(FEntityHandle handle, ComponentUID entityUid)
		{
			for(auto const & system: SystemRegistry)
			{
				auto const& type_name = system.first;
				auto const& system_pointer = system.second;
				auto& registered_entity_uid = ComponentToComponentUID[type_name];

				if((entityUid & registered_entity_uid) == registered_entity_uid)
				{
					system_pointer->EntityHandles.insert(handle);
				}
				else
				{
					system_pointer->EntityHandles.erase(handle);
				}
			}
		}
	private:
		std::unordered_map<const char*, ComponentUID> ComponentToComponentUID;
		
		std::unordered_map<const char*, std::shared_ptr<FSystem>> SystemRegistry;
	};


	class FEntityHandler
	{
	public:
		FEntityHandler();
		~FEntityHandler();


		FEntityHandle CreateEntity();

		void DestroyEntity(FEntityHandle entityHandle);

		void SetComponentUID(FEntityHandle EntityHandle, ComponentUID componentUID);

		ComponentUID GetComponentUID(FEntityHandle entityHandle);
		uint64 GetEntityCount() const;

	private:
		uint64 EntityCount = { 0 };
		std::queue<FEntityHandle> AvailableHandles;
		std::array<ComponentUID, MAX_ENTITIES> ComponentUIDList;

	};


	class EntityManager
	{
	public:
		~EntityManager();
	

		static EntityManager& Get()
		{
			static EntityManager Instance;
			return Instance;
		}

		static FEntityHandle CreateEntity()
		{
			return Get().CreateEntityInternal();
		}
		template<typename SystemType>
		static std::shared_ptr<SystemType> RegisterSystem()
		{
			return Get().RegisterSystemInternal<SystemType>();
		}
		template<typename Component>
		static void RegisterComponent()
		{
			Get().RegisterComponentInternal<Component>();
		}

		template <typename Component>
		static void AddComponent(FEntityHandle entityHandle, Component component)
		{
			Get().AddComponentInternal(entityHandle, component);
		}

		template <typename Component>
		static void RemoveComponent(uint64_t entityHandle, Component component)
		{
			Get().RemoveComponentInternal(entityHandle, component);
		}


		template <typename Component>
		static void SetSystemComponents(ComponentUID componentUid)
		{
			Get().SetSystemComponentsInternal<Component>(componentUid);
		}

		template <typename Component>
		static ComponentType GetComponentType()
		{
			return Get().GetComponentTypeInternal<Component>();
		}

		template<typename Component>
		static Component& GetComponent(FEntityHandle entityHandle)
		{
			return Get().GetComponentInternal<Component>(entityHandle);
		}


	

		static uint64 EntityCount()
		{
			return Get().EntityCountInternal();
		}
		
	private:
		EntityManager();

		FEntityHandle CreateEntityInternal();
		template<typename SystemType>
		std::shared_ptr<SystemType> RegisterSystemInternal();
		template<typename Component>
		void RegisterComponentInternal();
		template <typename Component>
		void AddComponentInternal(FEntityHandle entityHandle, Component component);

		template <typename Component>
		void RemoveComponentInternal(uint64_t uint64, Component component);
		


		template<typename Component>
		void SetSystemComponentsInternal(ComponentUID componentUid)
		{
			SystemManager.SetComponentUID<Component>(componentUid);
		}

		template <typename Component>
		ComponentType GetComponentTypeInternal()
		{
			return ComponentManager.GetComponentType<Component>();
		}

		template<typename Component>
		Component& GetComponentInternal(FEntityHandle entityHandle)
		{
			return ComponentManager.GetComponent<Component>(entityHandle);
		}

		/*Gets the current entity count*/
		uint64 EntityCountInternal() const;


		FEntityHandler EntityHandler;
		FSystemManager SystemManager;
		FComponentManager ComponentManager;
	};

	template <typename SystemType>
	std::shared_ptr<SystemType> EntityManager::RegisterSystemInternal()
	{
		return SystemManager.RegisterSystem<SystemType>();
	}

	template <typename Component>
	void EntityManager::RegisterComponentInternal()
	{
		ComponentManager.RegisterComponent<Component>();
	}


	

	template <typename Component>
	void EntityManager::AddComponentInternal(FEntityHandle entityHandle, Component component)
	{
		
		ComponentManager.AddComponent(entityHandle, component);
		ComponentUID UID = EntityHandler.GetComponentUID(entityHandle);
		UID.set(ComponentManager.GetComponentType<Component>(), true);
		EntityHandler.SetComponentUID(entityHandle, UID);
		SystemManager.OnEntitySignatureChanged(entityHandle, UID);
	}

	template <typename Component>
	void EntityManager::RemoveComponentInternal(FEntityHandle entityHandle, Component component)
	{
		ComponentManager.RemoveComponent<Component>(entityHandle);
		ComponentUID UID = EntityHandler.GetComponentUID(entityHandle);
		UID.set(ComponentManager.GetComponentType<Component>(), false);
		EntityHandler.SetComponentUID(entityHandle, UID);
		SystemManager.OnEntitySignatureChanged(entityHandle, UID);
	}


	/* A Wrapper class for Entity.*/
	class FEntity
	{
	public:

		FEntity() = delete;
		explicit FEntity(const FEntityHandle& handle, const std::string name ="");
		~FEntity();

		template <typename Component>
		void AddComponent(Component component)
		{
			EntityManager::AddComponent(EntityHandle, component);
		}

		template <typename Component>
		void RemoveComponent(Component component)
		{
			EntityManager::RemoveComponent(EntityHandle, component);
		}


		const FEntityHandle GetUID() const
		{
			return EntityHandle;
		}
	private:
	
		FEntityHandle EntityHandle;

	};
}
