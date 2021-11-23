#pragma once
#include "utility/Pch.h"
#include <string_view>

namespace KREngine
{
	class EEntity;
	/*This is the atomic interface class for all the components*/
	class IComponents
	{
		
	};


	/*This is the atomic interface class for all the systems*/
	class FGameSystem// NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		virtual ~FGameSystem() = default;
		virtual void Init() = 0;
		virtual void Run() = 0;
		virtual void Stop() = 0;


		virtual void GUIInit() {};
		virtual void GUIRun() {};
		virtual void GUIStop() {};

		const std::string& GetName() const
		{ return Name; }
	private:
		const std::string Name;
	};
	
	/*Entity is the atomic class for every object in kaar engine*/
	class EEntity
	{
	public:
		EEntity(std::string_view name);
		virtual ~EEntity() = default;
	protected:
		
	private:
		std::vector<FGameSystem*> SystemsList;
		std::string Name;
	};




}
