
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
	void handleTrottleEffort(const config::PL_R2U::sub::TrottleEffort& msg);
	void handleSteeringEffort(const config::PL_R2U::sub::SteeringEffort& msg);
	void handleJointsEffort(const config::PL_R2U::sub::JointsEffort& msg);

};
#endif /* COMPONENTMAIN_H_ */
