#include <math.h>
#include "bs.h"

#define DAYS_IN_YEAR 365

static double N(double, double, double, double, double);
static double delta2(double, double, double);
static double ND2(double, double, double);

static double N(double strike, double s, double sd, double r, double days)
{
    double ls = log(s);
    double lx = log(strike);
    double t = days / DAYS_IN_YEAR;
    double sd2 = pow(sd, 2);
    return ls - lx + r * t + sd2 * t / 2;
}

double delta(double strike, double s, double sd, double r, double days)
{ 
    double n = N(strike, s, sd, r, days);
    double sqT = sqrt(days / DAYS_IN_YEAR);
    double d = sd * sqT;
    double d1 = n / d;
    return normal(d1);
}

static double delta2(double n, double sd, double days)
{
    double sqT = sqrt(days / DAYS_IN_YEAR);
    double d = sd * sqT;
    double d1 = n / d;
    return normal(d1);
}

static double ND2(double n, double sd, double days)
{ 
     double sqrtT = sqrt(days / DAYS_IN_YEAR);
     double d = sd * sqrtT;
     double d1 = n / d;
     double d2 = d1 - sd * sqrtT;
     return normal(d2);
}

double bond(double strike, double s, double sd, double r, double days)
{   
    double n = N(strike, s, sd, r, days);
    double t = days / DAYS_IN_YEAR;
    double nd1 = delta2(n, sd, days);
    double nd2 = ND2(n, sd, days);
    return -strike * exp(-r*t) * nd2;
}


double callvalue(double strike, double s, double sd, double r, double days)
{ 
     double n = N(strike, s, sd, r, days);
     double t = days / DAYS_IN_YEAR;
     double nd1 = delta2(n, sd, days);
     double b = bond(strike, s, sd, r, days);
     return s * nd1 + b;
}


double putvalue(double strike, double s, double sd, double r, double days)
{
     double t = days / DAYS_IN_YEAR;
     double call = callvalue(strike, s, sd, r, days);
     return strike * exp(-r * t) - s + call;
}


double normal(double zz)
{ 
    //cdf of 0 is 0.5
    if (zz == 0)   
    { 
        return 0.5;
    }
    
    double z = zz;  //zz is input variable,  use z for calculations
    
    if (zz < 0)
        z = -zz;  //change negative values to positive
    
    //set constants
    double p = 0.2316419;  
    double b1 = 0.31938153;
    double b2 = -0.356563782;
    double b3 = 1.781477937;
    double b4 = -1.821255978;
    double b5 = 1.330274428;
    
    //CALCULATIONS
    double f = 1 / sqrt(2 * M_PI);
    double ff = exp(-pow(z, 2) / 2) * f;
    double s1 = b1 / (1 + p * z);
    double s2 = b2 / pow((1 + p * z), 2);
    double s3 = b3 / pow((1 + p * z), 3);
    double s4 = b4 / pow((1 + p * z), 4);
    double s5 = b5 / pow((1 + p * z), 5);
    
    //sz is the right-tail approximation
    double  sz = ff * (s1 + s2 + s3 + s4 + s5); 

    double rz; 
    //cdf of negative input is right-tail of input's absolute value 
    if (zz < 0)
        rz = sz;
    
    //cdf of positive input is one minus right-tail 
    if (zz > 0)
        rz = (1 - sz);
    return rz;
}