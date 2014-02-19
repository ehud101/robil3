
/*
 * ComponentMain.h
 *
 *  Created on: Wednesday, 19. February 2014 02:59PM
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
	void handleCustomIED(const config::IEDSIM::sub::CustomIED& msg);
	void handleLocalPath(const config::IEDSIM::sub::LocalPath& msg);
	void publishIEDLocation(config::IEDSIM::pub::IEDLocation& msg);
	void publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame);
	tf::StampedTransform getLastTrasform(std::string srcFrame, std::string distFrame);
	void publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report);
	void publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report);
};
#endif /* COMPONENTMAIN_H_ */
