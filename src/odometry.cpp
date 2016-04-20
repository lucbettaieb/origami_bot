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
#include <std_msgs/Bool.h>
#include <math.h>

double G_TICKS_METER;
double G_BASE_WIDTH;
int G_ODOM_RATE;

uint left_ticks = 0;
uint right_ticks = 0;


ros::Time then;

nav_msgs::Odometry odom;

// Initialize odometry
odom.pose.pose.orientation.z = 0.0;
odom.pose.pose.position.x = 0.0;
odom.pose.pose.position.y = 0.0;

void updateRightTicks(const std_msgs::UInt64& right)
{
  right_ticks = right.data;
}

void updateLeftTicks(const std_msgs::UInt64& left)
{
  left_ticks = left.data;
}

void updateLeftTicks(const std_msgs::Bool& reset)
{
  if (reset.data == true)
  {
    left_ticks = 0;
    right_ticks = 0;
  }
}

void updateOdom()
{
  // Time stuff
  ros::Time now = ros::Time.now();
  double elapsed_time = then.to_sec() - now.to_sec();
  then = now;


  double d_left = (left_ticks - right_ticks) / G_TICKS_METER;
  double d_right = (right_ticks - left_ticks) / G_TICKS_METER;

  double d = (d_left + d_right) / 2;

  // Small angle approximation of theta
  double theta = (d_right - d_left) / G_BASE_WIDTH;

  dx = d / elapsed_time;
  dr = theta / elapsed_time;

  double x_inc = Math::cos(theta) * d;
  double y_inc = -Math::sin(theta) * d;

  odom.pose.pose.orientation.z += theta;

  // Check for looparound on orientation.
  // Forward looparound
  if (odom.pose.pose.orientation.z > 2*pi)
    odom.pose.pose.orientation.z = 0;

  // Resverse looparound
  else if (odom.pose.pose.orientation.z < -2*pi)
    odom.pose.pose.orientation.z = 0;

  odom.pose.pose.position.x += x_inc;
  odom.pose.pose.position.y += y_inc;
}

int main(int argc, char** argv)
{
  ros::NodeHandle nh;

  ros::Subscriber l_wheel_sub = nh.subscribe("/rwheel", 3, &updateRightTicks);
  ros::Subscriber r_wheel_sub = nh.subscribe("/lwheel", 3, &updateLeftTicks);
  ros::Subsrriber reset_odom = nh.subscribe("/reset_odom", 1, &resetOdom)

  ros::Publisher odom_pub = nh.advertise<nav_msgs::Odometry>("/odom", 10);
  odom.header.seq = 1;
  odom.header.stamp = ros::Time::now();
  odom.header.frame_id = "base";  // This may need to change?
  odom.child_frame_id = "odom";

  // Load in parameters from the parameter server
  if (!nh.getParam("ticks_meter", G_TICKS_METER))
    G_TICKS_METER = 3;

  if (!nh.getParam("base_width", G_BASE_WIDTH))
    G_BASE_WIDTH = 3;

  if (!nh.getParam("rate", G_ODOM_RATE))
    G_ODOM_RATE = 3;

  then = ros::Time.now();

  while (ros::ok())
  {
    // then here?
    updateOdom();
    odom_pub.publish(odom);
    ros::spinOnce();
  }
}
