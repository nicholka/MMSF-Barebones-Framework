#ifndef ROBOT_H
#define ROBOT_H

#include "SurgicalProcedureManager.h"
#include "PointXYZ.h"
#include "HelperStructures.h"
#include "chai3d.h"
#include "Notifiee.h"
#include "FileIO.h"
#include "VE.h"
#include "RobotHardware.h"
#include "ORManager.h"
#include "SurgicalOperatorManager.h"

using namespace chai3d;
class BaseRobotHardware;

class Robot{
public:
	enum RobotStatus{INITIALIZING, EXECUTING_COMMAND, WAITING_FOR_COMMAND, SHUT_DOWN};
	enum RobotType{GENERIC_ROBOT,PALPATION_ROBOT,HID_ROBOT, VIRTUAL_HID_ROBOT};
	Robot();
	Robot(ORManager* ORman);
	class Notifiee;
	virtual void robotCommandNew(RobotAction* a);
	virtual RobotStatus status(){return status_;};
	virtual void statusIs(RobotStatus s){status_ = s;}
	virtual RobotAction* robotCommand(unsigned int index){return robotCommands_.at(index);}; 
	virtual void lastNotifieeIs(Robot::Notifiee* n){notifiees_.push_back(n);}
	virtual void robotCommandNewCallback(void){};
	RobotType robotType(void){return type_;}
	virtual PointXYZ position(void);
	virtual void positionIs(PointXYZ pos){};//Useful for notifiers/reactors
	virtual PointXYZ velocity(void);
	BaseRobotHardware* robotHardware(void){return robotHardware_;}
protected:
	virtual void applyForcesToFollowPath(PathPlannerStruct PathPlanner, PointXYZ cur_position,PointXYZ cur_velocity){}; 
	virtual bool pathTookTooLong();
	virtual bool reachedEndOfMove(PointXYZ cur_position, PointXYZ des_position){return false;}; 

	BaseRobotHardware* robotHardware_;
	bool threadInitialized_;
	std::vector<RobotAction*> robotCommands_;
	RobotStatus status_;
	PathPlannerStruct pathPlanner_;
	cThread* thread_;
	std::vector<Robot::Notifiee*> notifiees_;
	RobotType type_;
	PointXYZ position_;
	ORManager* orManager_;
};

/*****************   HID ROBOTS   ***********************/

class HIDRobot:public Robot{
public:
	HIDRobot(ORManager* ORMan):Robot(ORMan){}
	class Notifiee;
	PointXYZ position(void){return position_;}
	virtual void robotCommandNewCallback(void){};
	void buttonPressIs(bool b){buttonPress_ = b;}
	bool buttonPress(void){return buttonPress_;}

protected:
	Robot* slaveRobot_;
	bool buttonPress_;
};

/****  NOTIFIERS, NOTIFIEES, AND REACTORS ****************/

class Robot::Notifiee : public BaseNotifiee<Robot> {
public:
	Notifiee(Robot* robot) : BaseNotifiee<Robot>(robot){}
	virtual void onStatusIs() {}
	virtual void onPositionIs() {}
};

class HIDRobot::Notifiee: public Robot::Notifiee {
public:
	Notifiee(HIDRobot* robot): Robot::Notifiee(robot){}
	virtual void onPositionIs(){}
};

#endif 