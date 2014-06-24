
/*
 * RosComm.h
 *
 *  Created on: Thursday, 27. February 2014 12:29PM
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
	ros::Subscriber _sub_WorkSeqData;
	ros::Subscriber _sub_BladePosition;
	ros::Publisher  _pub_WSMVelocity;
	ros::Publisher  _pub_BladePositionCommand;
	ros::Subscriber _sub_Location;
	ros::Subscriber _sub_PerVelocity;

  bool init(int argc,char** argv);
public:
	RosComm(ComponentMain* comp,int argc,char** argv);
	virtual ~RosComm();
	void WorkSeqDataCallback(const config::WSM::sub::WorkSeqData::ConstPtr &msg);
	void BladePositionCallback(const config::WSM::sub::BladePosition::ConstPtr &msg);
	void publishWSMVelocity( config::WSM::pub::WSMVelocity &msg);
	void publishBladePositionCommand( config::WSM::pub::BladePositionCommand &msg);
	void LocationCallback(const config::LLC::sub::Location::ConstPtr &msg);
	void PerVelocityCallback(const config::LLC::sub::PerVelocity::ConstPtr &msg);

	void publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame);
	tf::StampedTransform getLastTrasform(std::string srcFrame, std::string distFrame);
	void publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report);
	void publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report);
	void heartbeat();
};
#endif /* ROSCOMM_H_ */
