if(DRACO_CMAKE_TOOLCHAINS_ARM_IOS_COMMON_CMAKE_)
  return()
endif()
set(DRACO_CMAKE_ARM_IOS_COMMON_CMAKE_ 1)

set(CMAKE_SYSTEM_NAME "Darwin")
if(CMAKE_OSX_SDK)
  set(CMAKE_OSX_SYSROOT ${CMAKE_OSX_SDK})
else()
  set(CMAKE_OSX_SYSROOT iphoneos)
endif()
set(CMAKE_C_COMPILER clang)
set(CMAKE_C_COMPILER_ARG1 "-arch ${CMAKE_SYSTEM_PROCESSOR}")
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_COMPILER_ARG1 "-arch ${CMAKE_SYSTEM_PROCESSOR}")

# TODO(tomfinegan): Handle bit code embedding.
