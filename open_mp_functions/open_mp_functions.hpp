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
    int a_var;
    std::vector<std::vector<double> > matrix;
    double run_norm();
    double run_omp();
public:
    /*!
     * \brief run_tests
     * \return
     */
    double run_tests();

};



#endif
