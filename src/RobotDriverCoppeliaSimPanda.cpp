#include "RobotDriverCoppeliaSimPanda.h"

RobotDriverCoppeliasimPanda::RobotDriverCoppeliasimPanda(const std::string &host,
                                                         const int &rpcPort,
                                                         const int &MAX_TIME_IN_MILLISECONDS_TO_TRY_CONNECTION)
    :RobotDriverCoppeliaSim(host, rpcPort, MAX_TIME_IN_MILLISECONDS_TO_TRY_CONNECTION)
{

}

void RobotDriverCoppeliasimPanda::echo_robot_state_mode()
{

}
