cmake_minimum_required(VERSION 2.8.3)
project(simple_tf)
set(CMAKE_VERBOSE_MAKEFILE no)
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_FLAGS "-O3 -g -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")

find_package(
  catkin REQUIRED
    COMPONENTS
        roscpp
        tf
        tf_conversions
        std_msgs
        geometry_msgs
        sensor_msgs
)

catkin_package(
  CATKIN_DEPENDS 
    roscpp
    std_msgs
    geometry_msgs
    sensor_msgs
)

include_directories(
    ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_listener
    src/simple_tf_listener.cpp
)

target_link_libraries(${PROJECT_NAME}_listener
    ${catkin_LIBRARIES}
)

add_dependencies(${PROJECT_NAME}_listener
    ${catkin_EXPORTED_TARGETS}
)

add_executable(${PROJECT_NAME}_isCaptured
    src/simple_tf_isCaptured.cpp
)

target_link_libraries(${PROJECT_NAME}_isCaptured
    ${catkin_LIBRARIES}
)

add_dependencies(${PROJECT_NAME}_isCaptured
    ${catkin_EXPORTED_TARGETS}
)


add_executable(${PROJECT_NAME}_pass
    src/simple_tf_pass.cpp
)

target_link_libraries(${PROJECT_NAME}_pass
    ${catkin_LIBRARIES}
)

add_dependencies(${PROJECT_NAME}_pass
    ${catkin_EXPORTED_TARGETS}
)