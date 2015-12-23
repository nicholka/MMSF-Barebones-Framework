#include "ORManager.h"
#include "SurgicalOperatorManager.h"
#include "SurgicalProcedureManager.h"
#include "chai3d.h"
#include "VE.h"
#include "FileIO.h"
#include "RobotHardware.h"
#include "HelperStructures.h"
#include "Robot.h"

#include <string>

#pragma warning(disable:4996)

using namespace chai3d;

HIDRobot* hidRobot = NULL;
int windowHandle0;
int displayW = 0;
int displayH = 0;

//Forward Declarations of functions in main
void InitGlut(void);

void keyPressed(unsigned char key, int x, int y){
	
}

void mouseClicks(int button, int state, int x, int y) {
	//PointXYZ pos = GetOGLPos(x,y);
	//pos.Print();
}

void updateGraphics(void)
{
	//ve_->Render(displayW, displayH);
    glutSwapBuffers();
}

void resizeWindow(int w, int h)
{
    // update the size of the viewport
    displayW = w;
    displayH = h;
    glViewport(0, 0, displayW, displayH);
}

void graphicsTimer(int data)
{
	glutPostRedisplay();
    glutSetWindow(windowHandle0);
    glutTimerFunc(30, graphicsTimer, 0);
}

void graphicsCallback()
{
	InitGlut();
}

void InitGlut(void){
	int argc;
	char* dummy_args[] = {"arg1", "arg2", NULL};

	glutInit(&argc, dummy_args);

    // retrieve the resolution of the computer display and estimate the position
    // of the GLUT window so that it is located at the center of the screen
    //int screenW = glutGet(GLUT_SCREEN_WIDTH);
    //int screenH = glutGet(GLUT_SCREEN_HEIGHT);
    int screenW = 1920;
    int screenH = 1080;
    int windowW = 0.6 * screenH;
    int windowH = windowW;
	int windowPosX = 2*windowW;
	int windowPosY = 0;
    //int windowPosX = (screenW - windowH) / 2;
    //int windowPosY = (screenH - windowW) / 2;

    // initialize the OpenGL GLUT window
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowPosition(windowPosX, windowPosY);
    glutInitWindowSize(windowW, windowH);
	windowHandle0 = glutCreateWindow(dummy_args[0]);
    glutSetWindowTitle("Tumor Segmentation");
	glutDisplayFunc(updateGraphics);
	glutReshapeFunc(resizeWindow);
	glutTimerFunc(30, graphicsTimer, 0);

	// initialize GLEW library
    glewInit();

	glutMouseFunc(mouseClicks);
	glutKeyboardFunc(keyPressed);
	
	// start loop
    glutMainLoop();
}

void main(){
	//Initializations...
	ProcedureType mProcedure = UNDEFINED_PROCEDURE;
	ORManager* orManager = ORManager::getInstance(mProcedure);
	std::string surgicalOperator = "Kirk Nichols";
	orManager->operatorNew(surgicalOperator);
}

//KIRK FIX LOCATION OF PHANTOM .dll, TEMPORARY FIX WAS TO PUT IT IN THE SYS32 FOLDER
