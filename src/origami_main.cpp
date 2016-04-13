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
ros::Publisher g_LWheelPublisher;
ros::Publisher g_RWheelPublisher;

int prev_l_enc_a = 0;
int prev_l_enc_b = 1;

int prev_r_enc_a = 0;
int prev_r_enc_b = 1;


uint l_enc_ticks;
uint r_enc_ticks;

OrigamiBot::OrigamiBot(ros::NodeHandle &nh)
{
  wiringPiSetup();

  softPwmCreate(L_FWD, 0, 100);  // M1 FWD Channel
  softPwmCreate(L_REV, 0, 100);  // M1 REV Channel

  softPwmCreate(R_FWD, 0, 100);  // M2 FWD Channel
  softPwmCreate(R_REV, 0, 100);  // M2 REV Channel

  pinMode(L_ENC_A, INPUT);
  pinMode(L_ENC_B, INPUT);
  pinMode(R_ENC_A, INPUT);
  pinMode(R_ENC_B, INPUT);

  nh_ = nh;

  currentTwist.linear.x = 0;
  currentTwist.linear.y = 0;
  currentTwist.linear.z = 0;
  currentTwist.angular.x = 0;
  currentTwist.angular.y = 0;
  currentTwist.angular.z = 0;

  l_enc_ticks = 0;
  r_enc_ticks = 0;

  g_TwistListener = nh_.subscribe("/cmd_vel", 3, &OrigamiBot::twistCB, this);
  g_LWheelPublisher = nh_.advertise<std_msgs::Int16>("/lwheel", 100);
  g_RWheelPublisher = nh_.advertise<std_msgs::Int16>("/rwheel", 100);
}

OrigamiBot::~OrigamiBot()
{
}

void publishTicks()
{
  //if(digitalRead(L_ENC_A) != )
}

void resetEncoders()
{
  l_enc_ticks = 0;
  r_enc_ticks = 0;
}

// Maybe unneccessary helper function.  Schedule for deletion.
bool OrigamiBot::compareTwists(geometry_msgs::Twist &t1, geometry_msgs::Twist &t2)
{
  if (t1.linear.x == t2.linear.x && t1.linear.y == t2.linear.y && t1.linear.z == t2.linear.z &&
     t1.angular.x == t2.angular.x && t1.angular.y == t2.angular.y && t1.angular.z == t2.angular.z)
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
  double x    = twist.linear.x;
  double phi  = twist.angular.z;

  float cmd_left = x;
  float cmd_right = x;

  if (phi > 0)
    cmd_right *= phi;
  else if (phi < 0)
    cmd_left *= (-1*phi);

  if (x > 0)  // Forward motors
  {
    softPwmWrite(L_REV, 0);
    softPwmWrite(R_REV, 0);

    softPwmWrite(L_FWD, 100 * cmd_left);
    softPwmWrite(R_FWD, 100 * cmd_right);
    std::cout << "FWD | L: " << cmd_left << " R: " << cmd_right << std::endl;
  }
  else if (x < 0)  // Reverse motors
  {
    softPwmWrite(L_FWD, 0);
    softPwmWrite(R_FWD, 0);

    softPwmWrite(L_REV, 100 * cmd_left);
    softPwmWrite(R_REV, 100 * cmd_right);
    std::cout << "REV | L: " << cmd_left << " R: " << cmd_right << std::endl;
  }
  else if (x == 0)  // Stop!
  {
    softPwmWrite(L_FWD, 0);
    softPwmWrite(R_FWD, 0);
    softPwmWrite(L_REV, 0);
    softPwmWrite(R_REV, 0);
  }
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "origami_main");
  ros::NodeHandle nh;

  OrigamiBot bot(nh);
  while (ros::ok())
  {
    bot.publishTicks();
    ros::spinOnce();
  }
}
