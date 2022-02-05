#pragma once


#include <set>
#include <unordered_map>

#include "utility/Defines.h"
#include "utility/Pch.h"


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
	using EntityUID = std::bitset<MAX_COMPONENTS>;


	/*This is the atomic interface class for all the systems*/
	class FGameSystem// NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		virtual ~FGameSystem() = default;
		virtual void Init() = 0;
		virtual void Run() = 0;
		virtual void Stop() = 0;

#ifdef GUI
		virtual void GUIInit() {}
		virtual void GUIRun() {}
		virtual void GUIStop() {}
#endif


		const std::string& GetName() const
		{ return Name; }
	private:
		const std::string Name;
	};


	/*Static Entity Manager, Used to access all the entity in the engine*/
	class EntityManager 
	{
	public:
		EntityManager();
		~EntityManager();


		FEntityHandle CreateEntity();
	private:
		uint64 EntityCount = { 0 };
		std::queue<FEntityHandle> AvailableHandles;
		std::unordered_map<FEntityHandle, EntityUID> EntityIDLookUp;

	};


	/* A Wrapper class for Entity.*/
	class FEntity
	{
	public:
	

		FEntity(const FEntityHandle& handle);
		~FEntity();
	private:
		FEntity() = delete;
		FEntityHandle EntityHandle;
		EntityUID UID = { 0 };
	};
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
			ComponentTypeArray.reserve(MAX_ENTITIES);
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
			if(EntityToIndexMap.contains(entityHandle))
			{
				
				return ComponentTypeArray[EntityToIndexMap[entityHandle]];
			}
			else
			{
				return nullptr;
			}
		}

	public:
		~ComponentEntityArray() override
		{
			EntityToIndexMap.clear();
			ComponentTypeArray.clear();
			IndexToEntity.clear();
		};
	private:
		std::vector<Component> ComponentTypeArray;

		std::unordered_map<FEntityHandle, size_t> EntityToIndexMap;
		std::unordered_map<size_t, FEntityHandle> IndexToEntity;

		size_t Size;

	};




	class ComponentManager
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

		template <typename ComponentType>
		ComponentType GetComponentType()
		{
			const char* type_name = typeid(ComponentType).name();
			if (ComponentTypes.contains(type_name))
			{
				return ComponentTypes[type_name];
			}
			else
			{
				Logger::Fatal("Component not registered");
				return nullptr;
			}
				
		}

		template <typename ComponentType>
		void AddComponent(FEntityHandle entityHandle, ComponentType component)
		{
			GetComponentType<ComponentType>()->Add(entityHandle, component);
		}

		template <typename ComponentType>
		void RemoveComponent(FEntityHandle entityHandle)
		{
			GetComponentType<ComponentType>()->Remove(entityHandle);
		}

		template <typename ComponentType>
		ComponentType& GetComponent(FEntityHandle entityHandle)
		{
			return GetComponentArray<ComponentType>()->GetData(entityHandle);
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
				return std::static_pointer_cast<ComponentEntityArray<T>>(ComponentArrayPointerMap[typeName]);
			}
			else
			{
				Logger::Fatal("Component not registered");
				return nullptr;
			}
		}

	};

	class System
	{
	public:
		std::set<FEntityHandle> EntityHandles;
	};


	class SystemManager
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
				SystemRegistry.insert({ type_name, system_pointer });
				return  system_pointer;
			}
			return nullptr;
		}
		template<typename SystemType>
		void RegisterSystem(EntityUID uid)
		{
			const char* type_name = typeid(SystemType).name();

			if(SystemRegistry.contains(type_name))
			{
				SystemToEntityUID.insert({type_name, uid});
			}
			else
			{
				Logger::Error("Already register system");
			}
		}


		void OnEntitySignatureChanged(FEntityHandle handle, EntityUID entityUid) 
		{
			for(auto const & system: SystemRegistry)
			{
				auto const& type_name = system.first;
				auto const& system_pointer = system.second;
				auto const& registered_entity_uid = SystemToEntityUID[type_name];

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
		std::unordered_map<const char*, EntityUID> SystemToEntityUID;

		std::unordered_map<const char*, std::shared_ptr<System>> SystemRegistry;
	};
}
