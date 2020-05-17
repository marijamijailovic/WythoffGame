#include <chrono>
#include <unistd.h>
#include <utility>
#include <iostream>
#include <functional>
#include <fstream>
#include "arithmetic.h"
#include "recursive.h"
#include "algebraic.h"

using namespace std::chrono;

class MeasureTime
{
  public:
    static void calculate_time() {
      ofstream statistics;
      statistics.rdbuf()->pubsetbuf(0,0);
      statistics.open("statistics.csv",ios::app);
      //for(int i=0,k=83886080;i<5;i++,k*=2){
        //statistics << k << ",";
        //cout << k << endl;
        //Recursive recursive(k, 2);
        //auto rec = bind(&Recursive::p_positions,recursive);
        //statistics << timer(rec) << ",";
        //statistics << ",";
        Algebraic algebraic(1342177280, 2);
        auto alg = bind(&Algebraic::p_positions,algebraic);
        statistics << timer(alg) << ",";
        //Arithmetic arithmetic(41943040, 2);
        //auto art = bind(&Arithmetic::arithmetic_characterization_of_P_Position,arithmetic);
        //statistics << timer(art);
        //statistics << ",";
        statistics << "\n";
      //}
      statistics.close();
    }

  private:
    static double timer(std::function<void()> func){
      auto start = high_resolution_clock::now();
      func();
      auto stop = high_resolution_clock::now();
      return duration<double, std::milli>(stop - start).count();
    }
};
