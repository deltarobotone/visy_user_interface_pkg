cmake_minimum_required(VERSION 2.8.9)
project(visy_user_interface_pkg)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS roscpp geometry_msgs sensor_msgs cv_bridge image_transport visy_sorting_app_pkg)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(OpenCV REQUIRED)

catkin_package(CATKIN_DEPENDS roscpp geometry_msgs sensor_msgs cv_bridge image_transport visy_sorting_app_pkg)

qt5_add_resources(QT_RESOURCES_CPP res.qrc)
qt5_wrap_cpp(QT_MOC_HPP src/main_window.h src/data_exchange_thread.h)

include_directories(src ${catkin_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})

add_executable(
    visy_user_interface
    src/main_window.cpp
    src/data_exchange_thread.cpp
    src/user_interface_main.cpp
    ${QT_RESOURCES_CPP}
    ${QT_MOC_HPP})

target_link_libraries(visy_user_interface ${QT_LIBRARIES} ${catkin_LIBRARIES} Qt5::Widgets)
target_link_libraries(visy_user_interface ${OpenCV_LIBS})
install(TARGETS visy_user_interface RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
