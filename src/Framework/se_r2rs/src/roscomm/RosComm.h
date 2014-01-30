
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
	ros::Subscriber _sub_Sensor_SICK;
	ros::Subscriber _sub_Sensor_IBEO;
	ros::Subscriber _sub_Sensor_CAM_R;
	ros::Subscriber _sub_Sensor_CAM_L;


public:
	RosComm(ComponentMain* comp,int argc,char** argv);
	virtual ~RosComm();
	void Sensor_SICKCallback(const config::SE_R2RS::sub::Sensor_SICK::ConstPtr &msg);
	void Sensor_IBEOCallback(const config::SE_R2RS::sub::Sensor_IBEO::ConstPtr &msg);
	void Sensor_CAM_RCallback(const config::SE_R2RS::sub::Sensor_CAM_R::ConstPtr &msg);
	void Sensor_CAM_LCallback(const config::SE_R2RS::sub::Sensor_CAM_L::ConstPtr &msg);


};
#endif /* ROSCOMM_H_ */