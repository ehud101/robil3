
/*
 * ComponentMain.h
 *
 *  Created on: Thursday, 04. June 2015 09:56AM
 *      Author: autogenerated
 */
#ifndef COMPONENTMAIN_H_
#define COMPONENTMAIN_H_
#include "ros/ros.h"
#include <std_msgs/String.h>
#include <ParameterTypes.h>
#include <tf/tf.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include "../QinetiQ_IO/LLICtrl.h"
#include <boost/thread.hpp>
#include <pthread.h>

#include <ros/ros.h>

#include <iostream>     // std::cout
#include <sstream>

typedef enum { State_Off = 0, State_Init, State_Standby, State_Wait_Response, State_Ready } CS_STATE;
/***********************************
 * General Explanation
 *
 * There are two classes: ComponentMain and ComponentStates that work together:
 * --ComponentMain is the actual LLI component
 * --ComponentState is the module holding the State Machine: it defines the states of the component and how it changes
 * from one to another.
 * In this LLI component, we have two private members related to the state: _state and is_ready. The LLI component can
 * have is_ready = true only if the LLI_Ctrl state of the driver and the LLI_Ctrl state of the manipulator are equal to
 * lli_State_Ready. Setting the state of the driver and of the manipulator to ready can take time. The LLI component
 * would set these states to ready only when the initialization of the LLI_Ctrl has successfully completed.
 */
class ComponentMain {

public:
	ComponentMain(int argc,char** argv);
	virtual ~ComponentMain();
	//Thread Function for LLI Ctrl for QinetiQ
	void   lliCtrlLoop();
	static void * callPThread(void *pThis);
	static void *callHeartbeat(void *pThis);
	//This method is called when the state of the component is switching to State_Init
	void workerFunc();

	//Those methods are called each time the relevant topic has been caught
	void handleEffortsTh(const config::LLI::sub::EffortsTh& msg);
	void handleEffortsSt(const config::LLI::sub::EffortsSt& msg);
	void handleEffortsJn(const config::LLI::sub::EffortsJn& msg);


	void publishTransform(const tf::Transform& _tf,  std::string srcFrame, std::string distFrame);
	tf::StampedTransform getLastTrasform(std::string srcFrame, std::string distFrame);
	void publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report);
	void publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report);
	void publishConnectedToPlatform(std_msgs::Bool& msg);
	void heartbeat();

    void setReady();
    void setNotReady();
    void checkReady();
    void SetState(CS_STATE inState);
    bool StateNotReady();
    bool StateIsInit();
    CS_STATE GetComponentState();
    bool IsCLLIStillInInit();
    void releaseDriverAndManipulator();

private:
    bool _inited;
      ros::NodeHandle _nh;
      ros::Publisher _pub_diagnostic;
      boost::thread_group _maintains;
    	ros::Subscriber _sub_EffortsTh;
    	ros::Subscriber _sub_EffortsSt;
    	ros::Subscriber _sub_EffortsJn;
    	ros::Publisher _pub_connected_to_platform;


      bool init(int argc,char** argv);
	boost::thread* _driver_thread;
	CLLI_Ctrl *_clli;
	static ComponentMain *_this;
	pthread_t _mythread;
	bool is_ready;
	CS_STATE _state;
	pthread_t _myHeartbeatThread;
};
#endif /* COMPONENTMAIN_H_ */
