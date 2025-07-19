# ~/ros2_ws/src/operator_input/operator_cmd.py
import rclpy
from rclpy.node import Node
from std_msgs.msg import String

'''
This class is the ROS2 operator side.
'''
class OperatorPublisher(Node):
    def __init__(self):
        super().__init__('operator_publisher')
        self.pub = self.create_publisher(String, 'cmd_input', 10)
        self.timer = self.create_timer(3.0, self.send)

    def send(self):
        msg = String()
        msg.data = "MOVE_FORWARD"
        self.pub.publish(msg)
        self.get_logger().info("Sent operator command: " + msg.data)

rclpy.init()
rclpy.spin(OperatorPublisher())
