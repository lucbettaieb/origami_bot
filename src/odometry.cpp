/*
 * odometry
 *
 * Copyright (c) 2016, Luc Bettaieb
 * EMAE 488: Advanced Robotics
 * BSD Licensed
 */

#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/UInt64.h>

static const double WHEEL_RADIUS = ;
static const double WHEEL DISTANCE = ;


uint left_ticks = 0;
uint right_ticks = 0;

nav_msgs::Odometry odom;

void updateRightTicks(const std_msgs::UInt64& right)
{
  right_ticks = right.data;
}

void updateLeftTicks(const std_msgs::UInt64& left)
{
  left_ticks = left.data;
}

void updateOdom()
{
  double theta = ()
  double x = 
  double y = 

  odom.pose.pose.orientation.z = 
  odom.pose.pose.position.x = 
  odom.pose.pose.position.y = 
}

int main(int argc, char** argv)
{
  ros::NodeHandle nh;

  ros::Subscriber l_wheel_sub = nh.subscribe("/rwheel", 3, &updateRightTicks);
  ros::Subscriber r_wheel_sub = nh.subscribe("/lwheel", 3, &updateLeftTicks);

  ros::Publisher odom_pub = nh.advertise("/odom", 10);
  odom.header.seq = 1;
  odom.header.stamp = ros::Time::now();
  odom.header.frame_id = "base";  // This may need to change?
  odom.child_frame_id = "odom";

  while (ros::ok())
  {
    // then here?
    updateOdom();
    odom_pub.publish(odom);
    ros::spinOnce();
  }
}
