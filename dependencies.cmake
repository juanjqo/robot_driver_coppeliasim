
FIND_PACKAGE(Eigen3 REQUIRED)
FIND_PACKAGE(Threads REQUIRED)
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})
ADD_COMPILE_OPTIONS(-Werror=return-type -Wall -Wextra -Wmissing-declarations -Wredundant-decls -Woverloaded-virtual)


add_library(RobotDriverCoppeliaSim
    ${REPOSITORY_DIR}/include/RobotDriverCoppeliaSim.h
    ${REPOSITORY_DIR}/src/RobotDriverCoppeliaSim.cpp
)
target_link_libraries(RobotDriverCoppeliaSim dqrobotics-interface-coppeliasim-zmq)
