cmake_minimum_required(VERSION 3.10)

project(game-sdk)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ========================================
# BUILD TYPE (default = Release)
# ========================================
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# ========================================
# FLAGS BASE (comuns)
# ========================================
set(COMMON_FLAGS "-ffunction-sections -fdata-sections")

# ========================================
# DEBUG
# ========================================
set(CMAKE_CXX_FLAGS_DEBUG
    "-O0 -g -DDEBUG -fno-omit-frame-pointer ${COMMON_FLAGS}"
)

# ========================================
# RELEASE (foco: tamanho + performance)
# ========================================
set(CMAKE_CXX_FLAGS_RELEASE
    "-O3 -DNDEBUG ${COMMON_FLAGS}"
)

# Remove lixo no link (ESSENCIAL)
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE
    "-Wl,--gc-sections -s"
)

# ========================================
# Caminhos
# ========================================
set(SDK_ROOT ${CMAKE_SOURCE_DIR})
set(SRC_DIR ${SDK_ROOT}/src)
set(INCLUDE_DIR ${SDK_ROOT}/include ${SDK_ROOT}/third_party ${SDK_ROOT}/src/internal)
set(LIB_DIR ${SDK_ROOT}/libs)

# ========================================
# Coleta automática de fontes
# ========================================
file(GLOB_RECURSE SRC_FILES
    ${SRC_DIR}/*.cpp
)

# ========================================
# Biblioteca
# ========================================
add_library(game-sdk SHARED ${SRC_FILES})

# ========================================
# Includes
# ========================================
target_include_directories(game-sdk
    PUBLIC
        ${INCLUDE_DIR}
        ${SRC_DIR}
)

# ========================================
# Lib externa (ABI)
# ========================================
set(GLOSS_LIB_PATH ${LIB_DIR}/${ANDROID_ABI}/libGlossHook.a)
set(LOGGER_LIB_PATH ${LIB_DIR}/${ANDROID_ABI}/libLogger.a)

add_library(GlossHook STATIC IMPORTED)
set_target_properties(GlossHook PROPERTIES
    IMPORTED_LOCATION ${GLOSS_LIB_PATH}
)

# ========================================
# DEFINES
# ========================================
target_compile_definitions(game-sdk PRIVATE
    $<$<CONFIG:Debug>:GTASA_DEBUG>
    $<$<CONFIG:Release>:GTASA_RELEASE>
)

# ========================================
# LINK
# ========================================
target_link_libraries(game-sdk
    GlossHook
    log
)
