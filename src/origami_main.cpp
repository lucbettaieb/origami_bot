/*
 * origami_main
 *
 * Copyright (c) 2016, Luc Bettaieb
 * EMAE 488: Advanced Robotics
 * BSD Licensed
 */

#include "origami_bot/origami_main.h"

#include <math.h>

ros::Subscriber g_TwistListener;
int M1_FWD = 1;
int M1_REV = 2;
int M2_FWD = 3;
int M2_REV = 4;

OrigamiBot::OrigamiBot(ros::NodeHandle &nh)
{
  wiringPiSetup();

  softPwmCreate(1, 0, 100);  // M1 FWD Channel
  softPwmCreate(2, 0, 100);  // M1 REV Channel

  softPwmCreate(3, 0, 100);  // M2 FWD Channel
  softPwmCreate(4, 0, 100);  // M2 REV Channel

  nh_ = nh;

  current_twist.linear.x = 0;
  current_twist.linear.y = 0;
  current_twist.linear.z = 0;
  current_twist.angular.x = 0;
  current_twist.angular.y = 0;
  current_twist.angular.z = 0;
}

OrigamiBot::~OrigamiBot()
{
}

// Maybe unneccessary helper function.  Schedule for deletion.
bool OrigamiBot::compareTwists(geometry_msgs::Twist &t1, geometry_msgs::Twist &t2)
{
  if (t1->linear->x == t2->linear->x && t1->linear->y == t2->linear->y && t1->linear->z == t2->linear->z &&
     t1->angular->x == t2->angular->x && t1->angular->y == t2->angular->y && t1->angular->z == t2->angular->z)
  {
    return true;
  }
  else
    return false;
}

void OrigamiBot::twistCB(const geometry_msgs::Twist& twist)
{
  // if (!compareTwists(*currentTwist, twist))
  //   currentTwist = twist;  // Make sure this gets copied and is not some weird pointer thing.
  // else


}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "origami_main");
  ros::NodeHandle n;
}
