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

# Gazebo Install
Install Instructions:
1. Install ROS Kinetic (see Anush's instructions)
2. Install mavros and mavros_extras
3. Follow steps in [here](https://dev.px4.io/en/setup/dev_env_linux_ubuntu.html).
4. Run `sudo usermod -a -G dialout $USER`. Log out and log in.
5. Run `sudo apt-get remove modemmanager` to remove modemmanager since it can interfere in serial communications.
6. Install common dependencies:
```sh
sudo apt-get update -y
sudo apt-get install git zip qtcreator cmake \
    build-essential genromfs ninja-build -y
# Required python packages
sudo apt-get install python-argparse \
    python-empy python-toml python-numpy \
    python-dev python-pip -y
sudo -H pip install --upgrade pip 
sudo -H pip install pandas jinja2 pyserial

# Optional
# optional python tools
sudo -H pip install pyulog
```
7. Run `sudo apt-get install ninja-build -y` to install Ninja Build (alternative to Make that is faster).
8. Install FastRTPS (eProsima C++ implementation)
```sh
wget http://www.eprosima.com/index.php/component/ars/repository/eprosima-fast-rtps/eprosima-fast-rtps-1-5-0/eprosima_fastrtps-1-5-0-linux-tar-gz -O eprosima_fastrtps-1-5-0-linux.tar.gz
tar -xzf eprosima_fastrtps-1-5-0-linux.tar.gz eProsima_FastRTPS-1.5.0-Linux/
tar -xzf eprosima_fastrtps-1-5-0-linux.tar.gz requiredcomponents
tar -xzf requiredcomponents/eProsima_FastCDR-1.0.7-Linux.tar.gz

cd eProsima_FastCDR-1.0.7-Linux; ./configure --libdir=/usr/lib; make -j2; sudo make install
cd ..
cd eProsima_FastRTPS-1.5.0-Linux; ./configure --libdir=/usr/lib; make -j2; sudo make install
cd ..
rm -rf requiredcomponents eprosima_fastrtps-1-5-0-linux.tar.gz
```
9. (optional) Install Gazebo 8 (see above link for more details), but since ROS Kinetic includes Gazebo 7, this was skipped.
10. Since we are building for NuttX based hardware (Pixhawk) we must install the following dependencies:
```sh
sudo apt-get install python-serial openocd \
    flex bison libncurses5-dev autoconf texinfo \
    libftdi-dev libtool zlib1g-dev -y

# Remove older versions that may exist
sudo apt-get remove gcc-arm-none-eabi gdb-arm-none-eabi binutils-arm-none-eabi gcc-arm-embedded
sudo add-apt-repository --remove ppa:team-gcc-arm-embedded/ppa

# Execute following script to install GCC 7-2017-q4
pushd .
cd ~
wget https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu-rm/7-2017q4/gcc-arm-none-eabi-7-2017-q4-major-linux.tar.bz2
tar -jxf gcc-arm-none-eabi-7-2017-q4-major-linux.tar.bz2
exportline="export PATH=$HOME/gcc-arm-none-eabi-7-2017-q4-major/bin:\$PATH"
if grep -Fxq "$exportline" ~/.profile; then echo nothing to do ; else echo $exportline >> ~/.profile; fi
popd

# Restart your machine

# Check whether it was installed:
arm-none-eabi-gcc --version

# Expected output:
# arm-none-eabi-gcc (GNU Tools for Arm Embedded Processors 7-2017-q4-major) 7.2.1 20170904 (release) [ARM/embedded-7-branch revision 255204]
# Copyright (C) 2017 Free Software Foundation, Inc.
# This is free software; see the source for copying conditions.  There is NO
# warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```
10. Clone the PX4 Firmware
11. Follow [these instructions](https://dev.px4.io/en/simulation/gazebo.html)
12. Run following:
```sh
ch $(PLACE_YOU_CLONED_FIRMWARE)
make posix gazebo_iris_opt_flow
```
