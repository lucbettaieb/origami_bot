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
#include <std_msgs/UInt64.h>

class OrigamiBot
{
public:
  OrigamiBot(ros::NodeHandle &nh);
  virtual ~OrigamiBot();

  static const int L_FWD = 1;
  static const int L_REV = 2;
  static const int R_FWD = 3;
  static const int R_REV = 4;

  static const int L_ENC_A = 25;
  static const int L_ENC_B = 29;

  static const int R_ENC_A = 28;
  static const int R_ENC_B = 27;

  // These will need to be configured.
  static const int WHEEL_OPEN = 13;
  static const int WHEEL_CLOSE = 14;

  void publishTicks();
  void resetEncoders();

  void openWheels();
  void closeWheels();
private:
  ros::NodeHandle nh_;
  geometry_msgs::Twist currentTwist;

  bool compareTwists(geometry_msgs::Twist &t1, geometry_msgs::Twist &t2);
  void twistCB(const geometry_msgs::Twist &twist);

  void sendMotorCommands();
};

#endif  // ORIGAMI_MAIN_H
