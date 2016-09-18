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
 */
class omp_tester
{
private:
    bool add_sleep = false;
    struct Stats {
        double mean;
        double std_dev;
    };
    void omp_sine();
    void normal_sine();
    void run_sequential_tasks();
    void run_omp_tasks();
    Stats get_stats(std::vector<int>);
public:

    /*!
     * \brief run_tests
     * \return
     */
    double run_tests();

};



#endif
