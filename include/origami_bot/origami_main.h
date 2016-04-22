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
 #include <sensor_msgs/Joy.h>

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

  // These will need to be configured in export_pins.sh, too!!
  static const int WHEEL_PIN = 8;

  void publishTicks();
  void resetEncoders();
private:
  ros::NodeHandle nh_;
  geometry_msgs::Twist currentTwist;

  bool compareTwists(geometry_msgs::Twist &t1, geometry_msgs::Twist &t2);
  void twistCB(const geometry_msgs::Twist &twist);

  void openWheels();
  void closeWheels();

  /*
  * @param cmd 1 to open, 2 to close
  */
  void transformWheels(const sensor_msgs::Joy& cmd);

  void sendMotorCommands();
};

// Cat here.
//  \    /\
//   )  ( ')
//  (  /  )
//   \(__)|

#endif  // ORIGAMI_MAIN_H
