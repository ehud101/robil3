
/*
 * ComponentMain.h
 *
 *  Created on: Thursday, 06. February 2014 04:09PM
 *      Author: autogenerated
 */
#ifndef COMPONENTMAIN_H_
#define COMPONENTMAIN_H_
#include <std_msgs/String.h>
#include <ParameterTypes.h>
#include <tf/tf.h>
class RosComm;
class ComponentMain {
	RosComm* _roscomm;
public:
	ComponentMain(int argc,char** argv);
	virtual ~ComponentMain();
	void handleOdometry(const config::WSM::sub::Odometry& msg);
	void handleBladPosition(const config::WSM::sub::BladPosition& msg);
	void handleWSMCommand(const config::WSM::sub::WSMCommand& msg);
	void handleWSMData(const config::WSM::sub::WSMData& msg);
	void publishBladePositionCommand(config::WSM::pub::BladePositionCommand& msg);
	void publishWSMSpeed(config::WSM::pub::WSMSpeed& msg);
	void publishWSMExecutionState(config::WSM::pub::WSMExecutionState& msg);
	void publishWSMComponentState(config::WSM::pub::WSMComponentState& msg);
  void publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame);
  tf::StampedTransform getLastTrasform(std::string srcFrame, std::string distFrame);
};
#endif /* COMPONENTMAIN_H_ */
