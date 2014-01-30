
/*
 * ComponentMain.cpp
 *
 *  Created on: Thursday, 30. January 2014 04:16PM
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

void ComponentMain::handleRPPPath(const config::WPD::sub::RPPPath& msg)
{
	std::cout<< "WPD say:" << msg.data << std::endl;
}
	

void ComponentMain::handlePosAttVel(const config::WPD::sub::PosAttVel& msg)
{
	std::cout<< "WPD say:" << msg.data << std::endl;
}
	

void ComponentMain::publishTrottleEffort(config::WPD::pub::TrottleEffort& msg)
{
	_roscomm->publishTrottleEffort(msg);
}
	

void ComponentMain::publishSteeringEffort(config::WPD::pub::SteeringEffort& msg)
{
	_roscomm->publishSteeringEffort(msg);
}
	