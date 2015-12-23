#include "ORManager.h"

ORManager::ORManager(ProcedureType pt){
	status_ =STOP_PROCEDURE;
	fiom_ = new FileIOManager();
	pt_ = pt;
};

//*************      SURGICAL OPERATORS   ***********************/
void ORManager::operatorNew(std::string op){
	operators_.push_back(op);
}

void ORManager::operatorDel(std::string op){
	std::vector<std::string>::iterator it;
	it = find(operators_.begin(), operators_.end(),op);
	operators_.erase(it);
}

std::string ORManager::operators(void){
	std::string rval = "";
	for(unsigned int i = 0; i< operators_.size(); ++i){
		rval += operators_.at(i);
		rval += "\n\r";
	}
	return rval;
}

void ORManager::statusIs(ORStatus s){
	status_ = s;
	switch(status_){
	case RUN_PROCEDURE:
		som_->statusIs(SurgicalOperatorManager::SURGERIZING);
		break;
	}
}