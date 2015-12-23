#include "RobotHardware.h"

RobotHardwareManager::RobotHardwareManager(void){
	// create a haptic device handler
	handler_ = new cHapticDeviceHandler();
}

cGenericHapticDevice*  RobotHardwareManager::nextChaiDevice(void){
	static unsigned int index = 1;
	cGenericHapticDevice* robo;
	handler_->getDevice(robo,index);
	index--;
	return robo;
}

Chai3dRobot::Chai3dRobot(ORManager* ORMan): BaseRobotHardware(){
	RobotHardwareManager* rhm = ORMan->robotHardwareManager();
	hapticDevice_ = rhm->nextChaiDevice();
	hapticDevice_->open();
	hapticDevice_->calibrate();

	// retrieve information about the current haptic device
	cHapticDeviceInfo info = hapticDevice_->getSpecifications();
}

PointXYZ Chai3dRobot::position(void){
	//Initialize robot position
	cVector3d cCurPoint;
	hapticDevice_->getPosition(cCurPoint);
	PointXYZ pt(cCurPoint);
	pt = 1000 * pt;
	return pt;
}

PointXYZ Chai3dRobot::velocity(void){
	//Initialize robot position
	cVector3d cCurPoint;
	hapticDevice_->getLinearVelocity(cCurPoint);
	PointXYZ pt(cCurPoint);
	pt = 1000 * pt;
	return pt;
}

bool Chai3dRobot::switchAt(unsigned int index){
	bool button = false;
	hapticDevice_->getUserSwitch(index, button);
	return button;
}

bool Chai3dRobot::clutch(void){
		bool button = false;
		hapticDevice_->getUserSwitch(0, button);
		return button;
	}