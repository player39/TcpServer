project(TCPServerC)
CMAKE_MINIMUM_REQUIRED(VERSION 3.11)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)
SET(3RDPARTY_DIR "C:/3rdpart")
FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE(Qt5Core)
FIND_PACKAGE(Qt5Gui)
FIND_PACKAGE(Qt5Network)
file(GLOB UI_Files *.ui)
file(GLOB Header_Files *.h)
file(GLOB CPP_Files *.cpp)
qt5_wrap_ui(WRAP_FILES ${UI_Files})
INCLUDE_DIRECTORIES(
${Qt5Widgets_INCLUDE_DIRS}
${Qt5Core_INCLUDE_DIRS}
${Qt5Gui_INCLUDE_DIRS}
${Qt5Network_INCLUDE_DIRS}
)
add_executable(TCPServerC ${Header_Files} ${CPP_Files} ${WRAP_FILES})
target_link_libraries(TCPServerC Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Network)