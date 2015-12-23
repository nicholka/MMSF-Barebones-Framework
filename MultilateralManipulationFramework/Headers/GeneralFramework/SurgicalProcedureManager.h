#ifndef SURGICALPROCEDUREMANAGER_H
#define SURGICALPROCEDUREMANAGER_H

#include "RobotAction.h"
#include "HelperStructures.h"
#include <iostream>
#include "PointXYZ.h"
#include "VEParameters.h"

class SurgicalProcedureManager{
public:
	SurgicalProcedureManager(){};
	virtual RobotAction* actionDequeue();
	virtual void actionEnqueue(RobotAction* action, QueueInsertPosition pos);
	unsigned int numActions(void){return actions_.size();}
	RobotAction* front(void){return actions_.at(0);}
	void pop(void){actions_.erase(actions_.begin());}
	RobotAction* actionAtPosition(unsigned int i){
		if(i > numActions()) throw;
		return actions_[i];
	}
	void deleteActionAtPosition(unsigned int i){
		actions_.erase(actions_.begin() + i);
	}

protected:
	std::vector<RobotAction *> actions_;
};
#endif