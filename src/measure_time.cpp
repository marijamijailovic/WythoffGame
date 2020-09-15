#include "algebraic.h"
#include "arithmetic.h"
#include "recursive.h"
#include <chrono>
#include <cmath>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <utility>

using namespace std::chrono;

class MeasureTime {
public:
  static void caluculate_piles() {
    // Algebraic strategy
    ofstream piles_statistics;
    piles_statistics.rdbuf()->pubsetbuf(0, 0);
    piles_statistics.open("./statistics/csv/calculate_piles.csv", ios::app);
    for (long double i = 0, k = 10; i < 100; i++, k *= 2) {
      vector<long double> piles;
      stringstream sk;
      sk << fixed << setprecision(0) << k;
      piles_statistics << sk.str() << ",";
      // auto start = high_resolution_clock::now();
      biggest_piles_algebraic_method(k, 2, piles);
      stringstream spiles_0, spiles_1;
      spiles_0 << fixed << setprecision(0) << piles[0];
      // auto stop = high_resolution_clock::now();
      // piles_statistics << duration<double, std::milli>(stop - start).count()
      // << ",";
      piles_statistics << spiles_0.str() << ",";
      spiles_1 << fixed << setprecision(0) << piles[1];
      piles_statistics << spiles_1.str() << "\n";
    }
    piles_statistics.close();
  }

  static void calculate_time_n() {
    ofstream statistics;
    statistics.rdbuf()->pubsetbuf(0, 0);
    statistics.open("./statistics/csv/calculate_time_n.csv", ios::app);
    for (int i = 0, k = 10; i < 23; i++, k *= 2) {
      statistics << k << ",";
      Recursive recursive(k, 2);
      auto rec = bind(&Recursive::p_positions, recursive);
      statistics << timer(rec) << ",";
      Algebraic algebraic(k, 2);
      auto alg = bind(&Algebraic::p_positions, algebraic);
      statistics << timer(alg) << ",";
      Arithmetic arithmetic(k, 2);
      auto art = bind(&Arithmetic::arithmetic_characterization_of_P_Position,
                      arithmetic);
      statistics << timer(art);
      statistics << "\n";
    }
    statistics.close();
  }

  static void calculate_time_a() {
    ofstream statistics;
    statistics.rdbuf()->pubsetbuf(0, 0);
    statistics.open("./statistics/csv/calculate_time_a.csv", ios::app);
    for (int i = 0, a = 2; i < 25; i++, a *= 2) {
      statistics << a << ",";
      Algebraic algebraic(100000, a);
      auto alg = bind(&Algebraic::p_positions, algebraic);
      statistics << timer(alg) << ",";
      Arithmetic arithmetic(100000, a);
      auto art = bind(&Arithmetic::arithmetic_characterization_of_P_Position,
                      arithmetic);
      statistics << timer(art);
      statistics << "\n";
    }
    statistics.close();
  }

private:
  static void biggest_piles_algebraic_method(long double n, int a,
                                             vector<long double> &piles) {
    long double alpha = (2 - a + sqrt(a * a + 4)) / 2;
    long double beta = alpha + a;

    long double A = floor(alpha * n);
    long double B = floor(beta * n);

    piles.push_back(A);
    piles.push_back(B);
  }

  static double timer(std::function<void()> func) {
    auto start = high_resolution_clock::now();
    func();
    auto stop = high_resolution_clock::now();
    return duration<double, std::milli>(stop - start).count();
  }
};
