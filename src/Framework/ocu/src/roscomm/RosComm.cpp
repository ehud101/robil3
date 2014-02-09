
/*
 * RosComm.cpp
 *
 *  Created on: Thursday, 06. February 2014 04:09PM
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
	_sub_Odometry=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"OCU","Odometry","sub"), 10, &RosComm::OdometryCallback,this));
	_sub_BladPosition=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"OCU","BladPosition","sub"), 10, &RosComm::BladPositionCallback,this));
	_sub_Map=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"OCU","Map","sub"), 10, &RosComm::MapCallback,this));
	_sub_WPDDecisions=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"OCU","WPDDecisions","sub"), 10, &RosComm::WPDDecisionsCallback,this));
	_sub_LocalPath=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"OCU","LocalPath","sub"), 10, &RosComm::LocalPathCallback,this));
	_sub_PlatformState=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"OCU","PlatformState","sub"), 10, &RosComm::PlatformStateCallback,this));
	_sub_SoftwareState=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"OCU","SoftwareState","sub"), 10, &RosComm::SoftwareStateCallback,this));
	_sub_SensorsState=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"OCU","SensorsState","sub"), 10, &RosComm::SensorsStateCallback,this));
	_sub_SMMEMissionState=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"OCU","SMMEMissionState","sub"), 10, &RosComm::SMMEMissionStateCallback,this));
	_sub_MissionAcceptance=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"OCU","MissionAcceptance","sub"), 10, &RosComm::MissionAcceptanceCallback,this));
	_pub_PositionUpdate=ros::Publisher(_nh.advertise<config::OCU::pub::PositionUpdate>(fetchParam(&_nh,"OCU","PositionUpdate","pub"),10));
	_pub_SMMECommand=ros::Publisher(_nh.advertise<config::OCU::pub::SMMECommand>(fetchParam(&_nh,"OCU","SMMECommand","pub"),10));
	_pub_SMMEControlMode=ros::Publisher(_nh.advertise<config::OCU::pub::SMMEControlMode>(fetchParam(&_nh,"OCU","SMMEControlMode","pub"),10));
	_pub_NavigationTask=ros::Publisher(_nh.advertise<config::OCU::pub::NavigationTask>(fetchParam(&_nh,"OCU","NavigationTask","pub"),10));
	_pub_ManipulationTask=ros::Publisher(_nh.advertise<config::OCU::pub::ManipulationTask>(fetchParam(&_nh,"OCU","ManipulationTask","pub"),10));
	_pub_MissionTask=ros::Publisher(_nh.advertise<config::OCU::pub::MissionTask>(fetchParam(&_nh,"OCU","MissionTask","pub"),10));
	_pub_CustomPath=ros::Publisher(_nh.advertise<config::OCU::pub::CustomPath>(fetchParam(&_nh,"OCU","CustomPath","pub"),10));
	_pub_TeleoperationThrottle=ros::Publisher(_nh.advertise<config::OCU::pub::TeleoperationThrottle>(fetchParam(&_nh,"OCU","TeleoperationThrottle","pub"),10));
	_pub_TeleoperationSteering=ros::Publisher(_nh.advertise<config::OCU::pub::TeleoperationSteering>(fetchParam(&_nh,"OCU","TeleoperationSteering","pub"),10));
	_pub_TeleoperationJoints=ros::Publisher(_nh.advertise<config::OCU::pub::TeleoperationJoints>(fetchParam(&_nh,"OCU","TeleoperationJoints","pub"),10));
	_pub_IEDLocation=ros::Publisher(_nh.advertise<config::OCU::pub::IEDLocation>(fetchParam(&_nh,"OCU","IEDLocation","pub"),10));
}
RosComm::~RosComm()
{
}
bool RosComm::init(int argc,char** argv){
	ros::init(argc,argv,"OCU_node");
	return true;
}


void RosComm::OdometryCallback(const config::OCU::sub::Odometry::ConstPtr &msg)
{
	_comp->handleOdometry(*msg);
}
	

void RosComm::BladPositionCallback(const config::OCU::sub::BladPosition::ConstPtr &msg)
{
	_comp->handleBladPosition(*msg);
}
	

void RosComm::MapCallback(const config::OCU::sub::Map::ConstPtr &msg)
{
	_comp->handleMap(*msg);
}
	

void RosComm::WPDDecisionsCallback(const config::OCU::sub::WPDDecisions::ConstPtr &msg)
{
	_comp->handleWPDDecisions(*msg);
}
	

void RosComm::LocalPathCallback(const config::OCU::sub::LocalPath::ConstPtr &msg)
{
	_comp->handleLocalPath(*msg);
}
	

void RosComm::PlatformStateCallback(const config::OCU::sub::PlatformState::ConstPtr &msg)
{
	_comp->handlePlatformState(*msg);
}
	

void RosComm::SoftwareStateCallback(const config::OCU::sub::SoftwareState::ConstPtr &msg)
{
	_comp->handleSoftwareState(*msg);
}
	

void RosComm::SensorsStateCallback(const config::OCU::sub::SensorsState::ConstPtr &msg)
{
	_comp->handleSensorsState(*msg);
}
	

void RosComm::SMMEMissionStateCallback(const config::OCU::sub::SMMEMissionState::ConstPtr &msg)
{
	_comp->handleSMMEMissionState(*msg);
}
	

void RosComm::MissionAcceptanceCallback(const config::OCU::sub::MissionAcceptance::ConstPtr &msg)
{
	_comp->handleMissionAcceptance(*msg);
}
	

void RosComm::publishPositionUpdate( config::OCU::pub::PositionUpdate &msg)
{
	_pub_PositionUpdate.publish(msg);
}
	

void RosComm::publishSMMECommand( config::OCU::pub::SMMECommand &msg)
{
	_pub_SMMECommand.publish(msg);
}
	

void RosComm::publishSMMEControlMode( config::OCU::pub::SMMEControlMode &msg)
{
	_pub_SMMEControlMode.publish(msg);
}
	

void RosComm::publishNavigationTask( config::OCU::pub::NavigationTask &msg)
{
	_pub_NavigationTask.publish(msg);
}
	

void RosComm::publishManipulationTask( config::OCU::pub::ManipulationTask &msg)
{
	_pub_ManipulationTask.publish(msg);
}
	

void RosComm::publishMissionTask( config::OCU::pub::MissionTask &msg)
{
	_pub_MissionTask.publish(msg);
}
	

void RosComm::publishCustomPath( config::OCU::pub::CustomPath &msg)
{
	_pub_CustomPath.publish(msg);
}
	

void RosComm::publishTeleoperationThrottle( config::OCU::pub::TeleoperationThrottle &msg)
{
	_pub_TeleoperationThrottle.publish(msg);
}
	

void RosComm::publishTeleoperationSteering( config::OCU::pub::TeleoperationSteering &msg)
{
	_pub_TeleoperationSteering.publish(msg);
}
	

void RosComm::publishTeleoperationJoints( config::OCU::pub::TeleoperationJoints &msg)
{
	_pub_TeleoperationJoints.publish(msg);
}
	

void RosComm::publishIEDLocation( config::OCU::pub::IEDLocation &msg)
{
	_pub_IEDLocation.publish(msg);
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
