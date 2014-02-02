
/*
 * RosComm.h
 *
 *  Created on: Sunday, 02. February 2014 03:25PM
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
#include <tf/tf.h>
class ComponentMain;
class RosComm {
  bool _inited;
  ComponentMain   * _comp;
  ros::NodeHandle _nh;
	ros::Subscriber _sub_Sensor_WIRE;
	ros::Subscriber _sub_Sensor_INS;
	ros::Subscriber _sub_Sensor_GPS;


  bool init(int argc,char** argv);
public:
	RosComm(ComponentMain* comp,int argc,char** argv);
	virtual ~RosComm();
	void Sensor_WIRECallback(const config::SE_R2U::sub::Sensor_WIRE::ConstPtr &msg);
	void Sensor_INSCallback(const config::SE_R2U::sub::Sensor_INS::ConstPtr &msg);
	void Sensor_GPSCallback(const config::SE_R2U::sub::Sensor_GPS::ConstPtr &msg);


  void publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame);
  tf::StampedTransform getLastTrasform(std::string srcFrame, std::string distFrame);
};
#endif /* ROSCOMM_H_ */
