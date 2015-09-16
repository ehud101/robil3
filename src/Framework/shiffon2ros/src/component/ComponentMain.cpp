
/*
 * ComponentMain.cpp
 *
 *  Created on: Monday, 07. September 2015 03:23PM
 *      Author: autogenerated
 */
#include "ComponentMain.h"
#include "../roscomm/RosComm.h"
ComponentMain::ComponentMain(int argc,char** argv)
{
	_roscomm = new RosComm(this,argc, argv);
}
ComponentMain::~ComponentMain() {
	if(_roscomm) delete _roscomm; _roscomm=0;
}


void ComponentMain::publishGPS(config::SHIFFON2ROS::pub::GPS& msg)
{
	_roscomm->publishGPS(msg);
}
	

void ComponentMain::publishINS(config::SHIFFON2ROS::pub::INS& msg)
{
	_roscomm->publishINS(msg);
}
	

void ComponentMain::publishGpsSpeed(config::SHIFFON2ROS::pub::GpsSpeed& msg)
{
	_roscomm->publishGpsSpeed(msg);
}
	
void ComponentMain::publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame){
	_roscomm->publishTransform(_tf, srcFrame, distFrame);
}
tf::StampedTransform ComponentMain::getLastTrasform(std::string srcFrame, std::string distFrame){
	return _roscomm->getLastTrasform(srcFrame, distFrame);
}
void ComponentMain::publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report){
	_roscomm->publishDiagnostic(_report);
}
void ComponentMain::publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report){
	_roscomm->publishDiagnostic(header, _report);
}
