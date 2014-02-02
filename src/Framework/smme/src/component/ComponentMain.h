
/*
 * ComponentMain.h
 *
 *  Created on: Sunday, 02. February 2014 10:15AM
 *      Author: autogenerated
 */
#ifndef COMPONENTMAIN_H_
#define COMPONENTMAIN_H_
#include <std_msgs/String.h>
#include <ParameterTypes.h>
class RosComm;
class ComponentMain {
	RosComm* _roscomm;
public:
	ComponentMain(int argc,char** argv);
	virtual ~ComponentMain();
	void handleIEDDetectionEvent(const config::SMME::sub::IEDDetectionEvent& msg);
	void handleIEDLocation(const config::SMME::sub::IEDLocation& msg);
	void handleMissionPlan(const config::SMME::sub::MissionPlan& msg);
	void handleStatusData(const config::SMME::sub::StatusData& msg);
	void publishMissionStatus(config::SMME::pub::MissionStatus& msg);
	void publishMissionGlobalPath(config::SMME::pub::MissionGlobalPath& msg);
	void publishIEDPosAtt(config::SMME::pub::IEDPosAtt& msg);
	void publishExecuteWorkSequenceCommand(config::SMME::pub::ExecuteWorkSequenceCommand& msg);
};
#endif /* COMPONENTMAIN_H_ */
