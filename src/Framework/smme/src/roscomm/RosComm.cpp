
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
	_sub_Odometry=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"SMME","Odometry","sub"), 10, &RosComm::OdometryCallback,this));
	_sub_BladPosition=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"SMME","BladPosition","sub"), 10, &RosComm::BladPositionCallback,this));
	_sub_PPExecutionState=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"SMME","PPExecutionState","sub"), 10, &RosComm::PPExecutionStateCallback,this));
	_sub_WSMExecutionState=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"SMME","WSMExecutionState","sub"), 10, &RosComm::WSMExecutionStateCallback,this));
	_sub_IEDLocation=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"SMME","IEDLocation","sub"), 10, &RosComm::IEDLocationCallback,this));
	_sub_PlatformState=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"SMME","PlatformState","sub"), 10, &RosComm::PlatformStateCallback,this));
	_sub_SoftwareState=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"SMME","SoftwareState","sub"), 10, &RosComm::SoftwareStateCallback,this));
	_sub_SensorsState=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"SMME","SensorsState","sub"), 10, &RosComm::SensorsStateCallback,this));
	_sub_SMMECommand=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"SMME","SMMECommand","sub"), 10, &RosComm::SMMECommandCallback,this));
	_sub_SMMEControlMode=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"SMME","SMMEControlMode","sub"), 10, &RosComm::SMMEControlModeCallback,this));
	_sub_NavigationTask=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"SMME","NavigationTask","sub"), 10, &RosComm::NavigationTaskCallback,this));
	_sub_ManipulationTask=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"SMME","ManipulationTask","sub"), 10, &RosComm::ManipulationTaskCallback,this));
	_sub_MissionTask=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"SMME","MissionTask","sub"), 10, &RosComm::MissionTaskCallback,this));
	_pub_WSMData=ros::Publisher(_nh.advertise<config::SMME::pub::WSMData>(fetchParam(&_nh,"SMME","WSMData","pub"),10));
	_pub_MissionAcceptance=ros::Publisher(_nh.advertise<config::SMME::pub::MissionAcceptance>(fetchParam(&_nh,"SMME","MissionAcceptance","pub"),10));
	_pub_GlobalPath=ros::Publisher(_nh.advertise<config::SMME::pub::GlobalPath>(fetchParam(&_nh,"SMME","GlobalPath","pub"),10));
	_pub_MaxSpeed=ros::Publisher(_nh.advertise<config::SMME::pub::MaxSpeed>(fetchParam(&_nh,"SMME","MaxSpeed","pub"),10));
	_pub_SMMEMissionState=ros::Publisher(_nh.advertise<config::SMME::pub::SMMEMissionState>(fetchParam(&_nh,"SMME","SMMEMissionState","pub"),10));
	_pub_SMMEComponentState=ros::Publisher(_nh.advertise<config::SMME::pub::SMMEComponentState>(fetchParam(&_nh,"SMME","SMMEComponentState","pub"),10));
	_pub_WPDCommand=ros::Publisher(_nh.advertise<config::SMME::pub::WPDCommand>(fetchParam(&_nh,"SMME","WPDCommand","pub"),10));
	_pub_PPCommand=ros::Publisher(_nh.advertise<config::SMME::pub::PPCommand>(fetchParam(&_nh,"SMME","PPCommand","pub"),10));
	_pub_IEDSIMCommand=ros::Publisher(_nh.advertise<config::SMME::pub::IEDSIMCommand>(fetchParam(&_nh,"SMME","IEDSIMCommand","pub"),10));
	_pub_SSMCommand=ros::Publisher(_nh.advertise<config::SMME::pub::SSMCommand>(fetchParam(&_nh,"SMME","SSMCommand","pub"),10));
	_pub_WSMCommand=ros::Publisher(_nh.advertise<config::SMME::pub::WSMCommand>(fetchParam(&_nh,"SMME","WSMCommand","pub"),10));
	_pub_LLCCommand=ros::Publisher(_nh.advertise<config::SMME::pub::LLCCommand>(fetchParam(&_nh,"SMME","LLCCommand","pub"),10));
	_pub_LOCCommand=ros::Publisher(_nh.advertise<config::SMME::pub::LOCCommand>(fetchParam(&_nh,"SMME","LOCCommand","pub"),10));
	_pub_PERCommand=ros::Publisher(_nh.advertise<config::SMME::pub::PERCommand>(fetchParam(&_nh,"SMME","PERCommand","pub"),10));
}
RosComm::~RosComm()
{
}
bool RosComm::init(int argc,char** argv){
	ros::init(argc,argv,"SMME_node");
	return true;
}


void RosComm::OdometryCallback(const config::SMME::sub::Odometry::ConstPtr &msg)
{
	_comp->handleOdometry(*msg);
}
	

void RosComm::BladPositionCallback(const config::SMME::sub::BladPosition::ConstPtr &msg)
{
	_comp->handleBladPosition(*msg);
}
	

void RosComm::PPExecutionStateCallback(const config::SMME::sub::PPExecutionState::ConstPtr &msg)
{
	_comp->handlePPExecutionState(*msg);
}
	

void RosComm::WSMExecutionStateCallback(const config::SMME::sub::WSMExecutionState::ConstPtr &msg)
{
	_comp->handleWSMExecutionState(*msg);
}
	

void RosComm::IEDLocationCallback(const config::SMME::sub::IEDLocation::ConstPtr &msg)
{
	_comp->handleIEDLocation(*msg);
}
	

void RosComm::PlatformStateCallback(const config::SMME::sub::PlatformState::ConstPtr &msg)
{
	_comp->handlePlatformState(*msg);
}
	

void RosComm::SoftwareStateCallback(const config::SMME::sub::SoftwareState::ConstPtr &msg)
{
	_comp->handleSoftwareState(*msg);
}
	

void RosComm::SensorsStateCallback(const config::SMME::sub::SensorsState::ConstPtr &msg)
{
	_comp->handleSensorsState(*msg);
}
	

void RosComm::SMMECommandCallback(const config::SMME::sub::SMMECommand::ConstPtr &msg)
{
	_comp->handleSMMECommand(*msg);
}
	

void RosComm::SMMEControlModeCallback(const config::SMME::sub::SMMEControlMode::ConstPtr &msg)
{
	_comp->handleSMMEControlMode(*msg);
}
	

void RosComm::NavigationTaskCallback(const config::SMME::sub::NavigationTask::ConstPtr &msg)
{
	_comp->handleNavigationTask(*msg);
}
	

void RosComm::ManipulationTaskCallback(const config::SMME::sub::ManipulationTask::ConstPtr &msg)
{
	_comp->handleManipulationTask(*msg);
}
	

void RosComm::MissionTaskCallback(const config::SMME::sub::MissionTask::ConstPtr &msg)
{
	_comp->handleMissionTask(*msg);
}
	

void RosComm::publishWSMData( config::SMME::pub::WSMData &msg)
{
	_pub_WSMData.publish(msg);
}
	

void RosComm::publishMissionAcceptance( config::SMME::pub::MissionAcceptance &msg)
{
	_pub_MissionAcceptance.publish(msg);
}
	

void RosComm::publishGlobalPath( config::SMME::pub::GlobalPath &msg)
{
	_pub_GlobalPath.publish(msg);
}
	

void RosComm::publishMaxSpeed( config::SMME::pub::MaxSpeed &msg)
{
	_pub_MaxSpeed.publish(msg);
}
	

void RosComm::publishSMMEMissionState( config::SMME::pub::SMMEMissionState &msg)
{
	_pub_SMMEMissionState.publish(msg);
}
	

void RosComm::publishSMMEComponentState( config::SMME::pub::SMMEComponentState &msg)
{
	_pub_SMMEComponentState.publish(msg);
}
	

void RosComm::publishWPDCommand( config::SMME::pub::WPDCommand &msg)
{
	_pub_WPDCommand.publish(msg);
}
	

void RosComm::publishPPCommand( config::SMME::pub::PPCommand &msg)
{
	_pub_PPCommand.publish(msg);
}
	

void RosComm::publishIEDSIMCommand( config::SMME::pub::IEDSIMCommand &msg)
{
	_pub_IEDSIMCommand.publish(msg);
}
	

void RosComm::publishSSMCommand( config::SMME::pub::SSMCommand &msg)
{
	_pub_SSMCommand.publish(msg);
}
	

void RosComm::publishWSMCommand( config::SMME::pub::WSMCommand &msg)
{
	_pub_WSMCommand.publish(msg);
}
	

void RosComm::publishLLCCommand( config::SMME::pub::LLCCommand &msg)
{
	_pub_LLCCommand.publish(msg);
}
	

void RosComm::publishLOCCommand( config::SMME::pub::LOCCommand &msg)
{
	_pub_LOCCommand.publish(msg);
}
	

void RosComm::publishPERCommand( config::SMME::pub::PERCommand &msg)
{
	_pub_PERCommand.publish(msg);
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
