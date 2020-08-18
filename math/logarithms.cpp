#include <cmath>

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