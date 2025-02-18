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

void Benchmark::plotExecutionTimesComparison(const std::string &outputFile, std::string n_book) {
    Gnuplot gnuplot;
    gnuplot.redirect_to_png(outputFile + n_book + "_Comparison.png");

    gnuplot.set_title("Execution Times Comparison");
    gnuplot.set_xlabel("Threads");
    gnuplot.set_ylabel("Time (seconds)");

    // Definizione di colori personalizzati per ogni metodo
    std::map<std::string, std::string> colors = {
            {"ParallelAoS", "red"},
            {"ParallelSoA", "blue"},
            {"VectorizedSoA", "green"},
            {"SequentialAoS", "black"},
            {"SequentialSoA", "purple"}
    };

    std::stringstream plot_command;
    int line_type = 1; // Indice per i diversi tipi di linee in Gnuplot

    for (const auto &[method, data] : results) {
        if (data.empty()) continue;

        // Assegna uno stile di linea con colore specifico
        gnuplot.sendcommand("set style line " + std::to_string(line_type) +
                            " lt " + std::to_string(line_type) +
                            " lc rgb '" + colors[method] + "'");

        // Se è il primo metodo, avvia il comando plot, altrimenti aggiunge una virgola
        if (line_type == 1) {
            plot_command << "plot '-' using 1:2 with lines ls " << line_type << " title '" << method << "'";
        } else {
            plot_command << ", '-' using 1:2 with lines ls " << line_type << " title '" << method << "'";
        }

        line_type++;
    }

    // Esegui il comando di plotting
    gnuplot.sendcommand(plot_command.str());

    // Inserisci i dati per ogni metodo
    for (const auto &[method, data] : results) {
        if (data.empty()) continue;

        for (const auto &[t, time] : data) {
            gnuplot.sendcommand(std::to_string(t) + " " + std::to_string(time));
        }
        gnuplot.sendcommand("e"); // Termina la serie di dati
    }

    gnuplot.show();
}


void Benchmark::plotSpeedupComparison(const std::string &outputFile, std::string n_book) {
    auto speedups = calculateSpeedup();
    Gnuplot gnuplot;
    gnuplot.redirect_to_png(outputFile + n_book + "_Comparison.png");

    gnuplot.set_title("Speedup Comparison");
    gnuplot.set_xlabel("Threads");
    gnuplot.set_ylabel("Speedup");

    std::map<std::string, std::string> colors = {
            {"ParallelAoS", "red"},
            {"ParallelSoA", "blue"},
            {"VectorizedSoA", "green"},
            {"SequentialAoS", "black"},
            {"SequentialSoA", "purple"}
    };

    std::stringstream plot_command;
    int line_type = 1;

    for (const auto &[method, sp] : speedups) {
        if (sp.empty()) continue;

        gnuplot.sendcommand("set style line " + std::to_string(line_type) +
                            " lt " + std::to_string(line_type) +
                            " lc rgb '" + colors[method] + "'");

        if (line_type == 1) {
            plot_command << "plot '-' using 1:2 with lines ls " << line_type << " title '" << method << "'";
        } else {
            plot_command << ", '-' using 1:2 with lines ls " << line_type << " title '" << method << "'";
        }

        line_type++;
    }

    gnuplot.sendcommand(plot_command.str());

    for (const auto &[method, sp] : speedups) {
        if (sp.empty()) continue;

        for (size_t i = 0; i < sp.size(); ++i) {
            int threads = (i == 0) ? 1 : (i * 2); // Primo valore = sequenziale, poi incremento di 2 thread per volta
            gnuplot.sendcommand(std::to_string(threads) + " " + std::to_string(sp[i]));
        }

        gnuplot.sendcommand("e");
    }

    gnuplot.show();
}



