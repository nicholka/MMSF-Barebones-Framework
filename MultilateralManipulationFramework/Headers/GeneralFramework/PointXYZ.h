#ifndef PointXYZh
#define PointXYZh

#include <math.h>
#include <stdio.h>
#include <vector>
#include "chai3d.h"
class PointXYZ
{
	public:
		PointXYZ(void);
		PointXYZ(chai3d::cVector3d pnt);
		PointXYZ(double initX, double initY, double initZ);
		PointXYZ(std::vector<double> Pt);
		double norm();
		void Print(void);
		double& operator[](const unsigned int index);
		PointXYZ& operator+=(const PointXYZ& rhs){
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}
		PointXYZ& operator-=(const PointXYZ& rhs){
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}
		double dot(const PointXYZ& r){
			return x*r.x + y * r.y + z * r.z;
		}
		//bool IsProperyInitialized(void);
		void PointXYZ::clear(void);
		double x;
		double y;
		double z;
};

inline PointXYZ operator+(PointXYZ lhs, const PointXYZ& rhs){
	lhs += rhs;
	return lhs;
}

inline PointXYZ operator-(PointXYZ lhs, const PointXYZ& rhs){
	lhs -= rhs;
	return lhs;
}

inline PointXYZ operator*(double k, PointXYZ& rhs){
	rhs.x *= k;
	rhs.y *= k;
	rhs.z *= k;
	return rhs;
}

inline bool operator== (const PointXYZ& lhs, const PointXYZ& rhs){
	return ( (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z));
}

inline bool operator!= (const PointXYZ& lhs, const PointXYZ& rhs){
	return ( (lhs.x != rhs.x) || (lhs.y != rhs.y) || (lhs.z != rhs.z));
}
#endif

