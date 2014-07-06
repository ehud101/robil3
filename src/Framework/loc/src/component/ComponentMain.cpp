
/*
 * ComponentMain.cpp
 *
 *  Created on: Thursday, 27. February 2014 12:29PM
 *      Author: autogenerated
 */
#include "ComponentMain.h"
#include "boost/bind.hpp"
#include "../roscomm/RosComm.h"
#include "userHeader.h"

ComponentMain *ComponentMain::_this;

ComponentMain::ComponentMain(int argc,char** argv)
{
	//void (ComponentMain::)();;
	_roscomm = new RosComm(this,argc, argv);
	ComponentMain::_this = this;
	_estimation_thread = new boost::thread(&ComponentMain::performEstimation);
}
ComponentMain::~ComponentMain() {
	if(_roscomm) delete _roscomm; _roscomm=0;
	_estimation_thread->interrupt();
	delete _estimation_thread;
}

void ComponentMain::performEstimation()
{
	config::LOC::pub::Location msg1;
	config::LOC::pub::PerVelocity msg2;
	for(;;)
	{
		try
		{
			/* Perform the estimatior process*/
			if(_added_noise)
			{
				_this->_estimator.estimator();
				msg1 = _this->_estimator.getEstimatedPose();
				msg2 = _this->_estimator.getEstimatedSpeed();
			}
			else
			{
				_this->_observer.estimator();
				msg1 = _this->_observer.getEstimatedPose();
				msg2 = _this->_observer.getEstimatedSpeed();
			}
			_this->publishLocation(msg1);
			_this->publishPerVelocity(msg2);

			boost::this_thread::sleep(boost::posix_time::milliseconds(100));
		}
		catch(boost::thread_interrupted&)
		{
			std::cout << "Thread has stopped. No estimation is published to LOC!!!!" << std::endl;
			return;
		}
	}
}
void ComponentMain::handlePositionUpdate(const config::LOC::sub::PositionUpdate& msg)
{
	//std::cout<< "LOC say:" << msg << std::endl;
}
	

void ComponentMain::handleGPS(const config::LOC::sub::GPS& msg)
{
	config::LOC::pub::Location msg1;
	config::LOC::pub::PerVelocity msg2;
	if(_added_noise)
		_estimator.setGPSMeasurement(msg);
	else
		_observer.setGPSMeasurement(msg);
}
	

void ComponentMain::handleINS(const config::LOC::sub::INS& msg)
{
	if(_added_noise)
		_estimator.setIMUMeasurement(msg);
	else
		_observer.setIMUMeasurement(msg);
}
	

void ComponentMain::handleVOOdometry(const config::LOC::sub::VOOdometry& msg)
{
	//std::cout<< "LOC say:" << msg << std::endl;
}

void ComponentMain::handleGpsSpeed(const config::LOC::sub::PerGpsSpeed& msg)
{
	if(_added_noise)
		_estimator.setGPSSpeedMeasurement(msg);
	else
		_observer.setGPSSpeedMeasurement(msg);
}	

void ComponentMain::publishLocation(config::LOC::pub::Location& msg)
{
	_roscomm->publishLocation(msg);
}
	

void ComponentMain::publishPerVelocity(config::LOC::pub::PerVelocity& msg)
{
	_roscomm->publishPerVelocity(msg);
}
	
void ComponentMain::publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame){
	_roscomm->publishTransform(_tf, srcFrame, distFrame);
}
tf::StampedTransform ComponentMain::getLastTrasform(std::string srcFrame, std::string distFrame){
	return _roscomm->getLastTrasform(srcFrame, distFrame);
}
void ComponentMain::publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report){
	_roscomm->publishDiagnostic(_report);
}
void ComponentMain::publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report){
	_roscomm->publishDiagnostic(header, _report);
}
