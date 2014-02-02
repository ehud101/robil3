
/*
 * ComponentMain.cpp
 *
 *  Created on: Sunday, 02. February 2014 10:15AM
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

void ComponentMain::handleIEDDetectionEvent(const config::IEDSIM::sub::IEDDetectionEvent& msg)
{
	std::cout<< "IEDSIM say:" << msg << std::endl;
}
	

void ComponentMain::handleIEDLocation(const config::IEDSIM::sub::IEDLocation& msg)
{
	std::cout<< "IEDSIM say:" << msg << std::endl;
}
	

void ComponentMain::publishIEDDetectionEvent(config::IEDSIM::pub::IEDDetectionEvent& msg)
{
	_roscomm->publishIEDDetectionEvent(msg);
}
	

void ComponentMain::publishIEDLocation(config::IEDSIM::pub::IEDLocation& msg)
{
	_roscomm->publishIEDLocation(msg);
}
	
