#include "geometry_msgs/msg/twist.hpp" //geometry_msgs 추가
#include "rclcpp/rclcpp.hpp"
#include <memory>
#include <chrono>
#include <functional>

//클래스 Pub2Node선언 후 상속된 클래스 선언 rclcpp::Node
class Pub2Node : public rclcpp::Node
{
public:
    Pub2Node() : Node("pub2_node")
    {
        // 터틀1/cmdvel, 보낼 메세지의 큐 사이즈 10
        publisher = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);

        // create_wall_timer함수 사용
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(100),  //1000msec = 1sec
            std::bind(&Pub2Node::publish_velocity, this)); //bind를 써서 매개변수를 마음대로 바꿀 수 있다.
    }

private:
    //Twist메세지를 생성하였고 auto message라는 변수를 선언하는데 이때 auto는 자동으로 해당 변수에 적합한 자료형으로 적용이 됨
    void publish_velocity()
    {
        auto message = geometry_msgs::msg::Twist();
        message.linear.x = 1.0;  // 임의의 선속도 설정
        message.angular.z = -0.5; // 임의의 각속도 설정
        publisher->publish(message);
    }

    // 스마트 포인터를 사용하여 publisher사용
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher;
    // timer_사용
    rclcpp::TimerBase::SharedPtr timer_;
};
//메인 
int main(int argc, char *argv[])
{
    //생성자
    rclcpp::init(argc, argv);
    //스마트 포인터로 Pub2Node를 사용
    auto node = std::make_shared<Pub2Node>();
    //rclcpp의 spin은 while문과 같은 역할
    rclcpp::spin(node);
    rclcpp::shutdown(); //종료
    return 0; //0값을 반환
}