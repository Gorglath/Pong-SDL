#ifndef ID_PONG_TRIANGLE_H
#define ID_PONG_TRIANGLE_H
#define _USE_MATH_DEFINES
#include <math.h>
class Triangle
{
public:
	static double GetSinAngle(double hypotenuse, double opposite);
	static double CalculateDistance(double pointAX, double pointAY, double pointBX, double pointBY);
private:
	Triangle();
	~Triangle();
};
#endif // !ID_PONG_TRIANGLE_H
