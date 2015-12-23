#ifndef ORMANAGER_H
#define ORMANAGER_H

#include <string>
#include <vector>
#include <algorithm> //for find
#include "SurgicalOperatorManager.h"
#include "Robot.h"
#include "FileIO.h"
#include "RobotHardware.h"
#include "HelperStructures.h"

class Robot;
class SurgicalOperatorManager;
class FileIOManager;
class RobotHardwareManager;
class VE;
//High-level class of the entire procedure, including information about the operator and other settings
class ORManager{
public:
	enum ORStatus {RUN_PROCEDURE, STOP_PROCEDURE};
	static ORManager* getInstance(ProcedureType pt){
		static ORManager* instance_ = NULL;
		if(instance_ == NULL) instance_ = new ORManager(pt);
		return instance_;
	}
	void operatorNew(std::string op);
	void operatorDel(std::string op);
	std::string operators();	
	void statusIs(ORStatus s);
	void robotIs(Robot* r){robot_ = r;}
	Robot* robot(void){return robot_;}
	void hidRobotIs(Robot* r){hidRobot_ = r;}
	Robot* hidRobot(void){return hidRobot_;}
	void FileIOManagerIs(FileIOManager* fiom){fiom_ = fiom;}
	FileIOManager* fileIOManager(void){return fiom_;}
	RobotHardwareManager* robotHardwareManager(void){return robotHardwareManager_;}
	void robotHardwareManagerIs(RobotHardwareManager* rhm){robotHardwareManager_ = rhm;}

	void surgicalOperatorManagerIs(SurgicalOperatorManager* som){som_ = som;};
	SurgicalOperatorManager* surgicalOperationManager(void){return som_;};

	void surgicalProcedureManagerIs(SurgicalProcedureManager* spm){spm_ = spm;}
	SurgicalProcedureManager* surgicalProcedureManager(void){return spm_;}

	void procedureTypeIs(ProcedureType pt){pt_ = pt;};
	ProcedureType procedureType(void){return pt_;}

	void virtualEnvironmentIs(VE* ve){ve_ = ve;}
	VE* virtualEnvironment(void){return ve_;}

private:
	ORManager(ProcedureType pt);
	std::vector<std::string> operators_;
	SurgicalOperatorManager* som_;
	SurgicalProcedureManager* spm_;
	ORStatus status_;
	Robot* robot_;
	Robot* hidRobot_;
	FileIOManager* fiom_;
	RobotHardwareManager* robotHardwareManager_;
	ProcedureType pt_;
	VE* ve_;
};



#endif