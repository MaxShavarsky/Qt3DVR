cmake_minimum_required(VERSION 3.5)
project(qt3d_vive_plugin)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH ~/Development/deps/Qt/5.14.2/gcc_64/lib/cmake)

find_package(OpenGL REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS 3DQuick Core Gui Widgets 3DCore 3DExtras 3DRender 3DInput 3DLogic Qml)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(include)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${GLEW_INCLUDE_DIRS})

set(OPENVR_DIR "~/Development/deps/openvr")
include_directories("${OPENVR_DIR}/headers")
link_directories("${OPENVR_DIR}/lib/linux64/libopenvr_api.so")

set(SRC
        scenemodifier.cpp
        offscreenengine.cpp
        offscreensurfaceframegraph.cpp
        texturerendertarget.cpp
        offscreenenginedelegate.cpp
        mainwidget.cpp
        vive.cc
        vive_conversions.cc)

add_definitions(-DQT_NO_KEYWORDS)
add_definitions(-DLINUX -DPOSIX)

qt5_wrap_cpp(MOC_FILES
        scenemodifier.h
        offscreenengine.h
        offscreensurfaceframegraph.h
        texturerendertarget.h
        offscreenenginedelegate.h
        mainwidget.h
        vive.hh
        vive_conversions.hh
        )

set(LIBS
        Qt5::Widgets
        Qt5::3DQuick
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::3DCore
        Qt5::3DExtras
        Qt5::3DInput
        Qt5::3DRender
        Qt5::3DLogic
        Qt5::Qml
        ${OPENVR_DIR}/lib/linux64/libopenvr_api.so
        ${SDL2_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${OPENGL_INCLUDE_DIRS}
        ${OPENGL_gl_LIBRARY}
        )

add_library(qt3d_vive_plugin ${SRC} ${MOC_FILES} ${UIC_FILES})
add_executable(main main.cpp ${SRC} ${MOC_FILES} ${UIC_FILES})

target_link_libraries(qt3d_vive_plugin ${LIBS})
target_link_libraries(main ${LIBS})




