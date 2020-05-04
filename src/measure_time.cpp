#include <chrono>
#include <utility>
#include <functional>

using namespace std::chrono;

class MeasureTime
{
  public:
    static auto calculate_time(std::function<void()> func){
      auto start = high_resolution_clock::now();
      func();
      auto stop = high_resolution_clock::now();
      return duration_cast<nanoseconds>(stop - start).count();
    }
};
