
/*
 * RosComm.h
 *
 *  Created on: Sunday, 02. February 2014 10:15AM
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
  bool _inited;
  ComponentMain   * _comp;
  ros::NodeHandle _nh;
	ros::Subscriber _sub_Camera;
	ros::Subscriber _sub_INS;
	ros::Subscriber _sub_TF;
	ros::Publisher  _pub_PosAttVel;

  bool init(int argc,char** argv);
public:
	RosComm(ComponentMain* comp,int argc,char** argv);
	virtual ~RosComm();
	void CameraCallback(const config::VO::sub::Camera::ConstPtr &msg);
	void INSCallback(const config::VO::sub::INS::ConstPtr &msg);
	void TFCallback(const config::VO::sub::TF::ConstPtr &msg);
	void publishPosAttVel( config::VO::pub::PosAttVel &msg);

};
#endif /* ROSCOMM_H_ */
