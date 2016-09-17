#include "open_mp_functions.hpp"
#include <armadillo>

#include <omp.h>

#include <chrono>


using namespace arma;

double omp_tester::run_tests()
{
    mat A = randu<mat>(1000, 1000);
    mat B = randu<mat>(1000, 1000);

    //Create a vector for storing all the run times.
    std::vector<int> v_omp;
    std::vector<int> v_norm;

    for (int i = 0; i < 10; i++)
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        run_omp();
        std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();

        int ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
        std::cout << "omp time: " << ms << std::endl;
        v_omp.push_back(ms);
    }

    for (int i = 0; i < 10; i++)
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        run_norm();
        std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();

        int ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
        std::cout << "norm time: " << ms << std::endl;
        v_norm.push_back(ms);
    }

    double sum_omp = std::accumulate(v_omp.begin(), v_omp.end(), 0.0);
    double mean_omp = sum_omp / v_omp.size();

    double sum_norm = std::accumulate(v_norm.begin(), v_norm.end(), 0.0);
    double mean_norm = sum_norm / v_norm.size();

    std::cout << "Open MP: " << mean_omp << " microseconds" << std::endl;
    std::cout << "Norm:  " << mean_norm << " microseconds" << std::endl;
    return 0;
}

double omp_tester::run_omp()
{
    const int size = 25600;
    double sinTable[size];

#pragma omp parallel num_threads(8)
    {
        printf("hello from %d of %d\n",
               omp_get_thread_num(),
               omp_get_num_threads());
#pragma omp parallel for
        for(int n=0; n<size; ++n)
        {
            sinTable[n] = std::sin(2 * M_PI * n / size);
        }
    }
}

double omp_tester::run_norm()
{
    const int size = 25600;
    double sinTable[size];

    for(int n=0; n<size; ++n)
    {
        sinTable[n] = std::sin(2 * M_PI * n / size);
    }
}
