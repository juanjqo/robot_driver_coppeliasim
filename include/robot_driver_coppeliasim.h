#pragma once
#include <memory>
#include <thread>
#include <atomic>
#include <Eigen/Dense>
#include <dqrobotics/interfaces/coppeliasim/DQ_CoppeliaSimInterfaceZMQExperimental.h>


using namespace DQ_robotics;

class RobotDriverCoppeliasim
{
private:
    enum STATUS{
        IDLE,
        CONNECTED,
        INITIALIZED,
        DEINITIALIZED,
        DISCONNECTED,
    };
    STATUS current_status_{IDLE};

    enum OPERATION_MODE{
        STEALTH,
        MASTER,
    };
    OPERATION_MODE operation_mode_;

    void _start_echo_robot_state_mode();
    std::thread echo_robot_state_mode_thread_;
    void _start_echo_robot_state_mode_thread();
    std::atomic<bool> finish_echo_robot_state_;
    void _finish_echo_robot_state();

public:


protected:
    std::string ip_;
    std::vector<std::string> jointnames_;
    double simulation_time_{0};
    int port_;
    std::string status_msg_;

    int timeout_{1000};

    std::shared_ptr<DQ_CoppeliaSimInterfaceZMQExperimental> vi_;




    RobotDriverCoppeliasim(const std::string& host = "localhost",
                           const int& rpcPort = 23000,
                           const int& MAX_TIME_IN_MILLISECONDS_TO_TRY_CONNECTION = 1000);

    RobotDriverCoppeliasim(const std::shared_ptr<DQ_CoppeliaSimInterfaceZMQExperimental>& vi);

    virtual void echo_robot_state_mode() = 0;

public:
    std::string get_status_message() const;
    double   get_simulation_time() const;
    int get_port() const;
    std::string get_ip() const;

    void connect();
    void initialize();
    void deinitialize();
    void disconnect();



};


