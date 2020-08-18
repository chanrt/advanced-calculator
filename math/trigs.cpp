#include <cmath>

#define PI_PREC 3.14159265358979323846264338327950288419

double getRadians(double degrees)
{
    return (PI_PREC * degrees / 180.0);
}

double getDegrees(double radians)
{
    return (180.0 * radians / PI_PREC);
}

double getSin(double num, bool degree_mode)
{
    if (degree_mode)
        return sin(getRadians(num));
    else
        return sin(num);
}

double getCos(double num, bool degree_mode)
{
    if (degree_mode)
        return cos(getRadians(num));
    else
        return cos(num);
}

double getTan(double num, bool degree_mode)
{
    if (degree_mode)
        return tan(getRadians(num));
    else
        return tan(num);
}

double getArcSin(double num, bool degree_mode)
{
    if(degree_mode)
        return getDegrees(asin(num));
    else
        return asin(num);
}

double getArcCos(double num, bool degree_mode)
{
    if(degree_mode)
        return getDegrees(acos(num));
    else
        return asin(num);
}

double getArcTan(double num, bool degree_mode)
{
    if(degree_mode)
        return getDegrees(atan(num));
    else
        return asin(num);
}