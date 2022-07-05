#pragma once
#include "utility/CommonUtilityClass.h"
#include "utility/Enums.h"


namespace KREngine
{
	class FSettingsManager : INonCopyableClass
	{
	public:
		void ReadSettingsFromFile() const {}


		const ERenderingAPI& GetRenderingAPI() const
		{
			return RenderingAPI;
		}

		static FSettingsManager& Get()
		{
			static FSettingsManager instance;
			return instance;
		}

	private:
		FSettingsManager() = default;
		ERenderingAPI RenderingAPI = ERenderingAPI::OpenGL;
	};
}
