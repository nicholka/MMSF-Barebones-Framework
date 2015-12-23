#include "PointXYZ.h"
//#include "GeneratePathPoints.h"
#include <vector>

PointXYZ::PointXYZ(void)
{
	x = 0;
	y = 0;
	z = 0;
}

PointXYZ::PointXYZ(chai3d::cVector3d pnt){
	x = pnt.x();
	y = pnt.y();
	z = pnt.z();
}

PointXYZ::PointXYZ(double initX, double initY, double initZ)
{
	x = initX;
	y = initY;
	z = initZ;
}

PointXYZ::PointXYZ(std::vector<double> Pt)
{
	x = Pt[0];
	y = 0;
	z = Pt[1];
}

double PointXYZ::norm(void){
	return sqrt(x*x +y*y +z*z);
}

void PointXYZ::Print(void){
	printf("%f %f %f \n\r",x,y,z);
	return;
}

void PointXYZ::clear(void){
	x = 0;
	y = 0;
	z = 0;
	return;
}