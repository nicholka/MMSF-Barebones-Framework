#include "FileIO.h"

char palpationPath[500]="C:/Users/Charm_Stars/Documents/MultilateralManipulationFramework/Output/PalpatedPoints.DAT";
static FileIOManager* fiom;
char boundaryPointsPath[500]="C:/Users/Charm_Stars/Documents/MultilateralManipulationFramework/Output/BoundaryPoints.DAT";
void FileIOThreadCallback(void){
	fiom->threadCallback();
}