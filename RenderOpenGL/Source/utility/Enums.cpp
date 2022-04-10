#include "Enums.h"

#include <map>
#include <string>

static const std::map<EFileExtension, std::string> CommandToStringMap
{
	{EFileExtension::StaticMesh, ".staticmesh"},
	{EFileExtension::UnKnown, "Unknown"}


};
std::string FileExtensionToString(EFileExtension extension)
{
	std::string return_string = "Unknown";
	switch (extension)
	{
	case EFileExtension::StaticMesh:
		return_string = ".staticmesh";
		break;
	case EFileExtension::UnKnown:
	default:
		return_string = "Unknown";

		return  return_string;
	}
}

EFileExtension StringToFileExtension(const std::string& extension)
{
	for (const std::pair<const EFileExtension, std::string>& command : CommandToStringMap)
	{
		if (command.second == extension)
		{
			return command.first;
		}
	}

	return EFileExtension();
}
