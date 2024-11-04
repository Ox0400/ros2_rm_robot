/*
 * Filename: rm_robot/rm_example/src/api_Get_Arm_Gripper_State_demo.cpp
 * Path: rm_robot/rm_example/src
 * Created Date: Tuesday, October 29th 2024, 5:26:30 pm
 * Author: zhipeng
 */

#include <chrono>
#include <functional>
#include <memory>
#include <thread>
#include "rclcpp/rclcpp.hpp"
#include "rm_ros_interfaces/msg/gripperstate.hpp"
#include "std_msgs/msg/empty.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

/****************************************创建类************************************/ 
class GetGripperState: public rclcpp::Node
{
  public:
    GetGripperState();                                                                               //构造函数
    void get_gripper_state();                                                                        //改变工作坐标系函数
    void GetGripperState_Callback(const rm_ros_interfaces::msg::Gripperstate & msg);                 //结果回调函数
  
  private:
    rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr publisher_;                                   //声明发布器
    rclcpp::Subscription<rm_ros_interfaces::msg::Gripperstate>::SharedPtr subscription_;             //声明订阅器
};


/******************************接收到订阅的爪子状态消息后，会进入消息回调函数**************************/ 
void GetGripperState::GetGripperState_Callback(const rm_ros_interfaces::msg::Gripperstate & msg)
{
    // 将接收到的消息打印出来，显示是否执行成功

    RCLCPP_INFO (this->get_logger(),"Gripper enable(是否使能): %d\n", msg.enable);
    RCLCPP_INFO (this->get_logger(),"Gripper status(是否在线): %d\n", msg.status);
    RCLCPP_INFO (this->get_logger(),"Gripper error(错误码): %d\n", msg.error);
    RCLCPP_INFO (this->get_logger(),"Gripper mode(模式): %d\n", msg.mode);
    RCLCPP_INFO (this->get_logger(),"Gripper current_force(压力): %d\n", msg.current_force);
    RCLCPP_INFO (this->get_logger(),"Gripper temperature(温度): %d\n", msg.temperature);
    RCLCPP_INFO (this->get_logger(),"Gripper actpos(开口度): %d\n", msg.actpos);
    // RCLCPP_INFO (this->get_logger(),"sys_err is: %d\n",msg.sys_err);
}   
/***********************************************end**************************************************/

/*******************************************获取爪子状态函数****************************************/
void GetGripperState::get_gripper_state()
{
    std_msgs::msg::Empty gripper_state;
    this->publisher_->publish(gripper_state);
}
/***********************************************end**************************************************/

/***********************************构造函数，初始化发布器订阅器****************************************/
GetGripperState::GetGripperState():rclcpp::Node("get_gripper_state")
{
    // Get_Lift_State_Result = this->create_publisher<rm_ros_interfaces::msg::Liftstate>("rm_driver/get_lift_state_result", 10);
    RCLCPP_INFO (this->get_logger(),"Create Gripper State Result Queue\n");
    subscription_ = this->create_subscription<rm_ros_interfaces::msg::Gripperstate>("/rm_driver/get_current_gripper_state_result", 10, std::bind(&GetGripperState::GetGripperState_Callback, this,_1));
    RCLCPP_INFO (this->get_logger(),"Create Gripper State CMD Queue\n");
    publisher_ = this->create_publisher<std_msgs::msg::Empty>("/rm_driver/get_current_gripper_state_cmd", 10);
    RCLCPP_INFO (this->get_logger(),"Sleeping 2s ....\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    RCLCPP_INFO (this->get_logger(),"Calling get_gripper_state to push action to CMD Queue\n");
    get_gripper_state();
}
/***********************************************end**************************************************/

/******************************************************主函数*********************************************/
int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<GetGripperState>());
  rclcpp::shutdown();
  return 0;
}
