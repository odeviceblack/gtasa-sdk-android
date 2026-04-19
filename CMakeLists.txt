cmake_minimum_required(VERSION 3.10)
project(GTASASdk VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tipo de build padrão
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Opção para biblioteca compartilhada (ON = .so, OFF = .a)
option(BUILD_SHARED_LIBS "Build shared library" ON)

# Fontes
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Biblioteca principal
add_library(GTASASdk ${SRC_FILES})

# Diretórios de inclusão
target_include_directories(GTASASdk
    PUBLIC include
    PRIVATE src
            src/internal
            third_party
)

# Definições
target_compile_definitions(GTASASdk PRIVATE
    GAME_SDK_BUILD
    $<$<CONFIG:Debug>:GTASA_DEBUG>
    $<$<CONFIG:Release>:GTASA_RELEASE>
)

# Flags de compilação (ajuste conforme necessário)
target_compile_options(GTASASdk PRIVATE
    -ffunction-sections
    -fdata-sections
    $<$<CONFIG:Debug>:-O0 -g3 -ggdb3 -fno-omit-frame-pointer -fno-inline>
    $<$<CONFIG:Release>:-O3 -DNDEBUG -flto -fomit-frame-pointer -fno-exceptions -fno-rtti -fvisibility=hidden -fvisibility-inlines-hidden>
)

# Flags de link
target_link_options(GTASASdk PRIVATE
    $<$<CONFIG:Release>:-Wl,--gc-sections -Wl,--strip-all -flto>
)

# Dependências externas (apenas Android)
if(ANDROID)
    set(GLOSS_LIB_PATH ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libGlossHook.a)
    if(EXISTS ${GLOSS_LIB_PATH})
        target_link_libraries(GTASASdk PRIVATE ${GLOSS_LIB_PATH} log)
    endif()
endif()
