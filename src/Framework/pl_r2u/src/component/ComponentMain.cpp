
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

void ComponentMain::handleTrottleEffort(const config::PL_R2U::sub::TrottleEffort& msg)
{
	std::cout<< "PL_R2U say:" << msg << std::endl;
}
	

void ComponentMain::handleSteeringEffort(const config::PL_R2U::sub::SteeringEffort& msg)
{
	std::cout<< "PL_R2U say:" << msg << std::endl;
}
	

void ComponentMain::handleJointsEffort(const config::PL_R2U::sub::JointsEffort& msg)
{
	std::cout<< "PL_R2U say:" << msg << std::endl;
}
	

