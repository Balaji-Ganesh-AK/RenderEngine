#pragma once
#include "Entity/Entity.h"
#include "RenderOpenGL/Utility/Source/File/FJson.h"


namespace KREngine
{
	class FEditorTagSystem: public FSystem
	{
		public:
			void Init() override;
			void GUIInit() override;
			void Run() override;
			void GUIRun() const;
			
		private:

	};

	struct FName
	{
	public:
		std::string Name{ "Entity" };
		FJson ToJson()
		{
			FJson json;
			json["Name"] = Name;
			return json;
		}

		void FromJson(FJson json);
	};
}
