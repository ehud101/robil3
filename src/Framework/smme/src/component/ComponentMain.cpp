
/*
 * ComponentMain.cpp
 *
 *  Created on: Thursday, 27. February 2014 12:29PM
 *      Author: autogenerated
 */
#include "ComponentMain.h"
#include "MissionManager.h"
#include "ComponentStates.h"
#include <decision_making/ROSTask.h>
#include <tf/transform_listener.h>

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>
#include "ParameterHandler.h"
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
std::map<std::string, boost::shared_ptr<MissionMachine> > machines;
namespace {

template<class T>
bool operator<(const T& e, const std::set<T>& s){
	return s.find(e)!=s.end();
}
template<class T>
bool operator!=(const T& e, const std::set<T>& s){
	return s.find(e)==s.end();
}
#define in <
#define not_in !=



tf::TransformListener* tf_listener;

}


ComponentMain::ComponentMain(int argc,char** argv)
: _inited(init(argc, argv)), _events(0)
{
	_sub_AssignNavTask=ros::Subscriber(_nh.subscribe("/OCU/SMME/NavigationTask", 10, &ComponentMain::handleAssignNavTask,this));
	_sub_AssignManTask=ros::Subscriber(_nh.subscribe("/OCU/SMME/ManipulationTask", 10, &ComponentMain::handleAssignManTask,this));
	_sub_AssignMission=ros::Subscriber(_nh.subscribe("/OCU/SMME/MissionPlan", 10, &ComponentMain::handleAssignMission,this));
	_sub_BladePosition=ros::Subscriber(_nh.subscribe("/PER/BladPosition", 10, &ComponentMain::handleBladePosition,this));
	_sub_Location=ros::Subscriber(_nh.subscribe("/LOC/Pose", 10, &ComponentMain::handleLocation,this));
	_sub_IEDLocation=ros::Subscriber(_nh.subscribe("/IED/Location", 10, &ComponentMain::handleIEDLocation,this));
	_pub_GlobalPath=ros::Publisher(_nh.advertise<robil_msgs::Path>("/SMME/GlobalPath",10));
	_pub_WorkSeqData=ros::Publisher(_nh.advertise<robil_msgs::AssignManipulatorTask>("/SMME/WSM/Task",10));
	_pub_MissionAcceptance=ros::Publisher(_nh.advertise<robil_msgs::MissionAcceptance>("/SMME/OCU/MissionAcceptance",10));
	_pub_diagnostic=ros::Publisher(_nh.advertise<diagnostic_msgs::DiagnosticArray>("/diagnostics",100));
	_maintains.add_thread(new boost::thread(boost::bind(&ComponentMain::heartbeat,this)));

	_mission_manager = new MissionManager();
	_mission_manager->conf.start_mission_state="loaded";
	_mission_manager->conf.start_task_state="loaded";
	_mission_manager->conf.stop_task_state="unloaded";
	tf_listener = new tf::TransformListener();
	ROS_INFO("Mission manager created");
}

ComponentMain::~ComponentMain() {
	if(_mission_manager) delete _mission_manager; _mission_manager=0;
	delete tf_listener;
}

bool ComponentMain::init(int argc,char** argv){
	ros::init(argc,argv,"SMME_node");
	return true;
}

void ComponentMain::handleAssignNavTask(const config::SMME::sub::AssignNavTask& msg)
{
	_mission_manager->assign(msg);
}
	

void ComponentMain::handleAssignManTask(const config::SMME::sub::AssignManTask& msg)
{
	_mission_manager->assign(msg);
}
	

void ComponentMain::handleAssignMission(const config::SMME::sub::AssignMission& msg)
{
	config::SMME::pub::MissionAcceptance acceptance =
			_mission_manager->assign(msg);
	if(acceptance.status==0){
		ROS_INFO_STREAM("Mission "<<msg.mission_id<<" accepted");
		machines[msg.mission_id]=boost::shared_ptr<MissionMachine>(new MissionMachine(this,msg.mission_id));
		machines[msg.mission_id]->start();
	}else
	if(acceptance.status == 1000){
		acceptance.status = 0;
		ROS_INFO_STREAM("Mission "<<msg.mission_id<<" accepted, but continue with same mission fsm");
	}else{
		ROS_INFO_STREAM("Mission "<<msg.mission_id<<" rejected (error="<<acceptance.status<<")");
	}
	publishMissionAcceptance(acceptance);
}
	

void ComponentMain::handleBladePosition(const config::SMME::sub::BladePosition& msg)
{
	//std::cout<< "SMME say:" << msg << std::endl;
}
	

void ComponentMain::handleLocation(const config::SMME::sub::Location& msg)
{
	//std::cout<< "SMME say:" << msg << std::endl;
}
	
void ComponentMain::handleIEDLocation(const config::IEDSIM::pub::IEDLocation& msg)
{
	if(msg.is_detected==1){
		tf::StampedTransform transform;
		geometry_msgs::PointStamped location_local, location_global;
		location_local.point = msg.location;
		try{
			location_local.header.stamp = ros::Time(0);
			location_local.header.frame_id = "base_link";
			tf_listener->transformPoint( "map" , location_local, location_global);

			if(location_global.point not_in knownIEDObjects){
				std:stringstream buff;
				check_if_not_contains(location_global.point, knownIEDObjects, buff);
				if(events()) events()->raiseEvent("/IEDDetected");
				knownIEDObjects.insert(location_global.point);
				ROS_INFO_STREAM("SMME: new IED object detected: its global pose is "<<location_global.point.x<<", "<<location_global.point.y<<", "<<location_global.point.z);
				ROS_INFO_STREAM("SMME: new IED object detected: ... \n"<<buff.str());
			}
		}
		catch (tf::TransformException& ex){
			ROS_ERROR("ComponentMain::handleIEDLocation: ERROR: %s",ex.what());
			return;
		}
	}
}

void ComponentMain::publishGlobalPath(config::SMME::pub::GlobalPath& msg)
{
	_pub_GlobalPath.publish(msg);
}
	

void ComponentMain::publishWorkSeqData(config::SMME::pub::WorkSeqData& msg)
{
	_pub_WorkSeqData.publish(msg);
}
	

void ComponentMain::publishMissionAcceptance(config::SMME::pub::MissionAcceptance& msg)
{
	_pub_MissionAcceptance.publish(msg);
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
		using namespace boost::posix_time;
		ros::Publisher _pub = _nh.advertise<std_msgs::String>("/heartbeat", 10);
		double hz = HEARTBEAT_FREQUANCY;
		while(ros::ok()){
			boost::system_time stop_time = boost::get_system_time() + milliseconds((1/hz)*1000);
			std_msgs::String msg;
			msg.data = "SMME";
			_pub.publish(msg);
		    boost::this_thread::sleep(stop_time);
		}
}
