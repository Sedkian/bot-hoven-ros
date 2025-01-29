#include <functional>
#include <memory>
#include <thread>

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <rclcpp_components/register_node_macro.hpp>

#include "calibration/visibility_control.h"
#include "bothoven_msgs/action/calibration.hpp"

namespace calibration
{
    class CalibrationActionServer : public rclcpp::Node
    {
        public:
            using Calibration = bothoven_msgs::action::Calibration;
            using GoalHandleCalibration = rclcpp_action::ServerGoalHandle<Calibration>;

            CALIBRATION_PUBLIC
            explicit CalibrationActionServer(const rclcpp::NodeOptions & options = rclcpp::NodeOptions())
            : Node("calibration_action_server", options)
            {
                using namespace std::placeholders;
                
                auto handle_goal = [this](
                    const rclcpp_action::GoalUUID & uuid,
                    std::shared_ptr<const Calibration::Goal> goal)
                {
                    RCLCPP_INFO(this->get_logger(), "Received calibration request with command '%s'", goal->command.c_str());
                    (void) uuid;
                    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
                };
                
                auto handle_cancel = [this](
                    const std::shared_ptr<GoalHandleCalibration> goal_handle)
                {
                    RCLCPP_INFO(this->get_logger(), "Received request to cancel calibration");
                    (void) goal_handle;
                    return rclcpp_action::CancelResponse::ACCEPT;
                };
                
                auto handle_accepted = [this](
                    const std::shared_ptr<GoalHandleCalibration> goal_handle)
                {
                    RCLCPP_INFO(this->get_logger(), "Calibration request has been accepted");
                    auto execute_in_thread = [this, goal_handle](){
                        return this->execute(goal_handle);
                    };
                    std::thread(execute_in_thread).detach();
                };

                this->action_server_ = rclcpp_action::create_server<Calibration>(
                    this->get_node_base_interface(),
                    this->get_node_clock_interface(),
                    this->get_node_logging_interface(),
                    this->get_node_waitables_interface(),
                    "/calibrate",
                    handle_goal,
                    handle_cancel,
                    handle_accepted
                );

                RCLCPP_INFO(this->get_logger(), "Calibration action server has started successfully");
            } // constructor
        
        private:
            rclcpp_action::Server<Calibration>::SharedPtr action_server_;

            void execute(const std::shared_ptr<GoalHandleCalibration> goal_handle)
            {}; // execute

            // Add
    }; // class CalibrationActionServer
} // namespace calibration

RCLCPP_COMPONENTS_REGISTER_NODE(calibration::CalibrationActionServer)