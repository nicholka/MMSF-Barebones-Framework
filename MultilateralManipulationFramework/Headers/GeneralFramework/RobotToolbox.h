#ifndef ROBOT_TOOLBOX_H
#define ROBOT_TOOLBOX_H

#include <sys\timeb.h>
#include "PointXYZ.h"
#include "HelperStructures.h"
#include "SurgicalProcedureManager.h"
struct cubicSplineCoefficients;
namespace RobotToolbox{
	unsigned int diffBtwnTimes(timeb* LaterTime, timeb* EarlierTime);
	cubicSplineCoefficients generate_cubic_spline_coefficients(PointXYZ start_point, PointXYZ end_point, float time_duration);
	PathPlannerStruct createPathPlanner(PointXYZ CurDesiredPoint, PointXYZ NextDesiredPoint,float path_duration = 1000);
	PointXYZ currentReferencePoint(PathPlannerStruct pps);
};


#endif