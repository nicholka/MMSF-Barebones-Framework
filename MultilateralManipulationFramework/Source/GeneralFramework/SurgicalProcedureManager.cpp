#include "SurgicalProcedureManager.h"
#include "Robot.h"

RobotAction* SurgicalProcedureManager::actionDequeue(void){
	RobotAction* rval = actions_.front();
	actions_.erase(actions_.begin());
	return rval;
}

void SurgicalProcedureManager::actionEnqueue(RobotAction * action, QueueInsertPosition pos){
	switch(pos){
	case QUEUE_BEGINNING_INSERT:
		actions_.insert(actions_.begin(),action);
		break;
	case QUEUE_SECOND_ENTRY_INSERT:
	{
		unsigned int offset;
		for(offset = 1; offset < actions_.size(); ++offset){
			RobotAction* act = actions_.at(offset);
			if(act->actionInstigator() == RobotAction::AUTONOMOUS) break;
		}
		actions_.insert(actions_.begin() + offset ,action);
		break;
	};
	case QUEUE_END_INSERT:
		actions_.push_back(action);
		break;
	default:
		std::cout << "Enquing an action in invalid place" << std::endl;
		break;
	};//endswitch pos
}