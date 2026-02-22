#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

using namespace std::chrono_literals;

class RobotNewsStationNode : public rclcpp::Node
{
public:
    RobotNewsStationNode() : Node("robot_news_station"), robot_name_("Lichi01")
    {
        Publisher_ = this->create_publisher<example_interfaces::msg::String>("robot_news", 10);
        timer_ = this->create_wall_timer(0.5s, std::bind(&RobotNewsStationNode::PublishNews, this));
        RCLCPP_INFO(this->get_logger(), "Robot News station has been started");
    }

private:
    void PublishNews()
    {
        auto msg = example_interfaces::msg::String();
        msg.data = std::string("Namaste this is ") + robot_name_ + 
        std::string(", do you copy?");
        Publisher_->publish(msg);
    }

    std::string robot_name_;
    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr Publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotNewsStationNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}


