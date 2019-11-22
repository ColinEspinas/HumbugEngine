cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

PROJECT(HumbugEngine)

find_package(OpenGL REQUIRED)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

#
# Dependencies
#

#
# ULTRALIGHT
#
set(ULTRALIGHT_DIR_SDK "deps/ultralight")
set(ULTRALIGHT_INCLUDE_DIR "${ULTRALIGHT_DIR_SDK}/include")
set(ULTRALIGHT_LIBRARY_DIR "${ULTRALIGHT_DIR_SDK}/lib")
set(ULTRALIGHT_BIN_DIR "${ULTRALIGHT_DIR_SDK}/bin")

find_library(ULTRALIGHT_LIBRARY NAMES Ultralight.lib PATHS "${ULTRALIGHT_LIBRARY_DIR}" DOC "Ultralight library")
find_library(ULTRALIGHTCORE_LIBRARY NAMES UltralightCore.lib PATHS "${ULTRALIGHT_LIBRARY_DIR}" DOC "Ultralight Core library")
find_library(WEBCORE_LIBRARY NAMES WebCore.lib PATHS "${ULTRALIGHT_LIBRARY_DIR}" DOC "Ultralight WebCore library")
find_library(APPCORE_LIBRARY NAMES AppCore.lib PATHS "${ULTRALIGHT_LIBRARY_DIR}" DOC "Ultralight AppCore library")

file(COPY ${ULTRALIGHT_BIN_DIR} DESTINATION ${CMAKE_BINARY_DIR})

#
# GLEW
#
add_definitions(-DGLEW_STATIC)
add_subdirectory(deps/glew EXCLUDE_FROM_ALL)


#
# OpenAL
#
set(OPENAL_DIR_SDK "deps/OpenAL")
set(OPENAL_INCLUDE_DIR "${OPENAL_DIR_SDK}/include")
set(OPENAL_LIBRARY_DIR "${OPENAL_DIR_SDK}/libs/Win64")

find_library(OPENAL_LIBRARY NAMES OpenAL32.lib PATHS "${OPENAL_LIBRARY_DIR}" DOC "OpenAL library")
#set_target_properties(${OPENAL_LIBRARY} PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")


#
# sndfile
#
set(SNDFILE_DIR_SDK "deps/Sndfile")
find_library(SNDFILE_LIBRARY NAMES libsndfile-1.lib PATHS "${SNDFILE_DIR_SDK}" DOC "sndfile library")


#
# Headers
#
include_directories(
    ${PROJECT_SOURCE_DIR}/include
	${ULTRALIGHT_INCLUDE_DIR}
	${OPENAL_INCLUDE_DIR}
	${SNDFILE_DIR_SDK}

)

#
# Sources
#
file(GLOB PROJECT_SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} WIN32 ${PROJECT_SOURCES})

target_link_libraries(
	${PROJECT_NAME}
	${OPENGL_LIBRARIES}
	libglew_static
	${ULTRALIGHT_LIBRARY}
	${ULTRALIGHTCORE_LIBRARY}
	${WEBCORE_LIBRARY}
	${APPCORE_LIBRARY}
	${OPENAL_LIBRARY}
	${SNDFILE_LIBRARY}
)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})