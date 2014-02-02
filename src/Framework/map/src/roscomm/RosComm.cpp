
/*
 * RosComm.cpp
 *
 *  Created on: Sunday, 02. February 2014 03:25PM
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
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
RosComm::RosComm(ComponentMain* comp,int argc,char** argv)
	: _inited(init(argc, argv)), _comp(comp)
{
	_sub_BladePosition=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"MAP","BladePosition","sub"), 10, &RosComm::BladePositionCallback,this));
	_sub_PosAttVel=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"MAP","PosAttVel","sub"), 10, &RosComm::PosAttVelCallback,this));
	_sub_Laser=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"MAP","Laser","sub"), 10, &RosComm::LaserCallback,this));
	_sub_Camera=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"MAP","Camera","sub"), 10, &RosComm::CameraCallback,this));
	_pub_Map=ros::Publisher(_nh.advertise<config::MAP::pub::Map>(fetchParam(&_nh,"MAP","Map","pub"),10));
	_pub_MiniMap=ros::Publisher(_nh.advertise<config::MAP::pub::MiniMap>(fetchParam(&_nh,"MAP","MiniMap","pub"),10));
}
RosComm::~RosComm()
{
}
bool RosComm::init(int argc,char** argv){
	ros::init(argc,argv,"MAP_node");
	return true;
}


void RosComm::BladePositionCallback(const config::MAP::sub::BladePosition::ConstPtr &msg)
{
	_comp->handleBladePosition(*msg);
}
	

void RosComm::PosAttVelCallback(const config::MAP::sub::PosAttVel::ConstPtr &msg)
{
	_comp->handlePosAttVel(*msg);
}
	

void RosComm::LaserCallback(const config::MAP::sub::Laser::ConstPtr &msg)
{
	_comp->handleLaser(*msg);
}
	

void RosComm::CameraCallback(const config::MAP::sub::Camera::ConstPtr &msg)
{
	_comp->handleCamera(*msg);
}
	

void RosComm::publishMap( config::MAP::pub::Map &msg)
{
	_pub_Map.publish(msg);
}
	

void RosComm::publishMiniMap( config::MAP::pub::MiniMap &msg)
{
	_pub_MiniMap.publish(msg);
}
	
void RosComm::publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame){
	static tf::TransformBroadcaster br;
	br.sendTransform(tf::StampedTransform(_tf, ros::Time::now(), srcFrame, distFrame));
}
tf::StampedTransform RosComm::getLastTrasform(std::string srcFrame, std::string distFrame){
	tf::StampedTransform _tf;
	static tf::TransformListener listener;
	try {
	    listener.waitForTransform(distFrame, srcFrame, ros::Time(0), ros::Duration(10.0) );
	    listener.lookupTransform(distFrame, srcFrame, ros::Time(0), _tf);
	} catch (tf::TransformException& ex) {
	    ROS_ERROR("%s",ex.what());
	}
	return _tf;
}
