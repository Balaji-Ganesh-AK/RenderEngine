#pragma once




/*======================================CPP includes=====================*/
#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>
#include <sstream>
#include <thread>
#include <filesystem>
#include "algorithm"
#include "execution"
/*======================================3rd party =====================*/
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_impl_opengl3.h"
#include "../ThirdParty/stb_image.h"



#include "utility/Defines.h"
#include "utility/KRELogger.h"
#include "utility/LogTimer.h"
#include "../utility/Enums.h"
#include "utility/File/Logger.h"
#include "../utility/InputCodes.h"






/*======================================Custom Utility=====================*/

#include "Math/Color.h"
#include "Math/Vec4.h"
#include "Math/Vec3.h"
#include "Math/Vec2.h"
#include "Systems/Input/Input.h"



#include "Systems/Input/Windows/WindowsInput.h"
#include "Entity/Entity.h"