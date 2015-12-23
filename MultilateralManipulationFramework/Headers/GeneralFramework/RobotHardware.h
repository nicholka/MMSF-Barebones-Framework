#ifndef ROBOT_HARDWARE_H
#define ROBOT_HARDWARE_H

#include "PointXYZ.h"
#include "chai3d.h"
#include "ORManager.h"

using namespace chai3d;
class ORManager;

class RobotHardwareManager{
public:
	RobotHardwareManager::RobotHardwareManager(void);
	cGenericHapticDevice*  RobotHardwareManager::nextChaiDevice(void);

private:
	cHapticDeviceHandler* handler_;
};

class BaseRobotHardware{
public:
	BaseRobotHardware(){};
	virtual PointXYZ position(void){return PointXYZ();}
	virtual PointXYZ velocity(void){return PointXYZ();}
	virtual void forcesAre(PointXYZ f){};
	virtual PointXYZ lastForceCommand(void){return PointXYZ();}
	virtual bool clutch(void){return false;}
	virtual bool switchAt(unsigned int index){return false;}
protected:
	PointXYZ lastForceCommand_;
};

class Chai3dRobot:public BaseRobotHardware{
public:
	Chai3dRobot(ORManager* ORMan);
	~Chai3dRobot(){hapticDevice_->close();}
	cHapticDeviceHandler* hapticDeviceHandler(void){return handler_;}
	PointXYZ position(void);
	PointXYZ velocity(void);
	bool clutch(void);
	void forcesAre(PointXYZ command){
		lastForceCommand_ = command;
		hapticDevice_->setForce(cVector3d(command.x,command.y,command.z));
	};
	PointXYZ lastForceCommand(void){return lastForceCommand_;}
	bool switchAt(unsigned int index);

protected:
	cGenericHapticDevice* hapticDevice_;
	cHapticDeviceHandler* handler_;
};

#endif