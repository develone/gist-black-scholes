#include <stdio.h>
#include <stdlib.h>
#include "bs.h"

int main(int argc, char *argv[])
{
    double strike = atof(argv[1]);
    double asset = atof(argv[2]);
    double std = atof(argv[3]);
    double rfr = atof(argv[4]);
    double dte = atof(argv[5]);
    printf("Strike Price: %f \n", strike);
    printf("Asset Price:  %f \n", asset);
    printf("Std Dev:      %f \n", std);
    printf("Risk Free:    %f \n", rfr);
    printf("Days to Exp:  %f \n", dte);
    printf("Put Value:    %f \n", putvalue(strike, asset, std, rfr, dte));
    printf("Call Value:   %f \n", callvalue(strike, asset, std, rfr, dte));
    printf("Delta Ratio:  %f \n", delta(strike, asset, std, rfr, dte));
    printf("T-Bills:      %f \n", bond(strike, asset, std, rfr, dte));
    return 0;
}