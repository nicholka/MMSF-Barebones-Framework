#include "Robot.h"
#include <sys\timeb.h>
#include "RobotToolbox.h"

#pragma warning(disable:4244)
static Robot* slaveRobot; //Used for thread callback
static Robot* hidRobot;


void SlaveRobotThreadCallback(void){
	printf("Slave robot thread starting\n\r");
	slaveRobot->robotCommandNewCallback();
}

void HIDRobotThreadCallback(void){
	hidRobot->robotCommandNewCallback();
}

void Robot::robotCommandNew(RobotAction* cmd){
	robotCommands_.push_back(cmd);
	//robotCommandNewCallback(); //KAN DEBUGGING
	if(robotCommands_.size() == 1 && threadInitialized_ == false){
		//Start Robo Thread
		printf("ROBO THREAD STARTING\n\r");
		if((type_ == HID_ROBOT) || (type_ == VIRTUAL_HID_ROBOT))
			thread_->start(HIDRobotThreadCallback,CTHREAD_PRIORITY_HAPTICS);
		else
			thread_->start(SlaveRobotThreadCallback,CTHREAD_PRIORITY_HAPTICS);
		threadInitialized_ = true;
	}
}

Robot::Robot(){
	status_ = INITIALIZING;
	type_ = GENERIC_ROBOT;
	thread_ = new cThread();
	threadInitialized_ = false;
	robotHardware_ = new BaseRobotHardware();
};

Robot::Robot(ORManager* ORMan){
	status_ = INITIALIZING;
	type_ = GENERIC_ROBOT;
	orManager_ = ORMan;

	thread_ = new cThread();
	threadInitialized_ = false;

	robotHardware_ = new BaseRobotHardware();
};

PointXYZ Robot::position(void){
	position_ = robotHardware_->position();
	return position_;
}

PointXYZ Robot::velocity(void){
	return robotHardware_->velocity();
}

/***********************************************
PathTookTooLong

Description: Returns a boolean representing whether or not the path currently planned 
                should be re-calculated

Aguments: The current time 
Returns: True if the path should be re-evaluated
**********************************************/
bool Robot::pathTookTooLong(){
	timeb CurrentTime;
	ftime(&CurrentTime);
	float t_diff = RobotToolbox::diffBtwnTimes(&CurrentTime,&pathPlanner_.t_begin);
	if(t_diff > pathPlanner_.t_duration){
		//printf("Path took too long!!!\n\r");
		return true;
	}
	return false;
}