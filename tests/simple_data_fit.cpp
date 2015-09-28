#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>
#include "../src/dcgp.hpp"

bool test_fails(
        unsigned int n,
        unsigned int m,
        unsigned int r,
        unsigned int c,
        unsigned int l,
        unsigned int N) // number of samples
{
   dcgp::function_set basic_set({"sum","diff","mul","div"});
   dcgp::expression ex(n, m, r, c, l, basic_set(), 123);

    // creates N data points 
    std::default_random_engine re;
    std::vector<std::vector<double> > in;
    std::vector<std::vector<double> > out;
    std::vector<double> in_point(n);
    std::vector<double> out_point(m);
    bool all_finite;
    // assuming that mutating the program will sooner or later produce an expression that is not nan or inf in any of the points ...
    // ... the following loop is not infinite
    do 
    {
        ex.mutate_active();
        all_finite=true;
        in.clear();
        out.clear();
        for (auto i = 0u; i < N; ++i)
        {
            for (auto j = 0u; j < n; ++j) 
            {
                in_point[j] = std::uniform_real_distribution<double>(-1, 1)(re);
            }
            out_point = ex(in_point);
            for (auto k : out_point) {
                if (!std::isfinite(k)) {
                    all_finite = false;
                }
            }
            in.push_back(in_point);
            out.push_back(out_point);
        }
    } while (!all_finite);

    if (simple_data_fit(ex, in, out, dcgp::fitness_type::HITS_BASED) == N * m) {
        return false;
    }
    std::cout << simple_data_fit(ex, in, out, dcgp::fitness_type::HITS_BASED) << "instead of: " << N * m << std::endl;
    return true;
}

/// This tests that computing the fitness simple_data_fit on data generated by the expression itself 
/// returns a zero error
int main() {
    return test_fails(2,4,2,3,4, 100) ||
           test_fails(2,4,10,10,11, 100) ||
           test_fails(2,4,20,20,21, 100) ||
           test_fails(1,1,1,100,101, 100) ||
           test_fails(1,1,2,100,101, 100) ||
           test_fails(1,1,3,100,101, 100);
}

