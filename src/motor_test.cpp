/*
 * motor_test
 *
 * Copyright (c) 2016, Luc Bettaieb
 * EMAE 488: Advanced Robotics
 * BSD Licensed
 */

#include <ros/ros.h>
#include "wiringPi.h"
#include "softPwm.h"

#include <math.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "motor_test");
  ros::NodeHandle n;

  wiringPiSetup();

  softPwmCreate(1, 0, 100);

  pinMode(25, INPUT);
  pinMode(29, INPUT);
  pinMode(28, INPUT);
  pinMode(27, INPUT);

  uint t = 0;
  double val = 0;
  while (ros::ok())
  {
    // for (int i = 0; i < 100; ++i)
    // {
    //   softPwmWrite(1, i);
    //   delay(10);
    // }

    // for (int i = 100; i > 0; --i)
    // {
    //   softPwmWrite(1, i);
    //   delay(10);
    // }
    std::cout << "LA: " << digitalRead(25) << " LB: " << digitalRead(29) << " RA: " << digitalRead(28) << " RB: " << digitalRead(27) << std::endl;

  ros::spinOnce();
    t++;
  }
}
