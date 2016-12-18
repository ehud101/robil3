
/*
 * ComponentMain.h
 *
 *  Created on: Thursday, 27. February 2014 12:29PM
 *      Author: autogenerated
 */
#ifndef COMPONENTMAIN_H_
#define COMPONENTMAIN_H_
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>
#include <tf/tf.h>
#include <boost/thread.hpp>

#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <std_msgs/Float64.h>
#include <diagnostic_msgs/DiagnosticArray.h>
#include <sensor_msgs/JointState.h>
#include <geometry_msgs/TwistStamped.h>

#ifndef HEARTBEAT_FREQUANCY
#define HEARTBEAT_FREQUANCY 2 //Hz
#endif

#ifndef HEARTBEAT_FREQUENCY
#define HEARTBEAT_FREQUENCY 2 //Hz
#endif


class ComponentMain {
	bool _inited;

	  ros::NodeHandle _nh;
	  ros::Publisher _pub_diagnostic;
	  boost::thread_group _maintains;
		ros::Subscriber _sub_WPDVelocity;
		ros::Subscriber _sub_WSMVelocity;
		ros::Subscriber _sub_BladePositionCommand;
		ros::Subscriber _sub_Location;
		ros::Subscriber _sub_PerVelocity;
		ros::Publisher  _pub_EffortsTh;
		ros::Publisher  _pub_EffortsSt;
		ros::Publisher  _pub_EffortsJn;
		ros::Publisher  _pub_Speed;
		pthread_t _myHeartbeatThread;

	  bool init(int argc,char** argv);
public:
	//config::LLC::sub::PerVelocity Per_measured_speed ;	/* real measured speed */
	geometry_msgs::Twist Per_measured_speed ;
	geometry_msgs::TwistStamped WSM_desired_speed ;		/* WSM desired vel. - on work sequence mode */
	geometry_msgs::TwistStamped WPD_desired_speed ;		/* WPD desired vel. - on driving mode */
	sensor_msgs::JointState Blade_angle ; 	/* WSM desired supporter positon */
	geometry_msgs::PoseWithCovarianceStamped Per_pose ; 					/* Per location */
	int t_flag;

	ComponentMain(int argc,char** argv);
	virtual ~ComponentMain();
	void handleWPDVelocity(const geometry_msgs::TwistStamped& msg);
	void handleWSMVelocity(const geometry_msgs::TwistStamped& msg);
	void handleBladePositionCommand(const sensor_msgs::JointState& msg);
	void handleLocation(const geometry_msgs::PoseWithCovarianceStamped& msg);
	void handlePerVelocity(const geometry_msgs::TwistStamped& msg);
	void publishEffortsTh(std_msgs::Float64& msg);
	void publishEffortsSt(std_msgs::Float64& msg);
	void publishEffortsJn(sensor_msgs::JointState& msg);
	void publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame);
	tf::StampedTransform getLastTransform(std::string srcFrame, std::string distFrame);
	void publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report);
	void publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report);
	void heartbeat();
	static void *callHeartbeat(void *pThis);

};
#endif /* COMPONENTMAIN_H_ */

