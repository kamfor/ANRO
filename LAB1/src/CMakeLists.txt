# %Tag(FULLTEXT)%
cmake_minimum_required(VERSION 2.8.3)
project(turtle_keypad)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(turtle src/turtle.cpp)
target_link_libraries(turtle ${catkin_LIBRARIES})
add_dependencies(turtle turtle_keypad_generate_messages_cpp)

# %EndTag(FULLTEXT)%
