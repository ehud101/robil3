
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
	ros::Subscriber _sub_PosAttVel;
	ros::Subscriber _sub_PositionUpdate;
	ros::Publisher  _pub_PosAttVel;

public:
	RosComm(ComponentMain* comp,int argc,char** argv);
	virtual ~RosComm();
	void PosAttVelCallback(const config::LOC::sub::PosAttVel::ConstPtr &msg);
	void PositionUpdateCallback(const config::LOC::sub::PositionUpdate::ConstPtr &msg);
	void publishPosAttVel( config::LOC::pub::PosAttVel &msg);

};
#endif /* ROSCOMM_H_ */