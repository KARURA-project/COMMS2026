import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/karura/racs2_ws/ros2_ws/install/bridge_py_s'
