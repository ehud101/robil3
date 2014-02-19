
/*
 * RosComm.h
 *
 *  Created on: Wednesday, 19. February 2014 02:59PM
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
#include <boost/thread.hpp>
class ComponentMain;
class RosComm {
  bool _inited;
  ComponentMain   * _comp;
  ros::NodeHandle _nh;
  ros::Publisher _pub_diagnostic;
  boost::thread_group _maintains;

	ros::Publisher  _pub_SensorINS;
	ros::Publisher  _pub_SensorGPS;
	ros::Publisher  _pub_SensorCamL;
	ros::Publisher  _pub_SensorCamR;
	ros::Publisher  _pub_SensorWire;
	ros::Publisher  _pub_SensorSICK;
	ros::Publisher  _pub_SensorIBEO1;
	ros::Publisher  _pub_SensorIBEO2;
	ros::Publisher  _pub_SensorIBEO3;
	ros::Publisher  _pub_SensorIBEO4;

  bool init(int argc,char** argv);
public:
	RosComm(ComponentMain* comp,int argc,char** argv);
	virtual ~RosComm();

	void publishSensorINS( config::SENSORS::pub::SensorINS &msg);
	void publishSensorGPS( config::SENSORS::pub::SensorGPS &msg);
	void publishSensorCamL( config::SENSORS::pub::SensorCamL &msg);
	void publishSensorCamR( config::SENSORS::pub::SensorCamR &msg);
	void publishSensorWire( config::SENSORS::pub::SensorWire &msg);
	void publishSensorSICK( config::SENSORS::pub::SensorSICK &msg);
	void publishSensorIBEO1( config::SENSORS::pub::SensorIBEO1 &msg);
	void publishSensorIBEO2( config::SENSORS::pub::SensorIBEO2 &msg);
	void publishSensorIBEO3( config::SENSORS::pub::SensorIBEO3 &msg);
	void publishSensorIBEO4( config::SENSORS::pub::SensorIBEO4 &msg);

	void publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame);
	tf::StampedTransform getLastTrasform(std::string srcFrame, std::string distFrame);
	void publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report);
	void publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report);
	void heartbeat();
};
#endif /* ROSCOMM_H_ */
