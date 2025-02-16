cmake_minimum_required(VERSION 3.7)
set(CMAKE_C_STANDARD 90)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Jumpio VERSION 1.0)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

option(LOG_COLORFUL "Logging messages will be in different colors" ON)

if(LOG_COLORFUL)
	add_definitions(-DLOG_USE_COLOR)
endif()

add_definitions(-DASSET_PATH=\"${CMAKE_SOURCE_DIR}/assets\")
add_definitions(-DSHADER_PATH=\"${CMAKE_SOURCE_DIR}/shaders\")

set(SOURCES
src/main.c
src/test.c
src/test.h
src/application/app.c
src/application/app.h
src/engine/audio.c
src/engine/audio.h
src/engine/filesystem.c
src/engine/filesystem.h
src/engine/common.c
src/engine/common.h
src/engine/data_types.h
src/engine/engine.h
src/engine/input.c
src/engine/input.h
src/engine/log.c
src/engine/log.h
src/engine/time.c
src/engine/time.h
src/engine/zone.c
src/engine/zone.h
src/engine/renderer/font.c
src/engine/renderer/font.h
src/engine/renderer/r_shader.c
src/engine/renderer/r_shader.h
src/engine/renderer/renderer2D.c
src/engine/renderer/renderer2D.h
vendor/glad/src/glad.c)

add_executable(Jumpio ${SOURCES})

target_include_directories(Jumpio PRIVATE vendor/SDL3/include)
target_include_directories(Jumpio PRIVATE vendor/glad/include)
target_include_directories(Jumpio PRIVATE vendor/cglm/include)
target_include_directories(Jumpio PRIVATE vendor/freetype/include)
target_include_directories(Jumpio PRIVATE src)

target_link_libraries(Jumpio ${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3/lib/x64/SDL3.lib)
target_link_libraries(Jumpio ${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3/lib/x64/SDL3_mixer.lib)
target_link_libraries(Jumpio ${CMAKE_CURRENT_SOURCE_DIR}/vendor/cglm/lib/cglm.lib)
target_link_libraries(Jumpio ${CMAKE_CURRENT_SOURCE_DIR}/vendor/freetype/lib/freetype.lib)