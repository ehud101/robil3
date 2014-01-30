
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

void ComponentMain::handleIEDDetectionEvent(const config::SMME::sub::IEDDetectionEvent& msg)
{
	std::cout<< "SMME say:" << msg.data << std::endl;
}
	

void ComponentMain::handleIEDLocation(const config::SMME::sub::IEDLocation& msg)
{
	std::cout<< "SMME say:" << msg.data << std::endl;
}
	

void ComponentMain::handleMissionPlan(const config::SMME::sub::MissionPlan& msg)
{
	std::cout<< "SMME say:" << msg.data << std::endl;
}
	

void ComponentMain::handleStatusData(const config::SMME::sub::StatusData& msg)
{
	std::cout<< "SMME say:" << msg.data << std::endl;
}
	

void ComponentMain::publishMissionStatus(config::SMME::pub::MissionStatus& msg)
{
	_roscomm->publishMissionStatus(msg);
}
	

void ComponentMain::publishMissionGlobalPath(config::SMME::pub::MissionGlobalPath& msg)
{
	_roscomm->publishMissionGlobalPath(msg);
}
	

void ComponentMain::publishIEDPosAtt(config::SMME::pub::IEDPosAtt& msg)
{
	_roscomm->publishIEDPosAtt(msg);
}
	

void ComponentMain::publishExecuteWorkSequenceCommand(config::SMME::pub::ExecuteWorkSequenceCommand& msg)
{
	_roscomm->publishExecuteWorkSequenceCommand(msg);
}
	