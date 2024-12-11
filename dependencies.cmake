
FIND_PACKAGE(Eigen3 REQUIRED)
FIND_PACKAGE(Threads REQUIRED)
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})
ADD_COMPILE_OPTIONS(-Werror=return-type -Wall -Wextra -Wmissing-declarations -Wredundant-decls -Woverloaded-virtual)


add_library(RobotDriverCoppeliasim
    ${REPOSITORY_DIR}/include/RobotDriverCoppeliasim.h
    ${REPOSITORY_DIR}/src/RobotDriverCoppeliasim.cpp
)
target_link_libraries(RobotDriverCoppeliasim dqrobotics-interface-coppeliasim-zmq)
