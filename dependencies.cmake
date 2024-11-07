
FIND_PACKAGE(Eigen3 REQUIRED)
FIND_PACKAGE(Threads REQUIRED)
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})
ADD_COMPILE_OPTIONS(-Werror=return-type -Wall -Wextra -Wmissing-declarations -Wredundant-decls -Woverloaded-virtual)


add_library(robot_driver_coppeliasim
    ${REPOSITORY_DIR}/include/robot_driver_coppeliasim.h
    ${REPOSITORY_DIR}/src/robot_driver_coppeliasim.cpp
)
target_link_libraries(robot_driver_coppeliasim dqrobotics-interface-coppeliasim)
