#ifndef MATH
#define MATH

#define PI_PREC 3.14159265358979323846264338327950288419
#include <iostream>
#include <cmath>
using namespace std;

long long getFact(int num)
{
    if (num == 0 || num == 1)
        return 1;

    long long answer = num;
    for (int i = num - 1; i > 0; i--)
    {
        answer = answer * i;
    }
    return answer;
}

double getPerm(int n, int r)
{
    return (getFact(n)/getFact(n-r));
}

double getComb(int n, int r)
{
    return (getPerm(n,r)/getFact(r));
}

double getLn(double num)
{
    return log(num);
}

double getLog(double num)
{
    return (log(num)/log(10.0));
}

double getLogBaseN(double num, double base)
{
    return (log(num)/log(base));
}

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

#endif