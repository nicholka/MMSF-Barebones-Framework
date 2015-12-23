#ifndef ROBOTACTION_H
#define ROBOTACTION_H

#include <vector>
#include "PointXYZ.h"

typedef enum{NULL_ACTION,INITIALIZE,MOVE,FOLLOW_HID,WAIT_FOR_NEXT_COMMAND,HOLD_POSITION,TASK_COMPLETE} robotActionType;

class RobotAction{
public:
	enum ActionInstigator{AUTONOMOUS, HUMAN};
	RobotAction(){ 
		mActions_ = std::vector<RobotAction*>();
		instigator_ = AUTONOMOUS;
		mActionType_ = NULL_ACTION;
	};
	std::vector<RobotAction*> actions(void){return mActions_;};
	unsigned int numActions(void){return mActions_.size();};
	RobotAction* action(unsigned int i){return mActions_.at(i);};
	robotActionType type(void){return mActionType_;};
	PointXYZ point(void){return point_;}
	void actionInstigatorIs(ActionInstigator ai){instigator_ = ai;}
	ActionInstigator actionInstigator(void){return instigator_;}

protected:
	robotActionType mActionType_;
	std::vector<RobotAction*> mActions_;
	PointXYZ point_;
	ActionInstigator instigator_;
};


class MoveAction: public RobotAction{
public:
	MoveAction(PointXYZ pt) : RobotAction(){
		point_ = pt;
		mActionType_ = MOVE;
		mActions_.push_back(this);
	};
};

class HoldPositionAction: public RobotAction{
public:
	HoldPositionAction(PointXYZ pt): RobotAction(){
		point_ = pt;
		mActionType_ = HOLD_POSITION;
		mActions_.push_back(this);
	};
};

class FollowHIDAction: public RobotAction{
public:
	FollowHIDAction(PointXYZ pt):RobotAction(){
		point_ = pt;
		mActionType_ = FOLLOW_HID;
		mActions_.push_back(this);
	};
};

class WaitAction: public RobotAction{
public:
	WaitAction(): RobotAction(){
		mActionType_ = WAIT_FOR_NEXT_COMMAND;
	}
};

class InitializeAction: public RobotAction{
public:
	InitializeAction(): RobotAction(){
		mActionType_ = INITIALIZE;
	}
};

class TaskCompleteAction: public RobotAction{
public:
	TaskCompleteAction(): RobotAction(){
		mActionType_ = TASK_COMPLETE;
	}
};


#endif