#include "open_mp_functions.hpp"
#include <armadillo>
#include <omp.h>
#include <chrono>
#include <thread>
// TODO: Use armadillo matrix instead of the standard library.
using namespace arma;

double omp_tester::run_tests()
{
    // NOTE: The code below is not meant to be scalable, demo purposes only.
    //       There is a fair amount of repeat code that could easily be re-factored.
    // TODO: use armadillo matrices instead of std::vectors.
    mat A = randu<mat>(1000, 1000);
    mat B = randu<mat>(1000, 1000);

    // Create a vector for storing all the execution times.
    std::vector<int> v_omp;
    std::vector<int> v_norm;

    // Run the code omp code 1000 times and get an average execution time.
    for (int i = 0; i < 1000; i++)
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        omp_sine();
        std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();

        int ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
        //std::cout << "omp time: " << ns << std::endl;
        v_omp.push_back(ns);
    }
    // Run the straight line code 1000 times and get an average execution time.
    for (int i = 0; i < 1000; i++)
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        normal_sine();
        std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();

        int ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
        //std::cout << "norm time: " << ns << std::endl;
        v_norm.push_back(ns);
    }
    // Get the stats for the omp loop.
    omp_tester::Stats omp_stats;
    omp_stats = get_stats(v_omp);
    // Get the stats for the straight line loop.
    omp_tester::Stats norm_stats;
    norm_stats = get_stats(v_norm);

    std::cout << "   OpenMP mean: " << omp_stats.mean << " nanoseconds" << std::endl;
    std::cout << "OpenMP std dev: " << omp_stats.std_dev << std::endl;
    std::cout << "   Normal mean: " << norm_stats.mean << " nanoseconds" << std::endl;
    std::cout << "Normal std dev: " << norm_stats.std_dev << std::endl;

    // ----------Start of OMP Tasks demonstration-------------
    std::cout << "START LONG EXECUTION SECTION!" << std::endl;

    //Create a vector for storing all the run times.
    std::vector<int> v_omp_l;
    std::vector<int> v_norm_l;

    // Execute long running code with OMP sections.
    for (int i = 0; i < 1000; i++)
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        run_omp_large();
        std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();

        int ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
        //std::cout << "omp time: " << ns << std::endl;
        v_omp_l.push_back(ns);
    }
    // Execute long running code with straight line code.
    for (int i = 0; i < 1000; i++)
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        run_norm_large();
        std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();

        int ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
        //std::cout << "norm time: " << ns << std::endl;
        v_norm_l.push_back(ns);
    }

    omp_tester::Stats omp_stats_l;
    omp_stats_l = get_stats(v_omp_l);

    omp_tester::Stats norm_stats_l;
    norm_stats_l = get_stats(v_norm_l);

    std::cout << "   OpenMP mean: " << omp_stats_l.mean << " nanoseconds" << std::endl;
    std::cout << "OpenMP std dev: " << omp_stats_l.std_dev << std::endl;
    std::cout << "   Normal mean: " << norm_stats_l.mean << " nanoseconds" << std::endl;
    std::cout << "Normal std dev: " << norm_stats_l.std_dev << std::endl;
    
    return 0;
}
// See header for comments.
omp_tester::Stats omp_tester::get_stats(std::vector<int> v)
{
    omp_tester::Stats cur_stats;
    double sum = std::accumulate(v.begin(), v.end(), 0.0);
    double mean = sum / v.size();
    std::vector<double> diff(v.size());
    std::transform(v.begin(), v.end(), diff.begin(), [mean](double x) { return x - mean; });
    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / v.size());

    cur_stats.mean = mean;
    cur_stats.std_dev = stdev;
    return cur_stats;
}
// See header for comments.
void omp_tester::omp_sine()
{

    const int size = 25600;
    double sinTable[size];

#pragma omp parallel for
    for(int n=0; n<size; ++n)
    {
        //I used this to verify that this is actually running multithreaded.
        //Uncomment if you want to verify also.
        //int cur_thread = omp_get_thread_num();
        //std::cout << "omp thread num: " << cur_thread << std::endl;

        sinTable[n] = std::sin(2 * M_PI * n / size);
        //This sleep will cause OpenMP to run faster than sequential code.
        if(add_sleep)
        {
            std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        }

        //Again there is some code commented out here for debugging.
        //This will allow you to see the order OpenMP decides to index
        //into the array.
/*
#pragma omp critical
        {
        std::cout << "Setting Index: " << n << std::endl;
        }
*/
    }
    (void)sinTable; //suppress compiler warning
}

void omp_tester::normal_sine()
{
    const int size = 25600;
    double sinTable[size];

    for(int n=0; n<size; ++n)
    {
        sinTable[n] = std::sin(2 * M_PI * n / size);
        if(add_sleep)
        {
            std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        }
    }
    (void)sinTable; //suppress compiler warning
}
// See header for comments.
void omp_tester::run_omp_tasks()
{
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task
            {normal_sine();}
            #pragma omp task
            {normal_sine();}
            #pragma omp task
            {normal_sine();}
            #pragma omp task
            {normal_sine();}
            #pragma omp task
            {normal_sine();}
            #pragma omp task
            {normal_sine();}
        }
    }
}

void omp_tester::run_sequential_tasks()
{
    normal_sine();
    normal_sine();
    normal_sine();
    normal_sine();
    normal_sine();
    normal_sine();
}
