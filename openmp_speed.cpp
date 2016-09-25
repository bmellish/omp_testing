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
    // Print out what version the user is running.  Can be updated via cmake configs.
    std::cout << "Version: " << OpenMP_VERSION_MAJOR << "." << OpenMP_VERSION_MINOR << std::endl;
    // Instantiate the omp_tester class.
    omp_tester my_tester;
    // Run the public method that kicks off the tests.
    my_tester.run_tests();
    // TODO:: work in some error checking.
    return 0;
}
