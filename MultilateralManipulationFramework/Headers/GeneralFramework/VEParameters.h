#ifndef VEPARAMETERS_H
#define VEPARAMETERS_H

//Value-Type class, passed by value
class VEParameters{
public:
	VEParameters(){}
};

class PalpationVEParameters: public VEParameters{
public:
	PalpationVEParameters(void):VEParameters(){};
	PalpationVEParameters(double xMinP, double xMaxP, double yMinP, double yMaxP):xMin(xMinP),xMax(xMaxP),yMin(yMinP),yMax(yMaxP), VEParameters(){};
	double xMin;
	double xMax;
	double yMin;
	double yMax;
};

#endif