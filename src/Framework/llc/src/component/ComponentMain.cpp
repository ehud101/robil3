
/*
 * ComponentMain.cpp
 *
 *  Created on: Thursday, 27. February 2014 12:29PM
 *      Author: autogenerated
 */
#include "ComponentMain.h"

#include <ros/ros.h>
#include <std_msgs/String.h>


#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>
//#include "ParameterHandler.h"
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#define TEST_HEARTBEAT

ComponentMain::ComponentMain(int argc,char** argv)
: _inited(init(argc, argv))
{
	_sub_WPDVelocity=ros::Subscriber(_nh.subscribe("/WPD/Speed", 10, &ComponentMain::handleWPDVelocity,this));
	_sub_WSMVelocity=ros::Subscriber(_nh.subscribe("/WSM/Speed", 10, &ComponentMain::handleWSMVelocity,this));
	_sub_BladePositionCommand=ros::Subscriber(_nh.subscribe("/WSM/BladePosition", 10, &ComponentMain::handleBladePositionCommand,this));
	_sub_Location=ros::Subscriber(_nh.subscribe("/LOC/Pose", 10, &ComponentMain::handleLocation,this));
	_sub_PerVelocity=ros::Subscriber(_nh.subscribe("/LOC/Velocity", 10, &ComponentMain::handlePerVelocity,this));
	_pub_EffortsTh=ros::Publisher(_nh.advertise<std_msgs::Float64>("/LLC/EFFORTS/Throttle",10));
	_pub_EffortsSt=ros::Publisher(_nh.advertise<std_msgs::Float64>("/LLC/EFFORTS/Steering",10));
	_pub_EffortsJn=ros::Publisher(_nh.advertise<std_msgs::Float64>("/LLC/EFFORTS/Joints",10));
	_pub_diagnostic=ros::Publisher(_nh.advertise<diagnostic_msgs::DiagnosticArray>("/diagnostics",100));
	//_maintains.add_thread(new boost::thread(boost::bind(&ComponentMain::heartbeat,this)));
	    //Replace the thread group with a simple pthread because there is a SIGEV otherwise
		// and I didn't find the reason.
		// With pthread, it seems to work.
#ifdef TEST_HEARTBEAT
		_myHeartbeatThread = (pthread_t) NULL;
		pthread_create(&_myHeartbeatThread, NULL, &callHeartbeat, this);
#endif
}

ComponentMain::~ComponentMain() {
#ifdef TEST_HEARTBEAT
	if (_myHeartbeatThread) {
		pthread_cancel(_myHeartbeatThread);
		_myHeartbeatThread = (pthread_t)NULL;
	}
#endif
}

bool ComponentMain::init(int argc,char** argv){
	ros::init(argc,argv,"LLC_node");
	return true;
}

void ComponentMain::handleWPDVelocity(const config::LLC::sub::WPDVelocity& msg)
{
	this->WPD_desired_speed.twist.linear.x = msg.twist.linear.x ;
	this->WPD_desired_speed.twist.angular.z = msg.twist.angular.z ;

	//std::cout<< "LLC say:" << this->WPD_desired_speed << std::endl;

}
	
void ComponentMain::handleWSMVelocity(const config::LLC::sub::WSMVelocity& msg)
{

	this->WSM_desired_speed.twist.linear.x = msg.twist.linear.x ;
	this->WSM_desired_speed.twist.angular.z = msg.twist.angular.z ;

	//std::cout<< "LLC say:" << msg << std::endl;
}
	

void ComponentMain::handleBladePositionCommand(const config::LLC::sub::BladePositionCommand& msg)
{
	this->t_flag = 1 ;
	this->Blade_angle = msg ;
	//std::cout<< "Got blade command:" << msg << std::endl;
}
	
void ComponentMain::handleLocation(const config::LLC::sub::Location& msg)
{
	this->Per_pose = msg ;
	//std::cout<< "LLC say:" << msg << std::endl;
}
	

void ComponentMain::handlePerVelocity(const config::LLC::sub::PerVelocity& msg)
{

	this->Per_measured_speed.linear.x = msg.twist.linear.x ;
	this->Per_measured_speed.angular.z = msg.twist.angular.z ;

//	std::cout<< "LLC say:" << msg << std::endl;
}
	

void ComponentMain::publishEffortsTh(config::LLC::pub::EffortsTh& msg)
{
	_pub_EffortsTh.publish(msg);
}
	

void ComponentMain::publishEffortsSt(config::LLC::pub::EffortsSt& msg)
{
	_pub_EffortsSt.publish(msg);
}
	

void ComponentMain::publishEffortsJn(sensor_msgs::JointState& msg)
{
	_pub_EffortsJn.publish(msg);
}

void ComponentMain::publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame){
	static tf::TransformBroadcaster br;
	br.sendTransform(tf::StampedTransform(_tf, ros::Time::now(), srcFrame, distFrame));
}
tf::StampedTransform ComponentMain::getLastTransform(std::string srcFrame, std::string distFrame){
	tf::StampedTransform _tf;
		static tf::TransformListener listener;
		try {
		    listener.waitForTransform(distFrame, srcFrame, ros::Time(0), ros::Duration(10.0) );
		    listener.lookupTransform(distFrame, srcFrame, ros::Time(0), _tf);
		} catch (tf::TransformException& ex) {
		    ROS_ERROR("%s",ex.what());
		}
		return _tf;
}
void ComponentMain::publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report){
	diagnostic_msgs::DiagnosticArray msg;
		msg.status.push_back(_report);
		_pub_diagnostic.publish(msg);
}
void ComponentMain::publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report){
	diagnostic_msgs::DiagnosticArray msg;
		msg.header = header;
		msg.status.push_back(_report);
		_pub_diagnostic.publish(msg);
}

void ComponentMain::heartbeat(){
	//using namespace boost::posix_time;
	ros::Publisher _pub = _nh.advertise<std_msgs::String>("/heartbeat", 10);
	double hz = HEARTBEAT_FREQUENCY;
	double cycle = (1/hz);
	ros::Duration oneSec(cycle);

	while(ros::ok()){
		//boost::system_time stop_time = boost::get_system_time() + milliseconds((1/hz)*1000);
		std_msgs::String msg;
		msg.data = "LLC";
		_pub.publish(msg);
		oneSec.sleep();
	   // boost::this_thread::sleep(stop_time);
	}
}

void * ComponentMain::callHeartbeat(void * pParam)
{
	ComponentMain *myHandle = (ComponentMain *) (pParam);

	myHandle->heartbeat();

}
