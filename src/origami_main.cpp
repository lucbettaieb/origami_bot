#include <ros/ros.h>
#include "wiringPi.h"
#include "softPwm.h"

#include <math.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "origami_main");
  ros::NodeHandle n;

  wiringPiSetup();

  softPwmCreate(1, 0, 100);


  uint t = 0;
  double val = 0;
  while (ros::ok())
  {
  val = (100/2)*sin(0.03*t - M_PI/2) + (100/2);
  ROS_INFO("The value is %f", val);


  softPwmWrite(1, val);
  //delay(10);

   ros::Duration(0.00001).sleep();

//    for (int i = 0; i < 100; ++i)
//    {
//      softPwmWrite(1, i);
//      delay(10);
//    }

//    for (int i = 100; i > 0; --i)
//    {
//      softPwmWrite(1, i);
//      delay(10);
//    }


  ros::spinOnce();
    t++;
  }

}

