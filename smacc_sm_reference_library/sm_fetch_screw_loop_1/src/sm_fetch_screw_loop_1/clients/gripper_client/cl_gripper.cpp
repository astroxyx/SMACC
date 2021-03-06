/*****************************************************************************************************************
 * ReelRobotix Inc. - Software License Agreement      Copyright (c) 2018
 * 	 Authors: Pablo Inigo Blasco, Brett Aldrich
 *
 ******************************************************************************************************************/
#include <sm_fetch_screw_loop_1/clients/gripper_client/cl_gripper.h>
//#include <pluginlib/class_list_macros.h>

namespace sm_fetch_screw_loop_1
{
namespace cl_gripper
{

ClGripper::ClGripper(std::string actionServerName)
    : Base(actionServerName)
{
}

ClGripper::ClGripper()
    : Base()
{
}

std::string ClGripper::getName() const
{
    return "GRIPPER ACTUION CLIENT";
}

ClGripper::~ClGripper()
{
}
} // namespace cl_led

//PLUGINLIB_EXPORT_CLASS(cl_led::ClLED, smacc::ISmaccComponent)
}