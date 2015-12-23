#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include <queue>
#include "PointXYZ.h"
#include "SurgicalProcedureManager.h"
#include "ORManager.h"
#include "Robot.h"
#include "chai3d.h"
#include "VE.h"
#include <iostream>
#include <fstream>

using namespace std;

class ORManager;
class PalpationRobotFileIOReactor;
class FileIOBoundaryPointsReactor;

//Must not be a member function, as then the callback would have to note which object is
//  associated with it ---> compiler error
void FileIOCallback(void);
void FileIOThreadCallback(void);
class FileIOManager;

class FileIOManager{
public:
	enum IOStatus{NO_IO,YES_IO};
	FileIOManager(){status_ = NO_IO;}
	FileIOManager(ORManager* ORMan){
		ORMan_ = ORMan;
		fpRawData = ofstream("C:/Users/Charm_Stars/Documents/MultilateralManipulationFramework/Output/rawData.DAT");
		thread_ = new chai3d::cThread();
		if(fpRawData != NULL) status_ = YES_IO;
		else status_ = NO_IO;
	}
	virtual void threadCallback(){};
	IOStatus status(void){return status_;}
	virtual void writeAllDataToFile(void){};
protected:
	chai3d::cThread* thread_;
	ORManager* ORMan_;
	ofstream fpRawData;
	IOStatus status_;
};
#endif