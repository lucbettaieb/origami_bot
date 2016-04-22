/*
 * origami_main
 *
 * Copyright (c) 2016, Luc Bettaieb
 * EMAE 488: Advanced Robotics
 * BSD Licensed
 */

#include "origami_bot/origami_main.h"

#include <math.h>

ros::Publisher g_LWheelPublisher;
ros::Publisher g_RWheelPublisher;

ros::Subscriber g_TwistSubscriber;
ros::Subscriber g_WheelSubscriber;

// Keep track of prev encoder pattern
int prev_l_enc_a = 0;
int prev_l_enc_b = 0;

int prev_r_enc_a = 0;
int prev_r_enc_b = 0;

// Encoder variable
int n_l_enc = 0;
int n_r_enc = 0;

std_msgs::UInt64 l_enc_ticks;
std_msgs::UInt64 r_enc_ticks;

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

  pinMode(WHEEL_PIN, OUTPUT);
  // pinMode(WHEEL_CLOSE, OUTPUT);

  nh_ = nh;

  currentTwist.linear.x = 0;
  currentTwist.linear.y = 0;
  currentTwist.linear.z = 0;
  currentTwist.angular.x = 0;
  currentTwist.angular.y = 0;
  currentTwist.angular.z = 0;

  l_enc_ticks.data = 0;
  r_enc_ticks.data = 0;

  g_TwistSubscriber = nh_.subscribe("/cmd_vel", 3, &OrigamiBot::twistCB, this);
  g_WheelSubscriber = nh_.subscribe("/joy", 1, &OrigamiBot::transformWheels, this);

  g_LWheelPublisher = nh_.advertise<std_msgs::UInt64>("/lwheel", 100);
  g_RWheelPublisher = nh_.advertise<std_msgs::UInt64>("/rwheel", 100);
}

OrigamiBot::~OrigamiBot()
{
}

void OrigamiBot::transformWheels(const sensor_msgs::Joy& cmd)
{
  if (cmd.buttons[1] == 1)
  {
    openWheels();
  }
}
void OrigamiBot::openWheels()
{
  digitalWrite(WHEEL_PIN, HIGH);
  delay(1000);
  digitalWrite(WHEEL_PIN, LOW);
}

void OrigamiBot::closeWheels()
{
  digitalWrite(WHEEL_PIN, HIGH);
  delay(1000);
  digitalWrite(WHEEL_PIN, LOW);
}

void OrigamiBot::publishTicks()
{
  int l_enc_a = digitalRead(L_ENC_A);
  int l_enc_b = digitalRead(L_ENC_B);
  if (digitalRead(L_ENC_A) != prev_l_enc_a || digitalRead(L_ENC_B) != prev_l_enc_b)
  {
    prev_l_enc_a = l_enc_a;
    prev_l_enc_b = l_enc_b;

    n_l_enc++;
  }
  if (n_l_enc >= 4)
  {
    n_l_enc = 0;

    l_enc_ticks.data = r_enc_ticks.data + 1;
  }

  int r_enc_a = digitalRead(R_ENC_A);
  int r_enc_b = digitalRead(R_ENC_B);
  if (digitalRead(R_ENC_A) != prev_r_enc_a || digitalRead(R_ENC_B) != prev_r_enc_b)
  {
    prev_r_enc_a = r_enc_a;
    prev_r_enc_b = r_enc_b;

    n_r_enc++;
  }
  if (n_r_enc >= 4)
  {
    n_r_enc = 0;

    r_enc_ticks.data = r_enc_ticks.data + 1;
  }

  g_LWheelPublisher.publish(l_enc_ticks);
  g_RWheelPublisher.publish(r_enc_ticks);
}

void OrigamiBot::resetEncoders()
{
  l_enc_ticks.data = 0;
  r_enc_ticks.data = 0;
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
  }
  else if (x < 0)  // Reverse motors
  {
    softPwmWrite(L_FWD, 0);
    softPwmWrite(R_FWD, 0);

    softPwmWrite(L_REV, 100 * cmd_left);
    softPwmWrite(R_REV, 100 * cmd_right);
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
