
/*
 * RosComm.cpp
 *
 *  Created on: Thursday, 30. January 2014 04:16PM
 *      Author: autogenerated
 */
#include <ros/ros.h>
#include <std_msgs/String.h>
#include "RosComm.h"
#include "../component/ComponentMain.h"
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>
#include "ParameterHandler.h"
RosComm::RosComm(ComponentMain* comp,int argc,char** argv)
{
  ros::init(argc,argv,"PP_node");
  _comp=comp;
	_sub_TrottleEffort=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"LLI","TrottleEffort","sub"), 10, &RosComm::TrottleEffortCallback,this));
	_sub_SteeringEffort=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"LLI","SteeringEffort","sub"), 10, &RosComm::SteeringEffortCallback,this));
	_sub_JointsEffort=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"LLI","JointsEffort","sub"), 10, &RosComm::JointsEffortCallback,this));
	_sub_Teleoperation=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"LLI","Teleoperation","sub"), 10, &RosComm::TeleoperationCallback,this));
	_pub_Teleoperation=ros::Publisher(_nh.advertise<config::LLI::pub::Teleoperation>(fetchParam(&_nh,"LLI","Teleoperation","pub"),10));
	_pub_TrottleEffort=ros::Publisher(_nh.advertise<config::LLI::pub::TrottleEffort>(fetchParam(&_nh,"LLI","TrottleEffort","pub"),10));
	_pub_SteeringEffort=ros::Publisher(_nh.advertise<config::LLI::pub::SteeringEffort>(fetchParam(&_nh,"LLI","SteeringEffort","pub"),10));
	_pub_JointsEffort=ros::Publisher(_nh.advertise<config::LLI::pub::JointsEffort>(fetchParam(&_nh,"LLI","JointsEffort","pub"),10));
}
RosComm::~RosComm()
{
}

void RosComm::TrottleEffortCallback(const config::LLI::sub::TrottleEffort::ConstPtr &msg)
{
	_comp->handleTrottleEffort(*msg);
}
	

void RosComm::SteeringEffortCallback(const config::LLI::sub::SteeringEffort::ConstPtr &msg)
{
	_comp->handleSteeringEffort(*msg);
}
	

void RosComm::JointsEffortCallback(const config::LLI::sub::JointsEffort::ConstPtr &msg)
{
	_comp->handleJointsEffort(*msg);
}
	

void RosComm::TeleoperationCallback(const config::LLI::sub::Teleoperation::ConstPtr &msg)
{
	_comp->handleTeleoperation(*msg);
}
	

void RosComm::publishTeleoperation( config::LLI::pub::Teleoperation &msg)
{
	_pub_Teleoperation.publish(msg);
}
	

void RosComm::publishTrottleEffort( config::LLI::pub::TrottleEffort &msg)
{
	_pub_TrottleEffort.publish(msg);
}
	

void RosComm::publishSteeringEffort( config::LLI::pub::SteeringEffort &msg)
{
	_pub_SteeringEffort.publish(msg);
}
	

void RosComm::publishJointsEffort( config::LLI::pub::JointsEffort &msg)
{
	_pub_JointsEffort.publish(msg);
}
	