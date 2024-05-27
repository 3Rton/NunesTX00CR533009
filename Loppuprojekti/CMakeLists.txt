cmake_minimum_required(VERSION 3.29.0)
project(Loppuprojekti VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")

include(CTest)
enable_testing()

#Add Deps from net
#raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
	include(FetchContent)
	FetchContent_Declare(
		raylib
		GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
        GIT_SHALLOW 1
	)
	FetchContent_MakeAvailable(raylib)
endif()

#raylib cpp wrapper
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
	if (NOT DEFINED RAYLIB_CPP_VERSION)
        set(RAYLIB_CPP_VERSION v5.0.1)
	endif()
	include(FetchContent)
    FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG ${RAYLIB_CPP_VERSION}
    )
	FetchContent_MakeAvailable(raylib_cpp)
endif()

#Jolt Physics engine (Used in Horizon West)
find_package(JoltPhysics QUIET)
if (NOT JoltPhysics_FOUND)
	include(FetchContent)
	FetchContent_Declare(
		JoltPhysics
		GIT_REPOSITORY "https://github.com/jrouwe/JoltPhysics"
		GIT_TAG "v5.0.0"
		SOURCE_SUBDIR "Build"
	)
	FetchContent_MakeAvailable(JoltPhysics)
endif()


#Turn off raylib examples compilation
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#Create main.cpp
add_executable(Loppuprojekti main.cpp)

#Some default vscode cmake things
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

#raylib_cpp compiler version
set_target_properties(Loppuprojekti PROPERTIES CXX_STANDARD 20)


#Included Libs
target_link_libraries(
    Loppuprojekti
	raylib
	raylib_cpp
	Jolt
)

#Lib paths
target_include_directories(Loppuprojekti PUBLIC 
	"${raylib_SOURCE_DIR}/src"
	"${JoltPhysics_SOURCE_DIR}/Jolt"
)

