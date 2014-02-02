
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

void ComponentMain::handleSpeed(const config::LLC::sub::Speed& msg)
{
	std::cout<< "LLC say:" << msg << std::endl;
}
	

void ComponentMain::handleTrottleEffort(const config::LLC::sub::TrottleEffort& msg)
{
	std::cout<< "LLC say:" << msg << std::endl;
}
	

void ComponentMain::handleSteeringEffort(const config::LLC::sub::SteeringEffort& msg)
{
	std::cout<< "LLC say:" << msg << std::endl;
}
	

void ComponentMain::handleJointsEffort(const config::LLC::sub::JointsEffort& msg)
{
	std::cout<< "LLC say:" << msg << std::endl;
}
	

void ComponentMain::handleTeleoperation(const config::LLC::sub::Teleoperation& msg)
{
	std::cout<< "LLC say:" << msg << std::endl;
}
	

void ComponentMain::publishTrottleEffort(config::LLC::pub::TrottleEffort& msg)
{
	_roscomm->publishTrottleEffort(msg);
}
	

void ComponentMain::publishSteeringEffort(config::LLC::pub::SteeringEffort& msg)
{
	_roscomm->publishSteeringEffort(msg);
}
	

void ComponentMain::publishJointsEffort(config::LLC::pub::JointsEffort& msg)
{
	_roscomm->publishJointsEffort(msg);
}
	
