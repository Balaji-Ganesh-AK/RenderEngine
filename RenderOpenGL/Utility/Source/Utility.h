#pragma once
#include <stdexcept>


namespace KREngine
{
	class NotImplemented : public std::logic_error
	{
	public:
		NotImplemented(const std::string& additionalInfo = " ") : std::logic_error("Function not yet implemented! " + additionalInfo) { };
	};
}
