CMAKE_MINIMUM_REQUIRED(VERSION 2.8.3)

#
# Thanks to SFML for CMakeLists scripts
#



SET(CMAKE_MODULE_PATH ${CMAKE_ROOT}/cmake/)


macro(fim_set_option var default type docstring)
    IF(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()



fim_set_option(CMAKE_BUILD_TYPE Release STRING "Choose the type of build (Debug or Release)")


#fim_set_option(SFML_OPENGL_ES ${OPENGL_ES} BOOL "TRUE to use an OpenGL ES implementation, FALSE to use a desktop OpenGL implementation")

PROJECT(LevelMaker)



FILE(GLOB SOURCES "src/*.cpp")

LIST(APPEND SOURCES ../FriendshipIsMagic/jni/ressources/jsoncpp.cpp)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")


#FIND_PACKAGE(SFML COMPONENTS graphics network audio window system REQUIRED)
FIND_PACKAGE(Box2D)


INCLUDE_DIRECTORIES(
    ../FriendshipIsMagic/jni/ressources/
    )

ADD_DEFINITIONS(
    -std=c++14
    -fpermissive
    )


ADD_EXECUTABLE(
    LevelMaker
    ${SOURCES}
    )

TARGET_LINK_LIBRARIES(
    LevelMaker
    ${BOX2D_LIBRARY}
    )

