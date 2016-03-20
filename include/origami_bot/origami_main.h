/*
 * origami_main
 * 
 * Copyright (c) 2016, Luc Bettaieb
 * EMAR 488: Advanced Robotics
 *
 */

#ifndef ORIGAMI_MAIN_H
#define ORIGAMI_MAIN_H

#include <ros/ros.h>

class OrigamiBot
{
public:
  OrigamiBot(ros::NodeHandle &nh);
  virtual ~OrigamiBot();

private:
  ros::NodeHandle nh_;

public:
  

};

#endif  // ORIGAMI_MAIN_H