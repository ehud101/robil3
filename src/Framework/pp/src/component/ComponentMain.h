
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
//#include <ParameterTypes.h>
#include <tf/tf.h>
#include <boost/thread.hpp>

#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <diagnostic_msgs/DiagnosticArray.h>
#include <robil_msgs/Path.h>
#include <robil_msgs/Map.h>
#include <sensor_msgs/JointState.h>


#ifndef COMPONENT
#define COMPONENT context.parameters<Params>().comp
#endif

class MoveBase;
namespace decision_making{ class EventQueue; }

class ComponentMain {
	MoveBase* _move_base;
	decision_making::EventQueue* _events;
	boost::mutex _mt;
	 bool _inited;
	  ComponentMain   * _comp;
	  ros::NodeHandle _nh;
	  ros::Publisher _pub_diagnostic;
	  boost::thread_group _maintains;
		ros::Subscriber _sub_GlobalPath;
		ros::Subscriber _sub_BladePosition;
		ros::Subscriber _sub_Map;
		ros::Subscriber _sub_Location;
		ros::Publisher  _pub_LocalPath;

	  bool init(int argc,char** argv);
public:
	ComponentMain(int argc,char** argv);
	virtual ~ComponentMain();
	void handleGlobalPath(const robil_msgs::Path& msg);
	void handleBladePosition(const sensor_msgs::JointState& msg);
	void handleMap(const robil_msgs::Map& msg);
	void handleLocation(const geometry_msgs::PoseWithCovarianceStamped& msg);
	void publishLocalPath(robil_msgs::Path& msg);
	void publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame);
	tf::StampedTransform getLastTransform(std::string srcFrame, std::string distFrame);
	void publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report);
	void publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report);

	void set_events(decision_making::EventQueue* events);
	void rise_taskFinished();
	void rise_taskAborted();
	void rise_taskStarted();
	void rise_taskPaused();

	void cancel_navigation();
	void pause_navigation();
	void resume_navigation();

	void heartbeat();
};
#endif /* COMPONENTMAIN_H_ */
