
/*
 * ComponentMain.cpp
 *
 *  Created on: Thursday, 06. February 2014 04:09PM
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

void ComponentMain::handleOdometry(const config::IEDSIM::sub::Odometry& msg)
{
	std::cout<< "IEDSIM say:" << msg << std::endl;
}
	

void ComponentMain::handleIEDLocation(const config::IEDSIM::sub::IEDLocation& msg)
{
	std::cout<< "IEDSIM say:" << msg << std::endl;
}
	

void ComponentMain::handleIEDSIMCommand(const config::IEDSIM::sub::IEDSIMCommand& msg)
{
	std::cout<< "IEDSIM say:" << msg << std::endl;
}
	

void ComponentMain::publishIEDLocation(config::IEDSIM::pub::IEDLocation& msg)
{
	_roscomm->publishIEDLocation(msg);
}
	

void ComponentMain::publishIEDSIMComponentState(config::IEDSIM::pub::IEDSIMComponentState& msg)
{
	_roscomm->publishIEDSIMComponentState(msg);
}
	
void ComponentMain::publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame){
	_roscomm->publishTransform(_tf, srcFrame, distFrame);
}
tf::StampedTransform ComponentMain::getLastTrasform(std::string srcFrame, std::string distFrame){
	return _roscomm->getLastTrasform(srcFrame, distFrame);;
}
