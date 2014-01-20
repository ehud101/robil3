/*
 * ComponentMain.h
 *
 *  Created on: Jan 16, 2014
 *      Author: yuval
 */

#ifndef COMPONENTMAIN_H_
#define COMPONENTMAIN_H_

#include <robil2_msgs/String.h>

class RosComm;

class ComponentMain {
	RosComm *_roscomm;
public:
	ComponentMain(int argc,char** argv);
	virtual ~ComponentMain();

	void handleIEDDetectionEvent(robil2_msgs::String msg);
	void handleIEDLocation(robil2_msgs::String msg);

	void publishIEDDetectionEvent(robil2_msgs::String &msg);
	void publishIEDLocation(robil2_msgs::String &msg);
};

#endif /* COMPONENTMAIN_H_ */