cmake_minimum_required(VERSION 3.0.2)
project(turtlesim_fay)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

# Ensure this line correctly references your source file
add_executable(turtle_controller src/fay.cpp)

target_link_libraries(turtle_controller ${catkin_LIBRARIES})
