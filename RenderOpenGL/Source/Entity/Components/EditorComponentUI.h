#pragma once
#include "Entity/Entity.h"


namespace KREngine
{
	struct FCameraComponent;
	class FRenderer;
	class FShader;

	class FEditorComponentPanelSystem: public FSystem
	{
	public:
		void GUIInit();
		void GUIRun();
		void GUIStop();

		uint32 GetCurrentSelectedEntity() const
		{
			return CurrentSelectedEntity;
		}

		FEntityHandle& GetCurrentSelectedEntityMutable()
		{
			return CurrentSelectedEntity;
		}
	private:
		std::filesystem::path DefaultVertexShaderPath = "../Content/Shaders/Source/DefaultVertexShader.GLSL";
		std::filesystem::path DefaultFragmentShaderPath = "../Content/Shaders/Source/DefaultFragmentShaderOutliner.GLSL";
		std::shared_ptr<FShader> Shader;
		FEntityHandle CurrentSelectedEntity {0};
		int tempID = 0;
		std::string CurrentDisplayedTexture;
	};
}
