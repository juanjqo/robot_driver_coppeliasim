#include <iostream>
#include <robot_driver_coppeliasim_panda.h>
#include <capybara.hpp>

using namespace std;

int main()
{
    RobotDriverCoppeliasimPanda robot;

    robot.connect();
    std::cout<<robot.get_status_message()<<std::endl;
    robot.initialize();
    std::cout<<robot.get_status_message()<<std::endl;
    for (int i=0;i<10;i++)
    {
        Capybara::millidelay(100);
        std::cout<<robot.get_status_message()<<std::endl;
        std::cout<<robot.get_simulation_time()<<std::endl;
    }
    robot.deinitialize();
    std::cout<<robot.get_status_message()<<std::endl;
    robot.disconnect();
    std::cout<<robot.get_status_message()<<std::endl;

    return 0;
}
