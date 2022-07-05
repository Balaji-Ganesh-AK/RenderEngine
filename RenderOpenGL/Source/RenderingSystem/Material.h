#pragma once
namespace KREngine
{
	struct IMaterialComponent
	{
		
	};

	class IMaterial
	{
	public:
		virtual void Init(int& Slot) = 0;
		virtual void Bind(int& Slot) = 0;
		virtual void UnBind() = 0;
		virtual ~IMaterial() = default;

	private:

	};

}
