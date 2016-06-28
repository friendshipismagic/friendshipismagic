CMAKE_MINIMUM_REQUIRED(VERSION 2.8.3)

#
# Thanks to SFML for CMakeLists scripts
#



SET(CMAKE_MODULE_PATH ${CMAKE_ROOT}/cmake/Modules)

SET(FIM_COMPILE_ANDROID FALSE CACHE BOOL "Compile the project for android and generate a .apk")



macro(fim_set_option var default type docstring)
    IF(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()



fim_set_option(CMAKE_BUILD_TYPE Release STRING "Choose the type of build (Debug or Release)")

fim_set_option(ANDROID_API_MIN 9 STRING "Choose the Android API level to be used (minimum 9)")

set(ANDROID_NATIVE_API_LEVEL ${ANDROID_API_MIN}) # TOOLCHAIN 


# define the path to the Android NDK
fim_set_option(ANDROID_NDK "$ENV{ANDROID_NDK}" PATH "Path to the Android NDK")

# define the STL implementation to be used
fim_set_option(ANDROID_STL c++_shared STRING "Choose the STL implementation to be used (experimental)")


# default the ABI to ARM v7a for hardware floating point
if(NOT ANDROID_ABI)
    set(ANDROID_ABI armeabi-v7a)
endif()


if(SFML_OS_ANDROID)
    set(BUILD_SHARED_LIBS TRUE)
    set(LIB_SUFFIX "/${ANDROID_ABI}")

    # pass shared STL configuration (if any)
    if (ANDROID_STL MATCHES "_shared")
        add_definitions("-DSTL_LIBRARY=${ANDROID_STL}")
    endif()
else()
    unset(ANDROID_ABI CACHE)
    unset(ANDROID_API_MIN CACHE)
    unset(ANDROID_STL CACHE)
    unset(ANDROID_NATIVE_API_LEVEL CACHE)
unset(ANDROID_NDK CACHE)

endif()


#fim_set_option(SFML_OPENGL_ES ${OPENGL_ES} BOOL "TRUE to use an OpenGL ES implementation, FALSE to use a desktop OpenGL implementation")

PROJECT(FriendshipIsMagic)

include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake)


FILE(GLOB SOURCES jni/*/*.cpp )
FILE(GLOB ANDROID_SRC jni/android/*.cpp)

LIST(REMOVE_ITEM SOURCES ${ANDROID_SRC})



set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")


#if(not(SFML_OS_ANDROID))

FIND_PACKAGE(SFML COMPONENTS graphics network audio window system REQUIRED)
FIND_PACKAGE(Box2D)
find_package (Threads)

INCLUDE_DIRECTORIES(
	${SFML_INCLUDE_DIR}
	${BOX2D_INCLUDE_DIRS}
)

    ADD_DEFINITIONS(
        -std=gnu++11
        -fpermissive
        )


    ADD_EXECUTABLE(
        FriendshipIsMagic
        ${SOURCES}
        )

    TARGET_LINK_LIBRARIES(
        FriendshipIsMagic
        ${SFML_GRAPHICS_LIBRARY}
        ${SFML_WINDOW_LIBRARY}
        ${SFML_NETWORK_LIBRARY}
        ${SFML_AUDIO_LIBRARY}
        ${SFML_SYSTEM_LIBRARY}
        ${BOX2D_LIBRARY}
        ${CMAKE_THREAD_LIBS_INIT}
    )

