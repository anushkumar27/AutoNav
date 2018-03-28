/** Authors
 * Anush S Kumar (anushkumar27@gmail.com)
 * Sushrith Arkal (sushrith.arkal@gmail.com)
**/

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include "auto_nav_bridge/land.h"
#include "auto_nav_bridge/disarm.h"

// Current State
mavros_msgs::State current_state;
void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
}
// Destination Pose
geometry_msgs::PoseStamped dest_pose;
void dest_pose_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    dest_pose = *msg;
    ROS_INFO("Dest point: %f %f %f", dest_pose.pose.position.x, dest_pose.pose.position.y, dest_pose.pose.position.z);
}

// Land Service
bool should_land = false;
bool land_srv_cb(auto_nav_bridge::land::Request &req, auto_nav_bridge::land::Response &res) {
    ROS_INFO("Land command received");
    should_land = true;
    res.success = true;
    res.message = "Land command recieved";
    return true;
}

// Disarm service
bool should_disarm = false;
bool disarm_srv_cb(auto_nav_bridge::disarm::Request &req, auto_nav_bridge::disarm::Response &res) {
    ROS_INFO("Disarm command received");
    should_disarm = true;
    res.success = true;
    res.message = "Disarm command recieved";
    return true;
}

int main(int argc, char **argv)
{   
    // Initialise ros node and advertise to roscore
    ros::init(argc, argv, "mavros_bridge");

    // NodeHandle is the main access point to communications with the ROS system.
    ros::NodeHandle nh;

    // SUBSCRIBER
    // To fetch the current state of the FCU
    ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>
            ("mavros/state", 10, state_cb);
    // To get destination pose from Command Nodes
    ros::Subscriber dest_pose_sub = nh.subscribe<geometry_msgs::PoseStamped>
            ("auto_nav/mavros_bridge/pose", 10, dest_pose_cb);
    
    // PUBLISHER
    // To publish the raw destination pose to the FCU
    ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>
            ("mavros/setpoint_position/local", 10);
    
    // SERVICES (LANDING AND DISARM)
    ros::ServiceServer land_service = nh.advertiseService("auto_nav/land", land_srv_cb);
    ros::ServiceServer disarm_service = nh.advertiseService("auto_nav/disarm", disarm_srv_cb);

    // SERVICE CLIENTS
    // To ARM the FCU
    ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>
            ("mavros/cmd/arming");
    // To change flight mode to OFFBOARD
    ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode>
            ("mavros/set_mode");

    // The setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(20.0);

    // Wait for FCU connection
    while(ros::ok() && !current_state.connected){
        ros::spinOnce();
        rate.sleep();
    }

    // Desination msg, will be subscribed
    // Intitial value
    geometry_msgs::PoseStamped pose;
    pose.pose.position.x = 0;
    pose.pose.position.y = 0;
    pose.pose.position.z = 1;

    // Send a few setpoints before starting
    for(int i = 100; ros::ok() && i > 0; --i){
        local_pos_pub.publish(pose);
        ros::spinOnce();
        rate.sleep();
    }

    mavros_msgs::SetMode set_mode;
    set_mode.request.custom_mode = "OFFBOARD";

    mavros_msgs::CommandBool arm_cmd;
    arm_cmd.request.value = true;

    ros::Time last_request = ros::Time::now();

    while(ros::ok()){
        if( current_state.mode != "OFFBOARD" && !should_land && !should_disarm && 
            (ros::Time::now() - last_request > ros::Duration(5.0))) {
            if( set_mode_client.call(set_mode) &&
                set_mode.response.mode_sent){
                ROS_INFO("Offboard enabled");
            }
            last_request = ros::Time::now();
        } 
        else if( should_land && current_state.mode != "AUTO.LAND" &&
            (ros::Time::now() - last_request > ros::Duration(5.0))) {
            set_mode.request.custom_mode = "AUTO.LAND";
            if( set_mode_client.call(set_mode) &&
                set_mode.response.mode_sent){
                ROS_INFO("Landing");
            }
            last_request = ros::Time::now();
        }
        else if( current_state.armed && should_disarm &&
            (ros::Time::now() - last_request > ros::Duration(5.0))) {
            arm_cmd.request.value = false;
            if( arming_client.call(arm_cmd) &&
                arm_cmd.response.success){
                ROS_INFO("Vehicle disarmed");
            }
            last_request = ros::Time::now();
        }
        else {
            if( !current_state.armed &&
                (ros::Time::now() - last_request > ros::Duration(5.0))){
                if( arming_client.call(arm_cmd) &&
                    arm_cmd.response.success){
                    ROS_INFO("Vehicle armed");
                }
                last_request = ros::Time::now();
            }
        }

        // TODO: Check if this if block is really necessary
        if(!should_land && !should_disarm) {
            // Publish the current pose
            local_pos_pub.publish(pose);

            // Update the Pose to current destination pose
            pose.pose.position.x = dest_pose.pose.position.x;
            pose.pose.position.y = dest_pose.pose.position.y;
            pose.pose.position.z = dest_pose.pose.position.z;
        }
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}