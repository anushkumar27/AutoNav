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
```

# 3. Gazebo Install
## 3.1 System configuration 
```sh
sudo usermod -a -G dialout $USER
```
Log out and log in.

```sh
`sudo apt-get remove modemmanager` 
```
To remove modemmanager since it can interfere in serial communications.
## 3.2 Install common dependencies
```sh
sudo apt-get update -y
```
```sh
sudo apt-get install git zip qtcreator cmake build-essential genromfs ninja-build -y
```

### 3.2.1 Required python packages
```sh
sudo apt-get install python-argparse \
    python-empy python-toml python-numpy \
    python-dev python-pip -y
```
```sh
sudo -H pip install --upgrade pip 
```
```sh
sudo -H pip install pandas jinja2 pyserial
```
## 3.3 Build Dependecies
An alternative to MAKE tool
```sh
sudo apt-get install ninja-build -y
```
Install FastRTPS (eProsima C++ implementation)
```sh
wget http://www.eprosima.com/index.php/component/ars/repository/eprosima-fast-rtps/eprosima-fast-rtps-1-5-0/eprosima_fastrtps-1-5-0-linux-tar-gz -O eprosima_fastrtps-1-5-0-linux.tar.gz
```
```sh
tar -xzf eprosima_fastrtps-1-5-0-linux.tar.gz eProsima_FastRTPS-1.5.0-Linux
```
```sh
tar -xzf eprosima_fastrtps-1-5-0-linux.tar.gz requiredcomponents
```
```sh
tar -xzf requiredcomponents/eProsima_FastCDR-1.0.7-Linux.tar.gz
```
```sh
cd eProsima_FastCDR-1.0.7-Linux; ./configure --libdir=/usr/lib
```
```sh 
make -j2
```
```sh
sudo make install
```
```sh
cd ..
```
```sh
cd eProsima_FastRTPS-1.5.0-Linux; ./configure --libdir=/usr/lib
```
```sh
make -j2
```
```sh
sudo make install
```
```sh
cd ..
```
```sh
rm -rf requiredcomponents eprosima_fastrtps-1-5-0-linux.tar.gz
```
```sh
sudo apt-get install python-serial openocd \
    flex bison libncurses5-dev autoconf texinfo \
    libftdi-dev libtool zlib1g-dev -y
```
### 3.3.1 Install GCC 7-2017-q4
```sh
pushd .
```
```sh
cd ~
```
```sh
wget https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu-rm/7-2017q4/gcc-arm-none-eabi-7-2017-q4-major-linux.tar.bz2
```
```sh
tar -jxf gcc-arm-none-eabi-7-2017-q4-major-linux.tar.bz2
```
```sh
exportline="export PATH=$HOME/gcc-arm-none-eabi-7-2017-q4-major/bin:\$PATH"
```
```sh
if grep -Fxq "$exportline" ~/.profile; then echo nothing to do ; else echo $exportline >> ~/.profile; fi
```
```sh
popd
```

## 3.4 Remove older versions that may exist
```sh
sudo apt-get remove gcc-arm-none-eabi gdb-arm-none-eabi binutils-arm-none-eabi gcc-arm-embedded
```
```sh
sudo add-apt-repository --remove ppa:team-gcc-arm-embedded/ppa
```
# 4. Run Test Simulation
- Clone the PX4 Firmware
- Follow [https://dev.px4.io/en/simulation/gazebo.html](https://dev.px4.io/en/simulation/gazebo.html)
- Run following:
```sh
cd $(PLACE_YOU_CLONED_FIRMWARE)
make posix gazebo_iris_opt_flow
```
