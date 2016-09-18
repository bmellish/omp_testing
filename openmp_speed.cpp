//A simple program to test open mp for loop decorators.
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "openmp_speed.hpp"
#ifdef USE_OPEN_MP_FUNCTIONS
#include "open_mp_functions.hpp"
#endif



int main (int argc, char *argv[])
{
    std::cout << "Version: " << OpenMP_VERSION_MAJOR << "." << OpenMP_VERSION_MINOR << std::endl;

    omp_tester my_tester;

    my_tester.run_tests();

    return 0;
}
