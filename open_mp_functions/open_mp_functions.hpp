#ifndef OPEN_MP_FUNCTIONS
#define OPEN_MP_FUNCTIONS

//Use chrono in order to time the tests.
#include <chrono>
//Use utility in order to use the forward function.
#include <utility>
//Use the armadillo matrix libs.
#include <armadillo>

/*!
 * \brief The omp_tester class
 *        This class will facilitate the calling a few functions that can 
 *        demonstrate some useage scenarios for OpenMP.
 */
class omp_tester
{
private:
    // This will add a one nanoseconds sleep to the normal_sine function.
    // Turn this on if you want to simulate the overhead of kicking off a thread.
    bool add_sleep = false;
    // A simple struct for holding the mean and standard deviation returned from
    // the get_stats function.
    struct Stats {
        double mean;
        double std_dev;
    };
    // Run a simple sin function in a for loop with an omp decoration.
    void omp_sine();
    // Run the same simple sin function with straight line code.
    void normal_sine();
    // Run a bunch of long running tasks (many calls to the function that 
    // generates the sin array) sequentially.
    void run_sequential_tasks();
    // Run a bunch of long running tasks in parallel.
    void run_omp_tasks();
    // Calculate the mean and the standard deviation of a vector of ints.
    // TODO: This would be a good place to show template usage.
    Stats get_stats(std::vector<int>);
public:

    /*!
     * \brief run_tests
     * \return
     */
    double run_tests();

};



#endif
