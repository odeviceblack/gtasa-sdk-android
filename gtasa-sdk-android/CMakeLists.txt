cmake_minimum_required(VERSION 3.10)
project(GTASASdk)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

option(BUILD_SHARED_LIBS "Build shared library" ON)

include(cmake/sources.cmake)
add_library(GTASASdk ${SRC_FILES})

target_include_directories(GTASASdk
	PUBLIC include
	PRIVATE src third_party
)

target_compile_definitions(GTASASdk PRIVATE
	GAME_SDK_BUILD
	$<$<CONFIG:Debug>:GTASA_DEBUG>
	$<$<CONFIG:Release>:GTASA_RELEASE>
)

target_compile_options(GTASASdk PRIVATE
	-ffunction-sections
	-fdata-sections
	$<$<CONFIG:Debug>:-O0 -g3 -ggdb3 -fno-omit-frame-pointer -fno-inline>
	$<$<CONFIG:Release>:-O3 -DNDEBUG -fomit-frame-pointer -fvisibility=hidden -fvisibility-inlines-hidden>
)

target_link_options(GTASASdk PRIVATE
	$<$<CONFIG:Release>:-Wl,--gc-sections -Wl,--strip-all>
)

if(ANDROID)
	set(GLOSS_LIB_PATH ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libGlossHook.a)
	if(EXISTS ${GLOSS_LIB_PATH})
		target_link_libraries(GTASASdk PRIVATE ${GLOSS_LIB_PATH} log)
	endif()
endif()

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/cmake/sources.cmake)
	message(
		FATAL_ERROR
		"Arquivo cmake/sources.cmake não encontrado!\n"
		"Execute: python scripts/generate_sources.py"
	)
endif()
