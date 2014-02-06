
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
	_sub_Sensor_SICK_1=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","Sensor_SICK_1","sub"), 10, &RosComm::Sensor_SICK_1Callback,this));
	_sub_Sensor_SICK_2=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","Sensor_SICK_2","sub"), 10, &RosComm::Sensor_SICK_2Callback,this));
	_sub_Sensor_IBEO_1=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","Sensor_IBEO_1","sub"), 10, &RosComm::Sensor_IBEO_1Callback,this));
	_sub_Sensor_IBEO_2=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","Sensor_IBEO_2","sub"), 10, &RosComm::Sensor_IBEO_2Callback,this));
	_sub_Sensor_IBEO_3=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","Sensor_IBEO_3","sub"), 10, &RosComm::Sensor_IBEO_3Callback,this));
	_sub_Sensor_IBEO_4=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","Sensor_IBEO_4","sub"), 10, &RosComm::Sensor_IBEO_4Callback,this));
	_sub_Sensor_CAM_R=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","Sensor_CAM_R","sub"), 10, &RosComm::Sensor_CAM_RCallback,this));
	_sub_Sensor_CAM_L=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","Sensor_CAM_L","sub"), 10, &RosComm::Sensor_CAM_LCallback,this));
	_sub_Sensor_WIRE=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","Sensor_WIRE","sub"), 10, &RosComm::Sensor_WIRECallback,this));
	_sub_Sensor_INS=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","Sensor_INS","sub"), 10, &RosComm::Sensor_INSCallback,this));
	_sub_Sensor_GPS=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","Sensor_GPS","sub"), 10, &RosComm::Sensor_GPSCallback,this));
	_sub_Odometry=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","Odometry","sub"), 10, &RosComm::OdometryCallback,this));
	_sub_TrottleEffort=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","TrottleEffort","sub"), 10, &RosComm::TrottleEffortCallback,this));
	_sub_SteeringEffort=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","SteeringEffort","sub"), 10, &RosComm::SteeringEffortCallback,this));
	_sub_JointsEffort=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","JointsEffort","sub"), 10, &RosComm::JointsEffortCallback,this));
	_sub_PERCommand=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","PERCommand","sub"), 10, &RosComm::PERCommandCallback,this));
	_pub_MiniMap=ros::Publisher(_nh.advertise<config::PER::pub::MiniMap>(fetchParam(&_nh,"PER","MiniMap","pub"),10));
	_pub_Map=ros::Publisher(_nh.advertise<config::PER::pub::Map>(fetchParam(&_nh,"PER","Map","pub"),10));
	_pub_INS=ros::Publisher(_nh.advertise<config::PER::pub::INS>(fetchParam(&_nh,"PER","INS","pub"),10));
	_pub_GPS=ros::Publisher(_nh.advertise<config::PER::pub::GPS>(fetchParam(&_nh,"PER","GPS","pub"),10));
	_pub_BladPosition=ros::Publisher(_nh.advertise<config::PER::pub::BladPosition>(fetchParam(&_nh,"PER","BladPosition","pub"),10));
	_pub_VOOdometry=ros::Publisher(_nh.advertise<config::PER::pub::VOOdometry>(fetchParam(&_nh,"PER","VOOdometry","pub"),10));
	_pub_SensorsCommand=ros::Publisher(_nh.advertise<config::PER::pub::SensorsCommand>(fetchParam(&_nh,"PER","SensorsCommand","pub"),10));
	_pub_PERSensorsState=ros::Publisher(_nh.advertise<config::PER::pub::PERSensorsState>(fetchParam(&_nh,"PER","PERSensorsState","pub"),10));
	_pub_PERComponentState=ros::Publisher(_nh.advertise<config::PER::pub::PERComponentState>(fetchParam(&_nh,"PER","PERComponentState","pub"),10));
}
RosComm::~RosComm()
{
}
bool RosComm::init(int argc,char** argv){
	ros::init(argc,argv,"PER_node");
	return true;
}


void RosComm::Sensor_SICK_1Callback(const config::PER::sub::Sensor_SICK_1::ConstPtr &msg)
{
	_comp->handleSensor_SICK_1(*msg);
}
	

void RosComm::Sensor_SICK_2Callback(const config::PER::sub::Sensor_SICK_2::ConstPtr &msg)
{
	_comp->handleSensor_SICK_2(*msg);
}
	

void RosComm::Sensor_IBEO_1Callback(const config::PER::sub::Sensor_IBEO_1::ConstPtr &msg)
{
	_comp->handleSensor_IBEO_1(*msg);
}
	

void RosComm::Sensor_IBEO_2Callback(const config::PER::sub::Sensor_IBEO_2::ConstPtr &msg)
{
	_comp->handleSensor_IBEO_2(*msg);
}
	

void RosComm::Sensor_IBEO_3Callback(const config::PER::sub::Sensor_IBEO_3::ConstPtr &msg)
{
	_comp->handleSensor_IBEO_3(*msg);
}
	

void RosComm::Sensor_IBEO_4Callback(const config::PER::sub::Sensor_IBEO_4::ConstPtr &msg)
{
	_comp->handleSensor_IBEO_4(*msg);
}
	

void RosComm::Sensor_CAM_RCallback(const config::PER::sub::Sensor_CAM_R::ConstPtr &msg)
{
	_comp->handleSensor_CAM_R(*msg);
}
	

void RosComm::Sensor_CAM_LCallback(const config::PER::sub::Sensor_CAM_L::ConstPtr &msg)
{
	_comp->handleSensor_CAM_L(*msg);
}
	

void RosComm::Sensor_WIRECallback(const config::PER::sub::Sensor_WIRE::ConstPtr &msg)
{
	_comp->handleSensor_WIRE(*msg);
}
	

void RosComm::Sensor_INSCallback(const config::PER::sub::Sensor_INS::ConstPtr &msg)
{
	_comp->handleSensor_INS(*msg);
}
	

void RosComm::Sensor_GPSCallback(const config::PER::sub::Sensor_GPS::ConstPtr &msg)
{
	_comp->handleSensor_GPS(*msg);
}
	

void RosComm::OdometryCallback(const config::PER::sub::Odometry::ConstPtr &msg)
{
	_comp->handleOdometry(*msg);
}
	

void RosComm::TrottleEffortCallback(const config::PER::sub::TrottleEffort::ConstPtr &msg)
{
	_comp->handleTrottleEffort(*msg);
}
	

void RosComm::SteeringEffortCallback(const config::PER::sub::SteeringEffort::ConstPtr &msg)
{
	_comp->handleSteeringEffort(*msg);
}
	

void RosComm::JointsEffortCallback(const config::PER::sub::JointsEffort::ConstPtr &msg)
{
	_comp->handleJointsEffort(*msg);
}
	

void RosComm::PERCommandCallback(const config::PER::sub::PERCommand::ConstPtr &msg)
{
	_comp->handlePERCommand(*msg);
}
	

void RosComm::publishMiniMap( config::PER::pub::MiniMap &msg)
{
	_pub_MiniMap.publish(msg);
}
	

void RosComm::publishMap( config::PER::pub::Map &msg)
{
	_pub_Map.publish(msg);
}
	

void RosComm::publishINS( config::PER::pub::INS &msg)
{
	_pub_INS.publish(msg);
}
	

void RosComm::publishGPS( config::PER::pub::GPS &msg)
{
	_pub_GPS.publish(msg);
}
	

void RosComm::publishBladPosition( config::PER::pub::BladPosition &msg)
{
	_pub_BladPosition.publish(msg);
}
	

void RosComm::publishVOOdometry( config::PER::pub::VOOdometry &msg)
{
	_pub_VOOdometry.publish(msg);
}
	

void RosComm::publishSensorsCommand( config::PER::pub::SensorsCommand &msg)
{
	_pub_SensorsCommand.publish(msg);
}
	

void RosComm::publishPERSensorsState( config::PER::pub::PERSensorsState &msg)
{
	_pub_PERSensorsState.publish(msg);
}
	

void RosComm::publishPERComponentState( config::PER::pub::PERComponentState &msg)
{
	_pub_PERComponentState.publish(msg);
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
