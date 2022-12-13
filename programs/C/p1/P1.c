// P1 Assignment
// Author: Brody Larson
// Date:   8/22/2022
// Class:  CS270
// Email:  larsonbm@colostate.edu

// Include files
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

double input[5];
double output[4];

// this function can be used as a guide for the funtions you will implement
void computeSphere(double a1, double* ret){
    double res = (4.0/3.0) * 3.141593 * a1 * a1 * a1;
    *ret = res;
}
void computeCube(double a1, double* ret){
    double res = a1 * a1 * a1;
    *ret = res;
}
void computeTetrahedron(double a1, double* ret){
    double res = 0.117851 * a1 * a1 * a1;
    *ret = res;
}
void computeCylinder(double a1, double a2, double* ret){
    double res = 3.141593 * a1 * a1 * a2;
    *ret = res;
}


int main(int argc, char *argv[])
{
    // Check number of arguments
    if (argc != 6) {
        printf("usage: ./P1 <double> <double> <double> <double> <double>\n");
        return EXIT_FAILURE;
    }

    // Parse arguments
    double radius = atof(argv[1]);

    computeSphere(radius, &output[0]);
    computeCube(atof(argv[2]), &output[1]);
    computeTetrahedron(atof(argv[3]), &output[2]);
    computeCylinder(atof(argv[4]), atof(argv[5]), &output[3]);

    printf("SPHERE, radius = %.5f, volume = %.5f.\n", radius, output[0]);
    printf("CUBE, side = %.5f, volume = %.5f.\n", atof(argv[2]), output[1]);
    printf("TETRAHEDRON, side = %.5f, volume = %.5f.\n", atof(argv[3]), output[2]);
    printf("CYLINDER, radius = %.5f, height = %.5f, volume = %.5f.\n", atof(argv[4]), atof(argv[5]), output[3]);

    // Return success
    return EXIT_SUCCESS;
}