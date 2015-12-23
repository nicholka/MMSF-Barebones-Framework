#ifndef VE_H	
#define VE_H

#include "ORManager.h"
#include "chai3d.h"
#include "GL/glut.h"
#include "SurgicalProcedureManager.h"
#include <vector>
#include "VEParameters.h"
#include "SurgicalOperatorManager.h"

using namespace chai3d;
class ORManager;

PointXYZ GetOGLPos(int x, int y);

class VE{
public:
	VE(ORManager* ORMan):ORMan_(ORMan){};

	virtual void Initialize(VEParameters params){};
	virtual void Render(int displayW, int displayH){};
	virtual void mouseClick(int button, int state, int x, int y, int displayW, int displayH){};
	ORManager* orManager(void){return ORMan_;}
protected:
	ORManager* ORMan_;
	cWorld* mWorld_;
	cCamera* mCamera_;
	cPositionalLight* mLight_;
};

/***************** NOTIFIERS **************************/



#endif