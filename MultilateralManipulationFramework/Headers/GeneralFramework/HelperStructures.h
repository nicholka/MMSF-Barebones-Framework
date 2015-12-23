#ifndef HELPERSTRUCTURES_H
#define HELPERSTRUCTURES_H

#include "PointXYZ.h"
#include <sys\timeb.h>

typedef enum {QUEUE_BEGINNING_INSERT,QUEUE_SECOND_ENTRY_INSERT,QUEUE_END_INSERT} QueueInsertPosition;

typedef enum {UNDEFINED_PROCEDURE} ProcedureType;

struct cubicSplineCoefficients{
		double a0x;
		double a1x;
		double a2x;
		double a3x;
		double a0y;
		double a1y;
		double a2y;
		double a3y;
		double a0z;
		double a1z;
		double a2z;
		double a3z;
	};

struct PathPlannerStruct{
	cubicSplineCoefficients cubicSplineCoefficients;
	float t_duration;
	timeb t_begin;
	PointXYZ desired_point;
	PointXYZ starting_point;
};

#endif