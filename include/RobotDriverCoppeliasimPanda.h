#pragma once
#include <RobotDriverCoppeliasim.h>

class RobotDriverCoppeliasimPanda: public RobotDriverCoppeliasim
{
protected:
    void echo_robot_state_mode() override;
public:
    RobotDriverCoppeliasimPanda(const std::string& host = "localhost",
                           const int& rpcPort = 23000,
                           const int& MAX_TIME_IN_MILLISECONDS_TO_TRY_CONNECTION = 1000);



};


