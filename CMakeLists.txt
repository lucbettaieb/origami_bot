cmake_minimum_required(VERSION 2.8.3)
project(origami_bot)

FIND_LIBRARY(WIRINGPI_LIBRARY wiringPi /home/ubuntu/488_ws/src/libraries/wiringPi)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES origami_bot
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)


include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
# add_library(origami_bot
#   src/${PROJECT_NAME}/origami_bot.cpp
# )

# add_dependencies(origami_bot ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(origami_main src/origami_main.cpp)
add_dependencies(origami_main wiringPi)
target_link_libraries(origami_main
  ${catkin_LIBRARIES}
  ${WIRINGPI_LIBRARY}
)

add_executable(motor_test src/motor_test.cpp)
add_dependencies(motor_test wiringPi)
target_link_libraries(motor_test
  ${catkin_LIBRARIES}
  ${WIRINGPI_LIBRARY}
)
