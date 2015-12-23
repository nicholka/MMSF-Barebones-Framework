#include "RobotToolbox.h"
#include "Eigen"

//Module-level function delcarations
std::vector<double> ZAxisData(std::vector<std::vector<double>> forces);
std::vector<double> ZAxisData(std::vector<PointXYZ> pts);
double AverageElementInVector(std::vector<PointXYZ> vec, char element);
double FindMaximumEntry(std::vector<double> Data);
double FindMinimumEntry(std::vector<double> Data);


/*****************************************

DiffBtwn Times 
Takes two times of type timeb and calculates the difference between them

Args: LaterTime, EarlierTime, two of timeb type
returns: Unsigned int representing the difference between the two times in us.

*********************************************/

unsigned int RobotToolbox::diffBtwnTimes(timeb* LaterTime, timeb* EarlierTime){
	float Us;
	unsigned int LaterTimeSec;
	//if I need to carry the seconds
	if( LaterTime->millitm < EarlierTime->millitm){
		//printf("LaterTime ms is %d\n\r",LaterTime->millitm);
		//printf("EarlierTime ms is %d\n\r",EarlierTime->millitm);
		unsigned int adjustedUs = LaterTime->millitm + 1000;
		LaterTimeSec = LaterTime->time - 1;
		//printf("nanoS is %u\n\r",nanoS);
		Us = adjustedUs - EarlierTime->millitm;
	}
	else{
		//printf("LaterTime ms is %f\n\r",LaterTime->millitm);
		//printf("EarlierTime ms is %f\n\r",EarlierTime->millitm);
		LaterTimeSec = LaterTime->time;
		Us = LaterTime->millitm - EarlierTime->millitm;
	}
	return Us + 1000*(unsigned int)(LaterTimeSec - EarlierTime->time);
}

cubicSplineCoefficients RobotToolbox::generate_cubic_spline_coefficients(PointXYZ start_point, PointXYZ end_point, float time_duration){
	cubicSplineCoefficients rval;
	PointXYZ velocity_end(0,0,0);

	rval.a0x = start_point.x;
	rval.a1x = velocity_end.x;
	rval.a2x = 3.0/pow(time_duration,2) * (end_point.x - start_point.x- velocity_end.x*time_duration );
	rval.a3x = -2.0/pow(time_duration,3) * (end_point.x - start_point.x- velocity_end.x*time_duration );

	rval.a0y = start_point.y;
	rval.a1y = velocity_end.y;
	rval.a2y = 3.0/pow(time_duration,2) * (end_point.y - start_point.y- velocity_end.y*time_duration );
	rval.a3y = -2.0/pow(time_duration,3) * (end_point.y - start_point.y- velocity_end.y*time_duration );

	rval.a0z = start_point.z;
	rval.a1z = velocity_end.z;
	rval.a2z = 3.0/pow(time_duration,2) * (end_point.z - start_point.z - velocity_end.z*time_duration );
	rval.a3z = -2.0/pow(time_duration,3) * (end_point.z - start_point.z- velocity_end.z*time_duration );

	//Special Case, time_duration = 0;
	if(time_duration == 0){
		rval.a2x = 0;
		rval.a3x = 0;
		rval.a2y = 0;
		rval.a3y = 0;
		rval.a2z = 0;
		rval.a3z = 0;
	}
	return rval;
}/***********************************************
UpdatePathPlanningState

Description: Called to update the path-planning coefficients when a new path is mapped

Aguments: The current time and position to map to
Returns: Nothing, the internal variable "PathPlanner" is updated
**********************************************/
PathPlannerStruct RobotToolbox::createPathPlanner(PointXYZ CurDesiredPoint, PointXYZ NextDesiredPoint, float path_duration) {
	//float path_duration = 1000;
	//grab current time
	timeb currentTime;
	//Grab the current time
	ftime(&currentTime);
	//float t_diff = DiffBtwnTimes(&CurrentTime,&t_begin);

	//Generate the path-planned reference point, which is different from the desired point, as we're path planning up in here.
	//  It's also differnt from the current point (consider the case where the Phantom is applying force to try to catch the
	//  reference point; in this case the new path should still include this force (so the initial reference point shouldn't change)
	//  across different iterations of this function
	//float ref_x = PathPlanner.a0x + t_diff*PathPlanner.a1x + pow(t_diff,2)*PathPlanner.a2x +  pow(t_diff,3)*PathPlanner.a3x;
	//float ref_y = PathPlanner.a0y + t_diff*PathPlanner.a1y + pow(t_diff,2)*PathPlanner.a2y +  pow(t_diff,3)*PathPlanner.a3y;
	//float ref_z = PathPlanner.a0z + t_diff*PathPlanner.a1z + pow(t_diff,2)*PathPlanner.a2z +  pow(t_diff,3)*PathPlanner.a3z;
	//PointXYZ CurrentDesiredPoint(ref_x,ref_y,ref_z);

	//Update the cubic spline coefficients
	//Note the 5000 is for 5000 ms
	PathPlannerStruct PP;
	cubicSplineCoefficients PathPlanningCoefficients = RobotToolbox::generate_cubic_spline_coefficients(CurDesiredPoint,NextDesiredPoint,path_duration);
	PP.cubicSplineCoefficients = PathPlanningCoefficients;

	//Update the other prameters in the structure
	PP.t_begin = currentTime;
	PP.t_duration = path_duration;
	PP.desired_point = NextDesiredPoint;
	PP.starting_point = CurDesiredPoint;
	//printf("Setting the following desired point\n\r");
	//NextDesiredPoint.Print();
	return PP;
}

PointXYZ RobotToolbox::currentReferencePoint(PathPlannerStruct PathPlanner){
	timeb CurrentTime;
	//Grab the current time
	ftime(&CurrentTime);
	double t_diff = RobotToolbox::diffBtwnTimes(&CurrentTime,&PathPlanner.t_begin);
	//Generate the path-planned position
	double ref_x = PathPlanner.cubicSplineCoefficients.a0x + t_diff*PathPlanner.cubicSplineCoefficients.a1x + pow(t_diff,2)*PathPlanner.cubicSplineCoefficients.a2x +  pow(t_diff,3)*PathPlanner.cubicSplineCoefficients.a3x;
	double ref_y = PathPlanner.cubicSplineCoefficients.a0y + t_diff*PathPlanner.cubicSplineCoefficients.a1y + pow(t_diff,2)*PathPlanner.cubicSplineCoefficients.a2y +  pow(t_diff,3)*PathPlanner.cubicSplineCoefficients.a3y;
	double ref_z = PathPlanner.cubicSplineCoefficients.a0z + t_diff*PathPlanner.cubicSplineCoefficients.a1z + pow(t_diff,2)*PathPlanner.cubicSplineCoefficients.a2z +  pow(t_diff,3)*PathPlanner.cubicSplineCoefficients.a3z;
	return PointXYZ(ref_x,ref_y,ref_z);
}

/************* Module-level FUNCTIONS   ************/

double AverageElementInVector(std::vector<PointXYZ> vec, char element){
	double runningSum = 0;
	switch(element){
	case 'x':
		for(unsigned int i=0; i< vec.size(); ++i){
			runningSum += vec.at(i).x;
		}
		break;
	case 'y':
		for(unsigned int i=0; i< vec.size(); ++i){
			runningSum += vec.at(i).y;
		}
		break;
	case 'z':
		for(unsigned int i=0; i< vec.size(); ++i){
			runningSum += vec.at(i).z;
		}
		break;
	}
	return runningSum/vec.size();
}

std::vector<double> ZAxisData(std::vector<std::vector<double>> forces){
	std::vector<double> rval;
	for(unsigned int i=0; i<forces.size(); ++i){
		rval.push_back(forces.at(i)[2]);
	}
	return rval;
}

std::vector<double> ZAxisData(std::vector<PointXYZ> pts){
	std::vector<double> rval;
	for(unsigned int i=0; i<pts.size(); ++i){
		rval.push_back(pts.at(i).z);
	}
	return rval;
}

double FindMaximumEntry(std::vector<double> Data){
	double MaxEntry = -1000000.0;
	for(unsigned int Index = 0; Index < Data.size(); ++Index)
	{
		if(Data[Index] > MaxEntry) MaxEntry = Data[Index];
	}
	return MaxEntry;
}

double FindMinimumEntry(std::vector<double> Data){
	double MinimumEntry = 1000000.0;
	for(unsigned int Index = 0; Index < Data.size(); ++Index)
	{
		if(Data[Index] < MinimumEntry) MinimumEntry = Data[Index];
	}
	return MinimumEntry;
}