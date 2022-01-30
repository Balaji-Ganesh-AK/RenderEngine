#pragma once

#include "utility/Pch.h"

namespace KREngine
{
	class EEntity;
	/*This is the atomic interface class for all the components*/
	struct IComponents
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
	
	/*Entity is the atomic class for every object in kaar engine*/
	class EEntity
	{
	public:
		EEntity(std::string_view name);
		virtual ~EEntity() = default;
	protected:
		
	private:
		std::vector<IComponents*> SystemsList;
		std::string Name;
	};




}
