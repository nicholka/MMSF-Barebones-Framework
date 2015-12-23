#ifndef SURGICALOPERATORMANAGER_H
#define SURGICALOPERATORMANAGER_H

#include "ORManager.h"
#include "Robot.h"
#include "chai3d.h"

class ORManager;
class Robot;
class HIDRobot;

class SurgicalOperatorManager{
	public:
		enum SurgicalOperatorStatus {SURGERIZING, NOT_SURGERIZING};
		class Notifiee;
		SurgicalOperatorManager(){}
		SurgicalOperatorManager(ORManager* ORMan, ProcedureType pt)
			:procedureType_(pt),mORManager_(ORMan){};
		SurgicalProcedureManager* surgicalProcedureManager(void){return spm_;};
		virtual void surgicalProcedureManagerIs(SurgicalProcedureManager* spm){spm_ = spm;}
		virtual void robotIs(Robot* robot){robot_ = robot;};
		virtual void hidRobotIs(HIDRobot* r){hidRobot_ = r;}
		virtual void statusIs(SurgicalOperatorStatus s){status_ = s;}
		Robot* robot(void){return robot_;}
		virtual void lastNotifieeIs(SurgicalOperatorManager::Notifiee* n){notifiees_.push_back(n);}
		virtual void keyPressIs(unsigned char key, int x, int y){}
	protected:
		ORManager* mORManager_;
		ProcedureType procedureType_;
		SurgicalProcedureManager* spm_;
		SurgicalOperatorStatus status_;
		Robot* robot_;
		HIDRobot* hidRobot_;
		std::vector<SurgicalOperatorManager::Notifiee*> notifiees_;
};

/***************** NOTIFIERS **************************/
class SurgicalOperatorManager::Notifiee : public BaseNotifiee<SurgicalOperatorManager> {
public:
	Notifiee(SurgicalOperatorManager* som) : BaseNotifiee<SurgicalOperatorManager>(som){}
};
#endif