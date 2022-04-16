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
	for (const std::pair<const EFileExtension, std::string>& command : CommandToStringMap)
	{
		if (command.first == extension)
		{
			return_string = command.second;
			break;
		}
	}
	return return_string;
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

	return EFileExtension::UnKnown;
}


static const std::map<EAssetType, std::string> EAssetToString
{
	{EAssetType::StaticMesh, "StaticMesh"},
	{EAssetType::Texture, "Texture"},
	{EAssetType::Material, "Material"},
	{EAssetType::UnKnown, "Unknown"}


};

std::string ToString(EAssetType AssetType)
{
	for (const auto& string_pair : EAssetToString)
	{
		if (string_pair.first == AssetType)
		{
			return string_pair.second;
		}
	}
	return {};
}

EAssetType StringToAssetType(const std::string& AssetName)
{
	for (const auto& string_pair : EAssetToString)
	{
		if (string_pair.second == AssetName)
		{
			return string_pair.first;
		}
	}

	return EAssetType::UnKnown;
}
