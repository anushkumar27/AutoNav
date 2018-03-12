# 1. ROS Kinetic installation instructions
## 1.1 Configure your Ubuntu repositories
```sh
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
```
## 1.2 Set up your keys
```sh
sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116
```
## 1.3  Update Debian package index
```sh
sudo apt-get update
```
## 1.4 ROS Kinetic Desktop-Full install
ROS, rqt, rviz, robot-generic libraries, 2D/3D simulators, navigation and 2D/3D perception
```sh
sudo apt-get install ros-kinetic-desktop-full
```
## 1.5 Initialize rosdep
```sh
sudo rosdep init
rosdep update
```
## 1.6 Dependecy for ROS package
```sh
sudo rosdep init
rosdep update
```

# 2. Mavros & Mavros Extras
```sh
sudo apt-get install ros-kinetic-mavros ros-kinetic-mavros-extras
``
