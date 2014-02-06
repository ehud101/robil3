
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
	void handleVOOdometry(const config::LOC::sub::VOOdometry& msg);
	void handleGPS(const config::LOC::sub::GPS& msg);
	void handleINS(const config::LOC::sub::INS& msg);
	void handlePositionUpdate(const config::LOC::sub::PositionUpdate& msg);
	void handleLOCCommand(const config::LOC::sub::LOCCommand& msg);
	void publishOdometry(config::LOC::pub::Odometry& msg);
	void publishLOCState(config::LOC::pub::LOCState& msg);
	void publishLOCComponentState(config::LOC::pub::LOCComponentState& msg);
  void publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame);
  tf::StampedTransform getLastTrasform(std::string srcFrame, std::string distFrame);
};
#endif /* COMPONENTMAIN_H_ */
