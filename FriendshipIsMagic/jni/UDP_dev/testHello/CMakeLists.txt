PROJECT(FriendshipIsMagic)

SET(CMAKE_MODULE_PATH ${CMAKE_ROOT}/cmake/)

FIND_PACKAGE(SFML COMPONENTS graphics network audio window system REQUIRED)
find_package (Threads)

#FIND_PACKAGE(Box2D)

FILE(GLOB SOURCES "src/**/*.cpp" "src/*.cpp")

ADD_DEFINITIONS(
    -std=c++14
    -fpermissive
    -lpthread
    )

ADD_EXECUTABLE(
    TestHello
    ${SOURCES}
    )

TARGET_LINK_LIBRARIES(
    TestHello
    ${SFML_GRAPHICS_LIBRARY}
    ${SFML_WINDOW_LIBRARY}
    ${SFML_NETWORK_LIBRARY}
    ${SFML_SYSTEM_LIBRARY}
    ${CMAKE_THREAD_LIBS_INIT}
    #${BOX2D_LIBRARY}
)



