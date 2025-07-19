import rlcpy 
from rclpy.node import Node
# Turtlesim command type: Twist
from geometry_msgs.msg import Twist 

'''
This class serves as the listener on the turtle side. This "listener" subscribes 
to the incoming cFS commands and publishes the "ROS2" command to the turtle.
'''
class TurtleListener(Node):
    def __init__(self):
        super().__init__('turtle_listener')
        self.sub = self.create_subscription(Twist, 'cfs_output', self.callback, 10)
        self.pub = self.create_publisher(Twist, 'turtle1/cmd_vel', 10)

    def callback(self, msg):
        self.get_logger().info(f"Forwarding Twist: linear={msg.linear.x}, angular={msg.angular.z}")
        self.pub.publish(msg)

rclpy.init()
rclpy.spin(TurtleListener())