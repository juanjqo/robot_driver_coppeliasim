#include "RobotDriverCoppeliaSim.h"



RobotDriverCoppeliaSim::RobotDriverCoppeliaSim(const std::string& host,
                                               const int& rpcPort,
                                               const int& MAX_TIME_IN_MILLISECONDS_TO_TRY_CONNECTION)
    :operation_mode_{OPERATION_MODE::MASTER}, ip_{host}, port_{rpcPort}, timeout_{MAX_TIME_IN_MILLISECONDS_TO_TRY_CONNECTION}
{
    vi_ = std::make_shared<DQ_CoppeliaSimInterfaceZMQExperimental>();
    //vi_->connect(ip_, port_, timeout_);
}

RobotDriverCoppeliaSim::RobotDriverCoppeliaSim(const std::shared_ptr<DQ_CoppeliaSimInterfaceZMQExperimental> &vi)
    :operation_mode_{OPERATION_MODE::STEALTH}, ip_{"localhost"}, port_{23000}, vi_{vi}

{

}

void RobotDriverCoppeliaSim::after_connect()
{

}



std::string RobotDriverCoppeliaSim::get_status_message() const
{
    return status_msg_;
}

double RobotDriverCoppeliaSim::get_simulation_time() const
{
    return simulation_time_;
}

int RobotDriverCoppeliaSim::get_port() const
{
    return port_;
}

std::string RobotDriverCoppeliaSim::get_ip() const
{
    return ip_;
}





void RobotDriverCoppeliaSim::connect()
{
    if (vi_)
    {
        try
        {
            if (!vi_->connect(ip_, port_, timeout_))
                throw std::runtime_error("Unable to connect to CoppeliaSim.");
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            status_msg_ = "connected!";
            current_status_ = STATUS::CONNECTED;
            after_connect();
        }
        catch (std::exception& e)
        {
            std::cout<<e.what()<<std::endl;
            if (operation_mode_ == OPERATION_MODE::MASTER)
            {
                vi_->stop_simulation();
                //vi_->disconnect();
            }
            current_status_ = STATUS::IDLE;
        }
    }
}


void RobotDriverCoppeliaSim::initialize()
{
    if (current_status_ == STATUS::CONNECTED)
    {
        if (operation_mode_ == OPERATION_MODE::MASTER)
            vi_->start_simulation();
        status_msg_ = "Initialized!";
        current_status_ = STATUS::INITIALIZED;
        _start_echo_robot_state_mode_thread();
    }else{
        std::cerr<<"The driver must be connected before to be initialized. "<<std::endl;
    }
}

void RobotDriverCoppeliaSim::deinitialize()
{
    if (current_status_ == STATUS::INITIALIZED)
    {

        _finish_echo_robot_state();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (echo_robot_state_mode_thread_.joinable())
        {
            echo_robot_state_mode_thread_.join();
        }
        if (operation_mode_ == OPERATION_MODE::MASTER)
            vi_->stop_simulation();
        current_status_ = STATUS::DEINITIALIZED;
        status_msg_ = "Deinitialized!";
    }
}

void RobotDriverCoppeliaSim::disconnect()
{
    //vi_->disconnect();
    current_status_ = STATUS::DISCONNECTED;
    status_msg_ = "Deinitialized!";
}


void RobotDriverCoppeliaSim::_start_echo_robot_state_mode()
{
    while(!finish_echo_robot_state_)
    {
        try
        {
            simulation_time_ = vi_->get_simulation_time();
            echo_robot_state_mode();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        catch (std::exception& e)
        {
            //set_message_window_parameters(true, e.what());
            std::cout<<e.what()<<std::endl;
        }
    }
}

void RobotDriverCoppeliaSim::_start_echo_robot_state_mode_thread()
{
    finish_echo_robot_state_ = false;
    status_msg_ = "Checking echo robot state thread";
    if (echo_robot_state_mode_thread_.joinable())
    {
        echo_robot_state_mode_thread_.join();
    }
    status_msg_ ="Starting echo robot state thread";
    echo_robot_state_mode_thread_ = std::thread(&RobotDriverCoppeliaSim::_start_echo_robot_state_mode, this);
}

void RobotDriverCoppeliaSim::_finish_echo_robot_state()
{
    status_msg_ = "Finishing echo robot state.";
    finish_echo_robot_state_ = true;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}



