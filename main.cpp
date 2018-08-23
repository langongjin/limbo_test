// please see the explanation in the documentation
// http://www.resibots.eu/limbo

#include <iostream>

// you can also include <limbo/limbo.hpp> but it will slow down the compilation
#include "limbo/bayes_opt/boptimizer.hpp"

using namespace limbo;

#define USE_NLOPT;

// Here we define the parameters
struct Params {
    struct bayes_opt_boptimizer : public defaults::bayes_opt_boptimizer {
    };
//    struct opt_nloptnograd : public defaults::opt_nloptnograd {
//    };
// depending on which internal optimizer we use, we need to import different parameters
#ifdef USE_NLOPT
    struct opt_nloptnograd : public defaults::opt_nloptnograd {
    };
#elif defined(USE_LIBCMAES)
    struct opt_cmaes : public defaults::opt_cmaes {
    };
#else
    struct opt_gridsearch : public defaults::opt_gridsearch {
    };
#endif

    struct kernel : public defaults::kernel {
        BO_PARAM(double, noise, 0.000001);
        BO_PARAM(bool, optimize_noise, false);
    };

    struct bayes_opt_bobase : public defaults::bayes_opt_bobase {
        BO_PARAM(bool, stats_enabled, true);
        BO_PARAM(bool, bounded, true); //false

    };

//    struct kernel_maternthreehalves : public defaults::kernel_maternthreehalves {
//        BO_PARAM(double, sigma_sq, 0.001);
//        BO_PARAM(double, l, 0.1);
//    };

    struct kernel_maternfivehalves : public defaults::kernel_maternfivehalves {
        BO_PARAM(double, sigma_sq, 0.001);
        BO_PARAM(double, l, 0.05);
    };

    struct init_randomsampling : public defaults::init_randomsampling {
        BO_PARAM(int, samples, 1);

    };

    struct stop_maxiterations : public defaults::stop_maxiterations {
        BO_PARAM(int, iterations, 2000); //we stop after 40 iterations

    };

    // we use the default parameters for acqui_ucb
    struct acqui_ucb : public defaults::acqui_ucb {
        //UCB(x) = \mu(x) + \alpha \sigma(x). high alpha have high exploration
        //iterations is high, alpha can be low for high accuracy in enoughiterations.
        // In contrast, the low iterations should have high alpha for high
        // searching in limited iterations, which guarantee to optimal.
        BO_PARAM(double, alpha, 0.5); // default alpha = 0.5
    };

//    // we use the default parameters for acqui_gpucb
//    struct acqui_gpucb : public limbo::defaults::acqui_gpucb {
//        //UCB(x) = \mu(x) + \kappa \sigma(x). high alpha have high exploration
//        BO_PARAM(double, delta, 1); // default alpha = 0.1
//    };
};

// Here we define the evaluation function
struct eval_func {
    // number of input dimension (x.size())
    BO_PARAM(size_t, dim_in, 20);
    // number of dimenions of the result (res.size())
    BO_PARAM(size_t, dim_out, 1);

    // the function to be optimized
    Eigen::VectorXd operator()(const Eigen::VectorXd& x) const
    {
        //double y = -((5 * x(0) - 2.5) * (5 * x(0) - 2.5)) + 5;
        //double y = (x(0) - 0.5) * std::sin(10 * (x(0) - 0.4));
        //double y = 0.5 - (0.8 * x(0) - 0.4) * (0.8 * x(0) - 0.4);
//        double y = x(0)*sin(10*x(0)) + x(1)*sin(10*x(1)) + x(2)*sin(10*x(2)) +
//                x(3)*sin(10*x(3)) + x(4)*sin(10*x(4));
        double y = x(0)*sin(10*x(0)) + x(1)*sin(10*x(1)) + x(2)*sin(10*x(2)) +
                   x(3)*sin(10*x(3)) + x(4)*sin(10*x(4)) + x(5)*sin(10*x(5)) +
                   x(6)*sin(10*x(6)) + x(7)*sin(10*x(7)) + x(8)*sin(10*x(8)) +
                   x(9)*sin(10*x(9)) + x(10)*sin(10*x(10)) + x(11)*sin(10*x(11)) +
                   x(12)*sin(10*x(12)) + x(13)*sin(10*x(13)) + x(14)*sin(10*x(14)) +
                   x(15)*sin(10*x(15)) + x(16)*sin(10*x(16)) + x(17)*sin(10*x(17)) +
                   x(18)*sin(10*x(18)) + x(19)*sin(10*x(19));
//        double y = 5 - std::pow(x(0),2) - std::pow(x(1),2) -
//                   std::pow(x(2),2) - std::pow(x(3),2) - std::pow(x(4),2);
//        double y = 20 - std::pow(x(0),2) - std::pow(x(1),2) -
//                   std::pow(x(2),2) - std::pow(x(3),2) - std::pow(x(4),2) -
//                   std::pow(x(5),2) - std::pow(x(6),2) - std::pow(x(7),2) -
//                   std::pow(x(8),2) - std::pow(x(9),2) - std::pow(x(10),2) -
//                   std::pow(x(11),2) - std::pow(x(12),2) - std::pow(x(13),2) -
//                   std::pow(x(14),2) - std::pow(x(15),2) - std::pow(x(16),2) -
//                   std::pow(x(17),2) - std::pow(x(18),2) - std::pow(x(19),2);
//        double y = 40 - std::pow(x(0),2) - std::pow(x(1),2) -
//                   std::pow(x(2),2) - std::pow(x(3),2) - std::pow(x(4),2) -
//                   std::pow(x(5),2) - std::pow(x(6),2) - std::pow(x(7),2) -
//                    std::pow(x(8),2) - std::pow(x(9),2) - std::pow(x(10),2) -
//                    std::pow(x(11),2) - std::pow(x(12),2) - std::pow(x(13),2) -
//                    std::pow(x(14),2) - std::pow(x(15),2) - std::pow(x(16),2) -
//                    std::pow(x(17),2) - std::pow(x(18),2) - std::pow(x(19),2) -
//                    std::pow(x(20),2) - std::pow(x(21),2) - std::pow(x(22),2) -
//                    std::pow(x(23),2) - std::pow(x(24),2) - std::pow(x(25),2) -
//                    std::pow(x(26),2) - std::pow(x(27),2) - std::pow(x(28),2) -
//                    std::pow(x(29),2) - std::pow(x(30),2) - std::pow(x(31),2) -
//                    std::pow(x(32),2) - std::pow(x(33),2) - std::pow(x(34),2) -
//                    std::pow(x(35),2) - std::pow(x(36),2) - std::pow(x(37),2) -
//                   std::pow(x(38),2) - std::pow(x(39),2);
        // we return a 1-dimensional vector
        return tools::make_vector(y);
    }
};

int main()
{
    // we use the default acquisition function / model / stat / etc.


    bayes_opt::BOptimizer<Params> boptimizer;
    // run the evaluation
    boptimizer.optimize(eval_func());
    // the best sample found
    std::cout << "Best sample: " << boptimizer.best_sample() << " - Best observation: " << boptimizer.best_observation()(0) << std::endl;
    return 0;
}
