#pragma once
#include "Runtime/Line/Line.h"


namespace KREngine
{

	/*Which transform the gizmo edits (Unreal: W = move, E = rotate, R = scale).*/
	enum class EGizmoMode { Translate, Rotate, Scale };

	struct FGizmo
	{
		friend class FGizmoSystem;
		void SetLocation(FVector location);

		bool bNeedsToRender = true;
		EGizmoMode Mode = EGizmoMode::Translate;
	private:

		std::vector<FLine> Axes{ { FVector{0,0,0}, FVector{10,0,0} , FColor::Red() } ,
			{ FVector{0,0,0}, FVector{0,10,0} , FColor::Green() } ,
			{ FVector{0,0,0},FVector{0,0,10} , FColor::Blue()} };
		std::shared_ptr<FShader> Shader;
		FVertexBuffer* VertexBufferData = nullptr;
		FVertexArray* VertexArray = nullptr;

		//FColor Color{ FColor::Blue() };
		std::vector<float>VertexBuffer;

		/*Per-mode draw ranges (first vertex + vertex count) into the single GL_LINES vertex
		 *buffer, indexed by (int)EGizmoMode. Built once in FGizmoSystem::Init.*/
		int ModeVertexOffset[3] = { 0, 0, 0 };
		int ModeVertexCount[3] = { 0, 0, 0 };

		/*Click-drag interaction state.*/
		int ActiveAxis = -1;        // -1 = none; 0/1/2 = X/Y/Z handle being dragged
		bool bWasMouseDown = false; // edge detection for grabbing a handle
		float LastDragX = 0.0f;     // last cursor pos (framebuffer space) while dragging
		float LastDragY = 0.0f;
	};

	class FGizmoSystem : public FSystem
	{
	public:
		~FGizmoSystem() override;
		void Init() override;
		void Run(const FCameraComponent& mainCamera, const std::shared_ptr<FRenderer>& renderer);
		/*Click-drag manipulation of the selected entity along the gizmo axes (move/rotate/scale per
		 *the current mode). Returns true while the gizmo is using the mouse, so the caller skips
		 *click-to-select that frame.*/
		bool UpdateInteraction(const FCameraComponent& mainCamera, FEntityHandle selectedEntity);
		void End() override;
		void GUIInit() override;
		void GUIRun() override;
		void GUIEnd() override;

		std::filesystem::path DefaultVertexShaderPath = "../Content/Shaders/Source/LineVertexColorVertexShader.GLSL";
		std::filesystem::path DefaultFragmentShaderPath = "../Content/Shaders/Source/LineVertexColorFragmentShader.GLSL";

	private:

	};
}
