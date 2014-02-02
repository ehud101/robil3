
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
	ros::Subscriber _sub_IEDDetectionEvent;
	ros::Subscriber _sub_IEDLocation;
	ros::Publisher  _pub_IEDDetectionEvent;
	ros::Publisher  _pub_IEDLocation;

  bool init(int argc,char** argv);
public:
	RosComm(ComponentMain* comp,int argc,char** argv);
	virtual ~RosComm();
	void IEDDetectionEventCallback(const config::IEDSIM::sub::IEDDetectionEvent::ConstPtr &msg);
	void IEDLocationCallback(const config::IEDSIM::sub::IEDLocation::ConstPtr &msg);
	void publishIEDDetectionEvent( config::IEDSIM::pub::IEDDetectionEvent &msg);
	void publishIEDLocation( config::IEDSIM::pub::IEDLocation &msg);

};
#endif /* ROSCOMM_H_ */
