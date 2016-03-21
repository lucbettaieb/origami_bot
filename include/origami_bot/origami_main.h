/*
 * origami_main
 * 
 * Copyright (c) 2016, Luc Bettaieb
 * EMAE 488: Advanced Robotics
 * BSD Licensed
 */

#ifndef ORIGAMI_MAIN_H
#define ORIGAMI_MAIN_H

#include <ros/ros.h>

#include "wiringPi.h"
#include "softPwm.h"

#include <geometry_msgs/Twist.h>

class OrigamiBot
{
public:
  OrigamiBot(ros::NodeHandle &nh);
  virtual ~OrigamiBot();

  static const int L_FWD = 1;
  static const int L_REV = 2;
  static const int R_FWD = 3;
  static const int R_REV = 4;

private:
  ros::NodeHandle nh_;
  geometry_msgs::Twist currentTwist;

  bool compareTwists(geometry_msgs::Twist &t1, geometry_msgs::Twist &t2);
  void twistCB(const geometry_msgs::Twist &twist);

  void sendMotorCommands();
};

#endif  // ORIGAMI_MAIN_H
