#include "Triangle.h"

Triangle::Triangle()
{

}
Triangle::~Triangle()
{

}
double Triangle::CalculateDistance(double pointAX, double pointAY, double pointBX, double pointBY)
{
	return sqrt(pow(pointBX - pointAX, 2) + pow(pointBY - pointAY, 2));
}
double Triangle::GetSinAngle(double hypotenuse, double opposite)
{
	double sinX = opposite / hypotenuse;
	double sinxInRad = asin(sinX);
	return sinxInRad * 180.0 / M_PI;
}