
/*
 * RosComm.h
 *
 *  Created on: Thursday, 30. January 2014 04:16PM
 *      Author: autogenerated
 */
#ifndef ROSCOMM_H_
#define ROSCOMM_H_
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>
#include <ParameterTypes.h>
class ComponentMain;
class RosComm {
  ComponentMain   * _comp;
  ros::NodeHandle _nh;
	ros::Subscriber _sub_RPPPath;
	ros::Subscriber _sub_PosAttVel;
	ros::Publisher  _pub_TrottleEffort;
	ros::Publisher  _pub_SteeringEffort;

public:
	RosComm(ComponentMain* comp,int argc,char** argv);
	virtual ~RosComm();
	void RPPPathCallback(const config::WPD::sub::RPPPath::ConstPtr &msg);
	void PosAttVelCallback(const config::WPD::sub::PosAttVel::ConstPtr &msg);
	void publishTrottleEffort( config::WPD::pub::TrottleEffort &msg);
	void publishSteeringEffort( config::WPD::pub::SteeringEffort &msg);

};
#endif /* ROSCOMM_H_ */