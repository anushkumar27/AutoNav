# Auto_Nav_Bridge

This ROS package provides autonomous navigation capabilities to Mavlink based FCUs.

## Description
This module/node is responsible for handling and abstracting out the complexities of communication to the PX4 FCU via MAVLink. 
It handles the arming and disarming of the aerial robot, as well as changing the mode of the aerial robot to accept external commands over the MAVLink protocol. 
These responsibilities are implemented through a set of published and subscribed topics as well as through “ROS Services” which act like an API for other nodes/modules to interact and invoke behavior in other nodes.
