#ifndef CONSTANTS
#define CONSTANTS

#define NUM_CONSTANTS 31

#include <iostream>
#include <vector>
#include "flags.cpp"

double getConst(int index)
{
    switch (index)
    {
    // math constants 3
    case PI:
        return 3.1415926535;
    case EU:
        return 2.7182818284;
    case GR:
        return 1.6180339887;

    // universal constants 4
    case SOL:
        return 299792458;
    case H:
        return 6.62607004e-34;
    case HC:
        return 1.054571726e-34;
    case G:
        return 6.67430e-11;

    // atomic and nuclear constants 7
    case EM:
        return 9.1093837015e-31;
    case PM:
        return 1.67262e-27;
    case NM:
        return 1.67493e-36;
    case BR:
        return 5.2917721092e-11;
    case FS:
        return 7.2973525698e-3;
    case HE:
        return 4.35977434e-18;
    case R:
        return 10973731.568;

    // electromagnetic constants 8
    case M_PER:
        return 1.256637061e-6;
    case E_PER:
        return 8.854187817e-12;
    case Z:
        return 376.730313461;
    case KC:
        return 8.987551787e9;
    case EC:
        return 1.602176565e-19;
    case BM:
        return 9.27400968e-24;
    case NUC_M:
        return 5.05078353e-27;
    case VK:
        return 25812.8074434;

    // Physio-chemical constants 9
    case AMU:
        return 1.660538921e-27;
    case AN:
        return 6.02214129e23;
    case KB:
        return 1.3806488e-23;
    case F:
        return 96485.3365;
    case C1:
        return 3.74177153e-16;
    case C2:
        return 1.4387770e-2;
    case UG:
        return 8.3144621;
    case SB:
        return 5.670373e-8;
    case WD:
        return 2.8977721e-3;
    }

    return 0;
}

vector<int> getConstIndex()
{
    vector<int> const_index;
    for (int i = 0; i < NUM_CONSTANTS; i++)
    {
        const_index.push_back(i);
    }

    return const_index;
}
#endif