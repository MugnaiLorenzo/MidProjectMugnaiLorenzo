#include "Benchmark.h"
#include "../include/gplot++.h"

void Benchmark::addResult(const std::string &method, int threads, double execution_time) {
    results[method].emplace_back(threads, execution_time);
}

std::map<std::string, std::vector<double>> Benchmark::calculateSpeedup() {
    std::map<std::string, std::vector<double>> speedups;
    for (const auto &[method, data] : results) {
        if (data.empty()) continue;

        double sequential_time = data.front().second;
        for (const auto &[threads, time] : data) {
            speedups[method].push_back(sequential_time / time);
        }
    }
    return speedups;
}

void Benchmark::plotExecutionTimes(const std::string &outputFile, std::string n_book) {
    Gnuplot gnuplot;

    for (const auto &[method, data] : results) {
        gnuplot.redirect_to_png(outputFile + n_book+"_"+ method+".png");
        std::vector<int> threads;
        std::vector<double> times;

        for (const auto &[t, time] : data) {
            threads.push_back(t);
            times.push_back(time);
        }

        gnuplot.plot(threads, times, method);
        gnuplot.set_title("Execution Times");
        gnuplot.set_xlabel("Threads");
        gnuplot.set_ylabel("Time (seconds)");
        gnuplot.show();
    }
}

void Benchmark::plotSpeedup(const std::string &outputFile, std::string n_book) {
    auto speedups = calculateSpeedup();
    Gnuplot gnuplot;

    for (const auto &[method, sp] : speedups) {
        gnuplot.redirect_to_png(outputFile + n_book + "_"+ method + ".png");
        std::vector<int> threads;
        threads.push_back(1);
        for (size_t i = 1; i < sp.size(); ++i) {
            threads.push_back( i * 2);
        }
        gnuplot.set_xrange(1,12);
        gnuplot.plot(threads, sp, method);
        gnuplot.set_title("Speedup");
        gnuplot.set_xlabel("Threads");
        gnuplot.set_ylabel("Speedup");
        gnuplot.show();
    }
}

