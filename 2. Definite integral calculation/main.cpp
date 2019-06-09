#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <functional>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <omp.h>

double compute_function(const double x) {
    return (1. / (x * x)) * std::pow( std::sin(1. / x), 2 );
}

double _true_integral(const double x) {
    return (-1 / (2 * x)) + 0.25 * std::sin(2. / x);
}

const double true_integral(const double a, const double b) {
    return _true_integral(b) - _true_integral(a);
}

// Sequential compute
const double sequential_integral(const double a, const double b,
                                 const double npoints = 100) {

    const double width = (b - a) / npoints;

    double result = compute_function(a) / 2. + compute_function(b) / 2.;
    for (int i = 1; i < npoints; ++i) {
        result += compute_function(a + i * width);
    }
    return result * width;
}

// Recution parallel compute
const double reduction_integral(const double a, const double b,
                                const int npoints = 100) {
    const double width = (b - a) / npoints;

    double result = (compute_function(a) + compute_function(b)) / 2.;
#pragma omp parallel for reduction(+:result)
    for(int i = 1; i < npoints; i++) {
        result += compute_function(a + i * width);
    }

    return result * width;
}

// Critical compute integral
const double critical_integral(const double a, const double b,
                               const int npoints = 100) {
    const double width = (b - a) / npoints;

    double result = (compute_function(a) + compute_function(b)) / 2.;

#pragma omp parallel
    {
        const int thread_num = omp_get_num_threads();
        const int points_per_thread = std::ceil(npoints*1. / thread_num);

        int id = omp_get_thread_num();
        int limit = std::min((id + 1) * points_per_thread, npoints);
        double localresult = 0.;

        for (int i = std::max(id * points_per_thread, 1); i < limit; ++i) {
            localresult += compute_function(a + i * width);
        }

#pragma omp critical
        {
            result += localresult;
        }
    }

    return result * width;
}

// Atomic compute integral
const double atomic_integral(const double a, const double b,
                             const int npoints = 100) {
    const double width = (b - a) / npoints;

    double result = (compute_function(a) + compute_function(b)) / 2.;

#pragma omp parallel
    {
        const int thread_num = omp_get_num_threads();
        const int points_per_thread = std::ceil(npoints*1. / thread_num);

        int id = omp_get_thread_num();
        int limit = std::min((id + 1) * points_per_thread, npoints);
        double localresult = 0.;

        for (int i = std::max(id * points_per_thread, 1); i < limit; ++i) {
            localresult += compute_function(a + i * width);
        }

#pragma omp atomic
        result += localresult;
    }

    return result * width;
}

// Locks compute integral
const double locks_integral(const double a, const double b,
                            const int npoints = 100) {
    const double width = (b - a) / npoints;

    omp_lock_t lock;
    omp_init_lock(&lock);

    double result = (compute_function(a) + compute_function(b)) / 2.;

#pragma omp parallel
    {
        const int thread_num = omp_get_num_threads();
        const int points_per_thread = std::ceil(npoints*1. / thread_num);
        int id = omp_get_thread_num();
        int limit = std::min((id + 1) * points_per_thread, npoints);
        double localresult = 0.;

        for (int i = std::max(id * points_per_thread, 1); i < limit; ++i) {
            localresult += compute_function(a + i * width);
        }

        omp_set_lock(&lock);
        result += localresult;
        omp_unset_lock(&lock);
    }

    omp_destroy_lock(&lock);
    return result * width;
}

int timeit(std::function<double(double, double, int)> func,
           double left, double right, int npoints, int thread_num) {

    omp_set_num_threads(thread_num);

    auto start_time = std::chrono::system_clock::now();
    func(left, right, npoints);
    auto end_time = std::chrono::system_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    return elapsed.count();
}

void time_method(const std::string & method_name, std::function<double(double, double, int)> method) {

    std::cout << "Testing method: " << method_name << "\n";
    std::ofstream out("../_results/csv/" + method_name + "_perf_test.csv");
    out << "method,A,B,threads,npoints,time,attempt\n";

    for (auto & left : { .00001, .0001, .001, .01, .1, 1., 10. }) {
        auto right = left * 10;

        for (auto & npoints : {2000, 5000, 10000, 50000, 100000}) {
            for (auto & threads : {1, 2, 3, 4}) {
                for (int attempt = 1; attempt <= 5; ++attempt) {
                    double time = timeit(method, left, right, npoints, threads);

                    out << method_name << "," << left << "," << right << "," << threads
                        << "," << npoints << "," << time << "," << attempt <<"\n";
                }
            }
        }
    }
    out.close();
}

double compute_precision(std::function<double(double, double, int)> method, double left, double right, int npoints) {
    double n1 = method(left, right, npoints - 1);
    double n2 = method(left, right, npoints);

    return std::fabs(n1 - n2) / n2;
}

std::pair<int, double> approximate_with_precision(std::function<double(double, double, int)> method,
                                                  double left, double right, double precision) {

    int npoints = 10000;
    while ( compute_precision(method, left, right, npoints) > precision ) {
        npoints += 1;
        if (npoints == 1e9) {
            break;
        }
    }
    return {npoints, method(left, right, npoints)};
}

int binary_precision_search(std::function<double(double, double, int)> method, double left, double right, double precision) {

    int lhs = 10000, rhs=500000;
    while (lhs < rhs) {

        int mid = (lhs + rhs) / 2.;

        double mid_value = compute_precision(method, left, right, mid);
        double mid_l_value = compute_precision(method, left, right, mid - 1);

        if (mid_value >= precision && mid_l_value < precision) {
            return mid_value;
        } else if (mid_value > precision) {
            lhs = mid + 1;
        } else {
            rhs = mid;
        }
    }
    return -1;
}

int main(int argc, char const *argv[]) {

    const double left = .1;
    const double right = 1.;

    std::cout << std::setw(15) << "Sequential: " << sequential_integral(left, right, 2000) << std::endl
              << std::setw(15) << "Reduction: " << reduction_integral(left, right, 2000) << std::endl
              << std::setw(15) << "Critical: " << critical_integral(left, right, 2000) << std::endl
              << std::setw(15) << "Atomic: " << atomic_integral(left, right, 2000) << std::endl
              << std::setw(15) << "Locks: " << locks_integral(left, right, 2000) << std::endl
              << std::setw(15) << "True integral: " << true_integral(left, right);

    std::cout << "True: " << true_integral(left, right) << "\n"
              << "Appr: " << sequential_integral(left, right, 2000) << "\n"
              << "Precision: " << compute_precision(sequential_integral, left, right, 2000000);

    auto && [npoints, value] = approximate_with_precision(critical_integral, left, right, 2.2e-11);
    std::cout << "\nNpoints: " << npoints;

    // Performance testing
    time_method("sequential", sequential_integral);
    time_method("reduction", reduction_integral);
    time_method("critical", critical_integral);
    time_method("atomic", atomic_integral);
    time_method("locks", locks_integral);

    // Compute table


    std::vector<std::function<double(double, double, int)>>
            methods = {sequential_integral, atomic_integral, critical_integral, locks_integral, reduction_integral};

    std::vector<double> lhs = {.00001, .0001, .001, .01, .1,  1.,  10.};
    std::vector<double> rhs = {.0001,   .001,  .01,  .1, 1., 10., 100.};
    std::vector<double> prec = {2.77e-11, 1.9e-10, 2.05e-11, 2.22e12, 8.67e-11, 6e-11, 6.3e-11};
    std::vector<std::string> filenames = {"sequential", "atomic", "critical", "locks", "reduction"};

    for (int method_ind = 0; method_ind < 5; ++method_ind) {
        auto method = methods[method_ind];
        auto filename = filenames[method_ind];

        std::ofstream out("../_results/txt/" + filename + ".txt");

        for (auto && thread_num : {1, 2, 3, 4, 5, 6, 7, 8}) {
            std::cout << thread_num << "\n";
            for (int i = 0; i < 7; ++i) {
                int npoints = binary_precision_search(method, lhs[i], rhs[i], prec[i]);
                auto time = timeit(method, lhs[i], rhs[i], npoints, thread_num);
                out << lhs[i] << ";" << rhs[i] << ";" << npoints << ";" << prec[i] << ";" << time <<";\n";
            }
            out << "\n\n";
            if (filename == "sequential") {
                break;
            }
        }
        out.close();
    }

    return 0;
}