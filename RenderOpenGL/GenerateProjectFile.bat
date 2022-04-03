call premake5.exe vs2022
cd "%~dp0\AssetLoader\Dependencies\ASSIMPO" 
echo Building Asset importer library from %cd%
call cmake CMakeLists.txt 
PAUSE 