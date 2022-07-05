#pragma once


#include <iostream>
#include <map>
#include <string>
#include <vector>


namespace KREngine
{
	enum class ECommand
		: int
	{
		Unknown = -1,
		LoadFBX,
		LoadOBJ,
		Count
		
	};
	
	class FParameters
	{
	public:
		FParameters(int argumentCount, char* arguments[]);
		FParameters();
		/** Set to true once the parameters have been validated */
		bool bValidParameters{ false };

		/*Minimum number of required parameters*/
		/*Example: arguments[0] = AssetLoader.exe, arguments[1] = ECommand*/
		int MinParameterCount {2};
		ECommand CurrentCommand;
		static std::string CommandToString(ECommand command);
		static ECommand StringToECommand(const std::string&  string);
	private:

	};

	FParameters::FParameters(int argumentCount, char* arguments[])
	{
		if (argumentCount < MinParameterCount)
		{
			std::cout<<"Check the argument passed! Does not have required minimum parameter count";
		}
		CurrentCommand = StringToECommand(arguments[1]);

		
	}

	FParameters::FParameters()
	{
	}

	static const std::map<ECommand, std::string> CommandToStringMap
	{
		{ECommand::Unknown, "Unknown"},
		{ECommand::LoadFBX, "LoadFBX"},
		{ECommand::LoadOBJ, "LoadOBJ"},
		{ECommand::Count, "Unknown"},

	};
	std::string FParameters::CommandToString(ECommand command)
	{
		std::string return_string{ "Error Reading ECommand" };
		switch (command)
		{
		case ECommand::Unknown:
			break;
		case ECommand::LoadFBX:
			return_string = "LoadFBX";
			break;
		case ECommand::LoadOBJ:
			return_string = "LoadOBJ";
			break;
		case ECommand::Count:
			return_string = "Count";
			break;

		}
		return return_string;
	}

	ECommand FParameters::StringToECommand(const std::string& string)
	{
		for (const std::pair<const ECommand, std::string>& command : CommandToStringMap)
		{
			if (command.second == string)
			{
				return command.first;
			}
		}
		return ECommand::Unknown;
	}


	
}
