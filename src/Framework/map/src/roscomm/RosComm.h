
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
	ros::Subscriber _sub_BladePosition;
	ros::Subscriber _sub_PosAttVel;
	ros::Subscriber _sub_Laser;
	ros::Subscriber _sub_Camera;
	ros::Publisher  _pub_Map;
	ros::Publisher  _pub_MiniMap;

  bool init(int argc,char** argv);
public:
	RosComm(ComponentMain* comp,int argc,char** argv);
	virtual ~RosComm();
	void BladePositionCallback(const config::MAP::sub::BladePosition::ConstPtr &msg);
	void PosAttVelCallback(const config::MAP::sub::PosAttVel::ConstPtr &msg);
	void LaserCallback(const config::MAP::sub::Laser::ConstPtr &msg);
	void CameraCallback(const config::MAP::sub::Camera::ConstPtr &msg);
	void publishMap( config::MAP::pub::Map &msg);
	void publishMiniMap( config::MAP::pub::MiniMap &msg);

};
#endif /* ROSCOMM_H_ */
