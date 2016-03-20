#include <ros/ros.h>
#include "wiringPi.h"
#include <math.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "origami_main");
  ros::NodeHandle n;

  wiringPiSetupSys();
  pinMode(11, OUTPUT);



  uint t = 0;
  double val = 0;
  while (ros::ok())
  {
    val = (255/2)*sin(t - M_PI/2) + (255/2);
    ROS_INFO("The value is %f", val);

    digitalWrite(11, val);

    delay(10);
    t++;
  }

}
