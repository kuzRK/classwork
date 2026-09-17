#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <future>
#include <algorithm>

class Clicker
{
public:
  Clicker():
    start_(std::chrono::high_resolution_clock::now())
  {}

  double millisec() const
  {
    auto t = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast< std::chrono::duration< double, std::milli > >(t - start_).count();
  }

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start_;
};

using data_t = std::vector< unsigned long long >;
using value_t = data_t::value_type;

value_t sum_range(
    const data_t &values,
    size_t begin,
    size_t end)
{
  value_t local_sum = 0;

  for (size_t i = begin; i < end; ++i)
  {
    local_sum += values[i];
  }

  return local_sum;
}

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cerr << "Incorrect number of arg\n";
    return 1;
  }

  constexpr size_t size = 1'000'000'000;

  const size_t thread_count = std::stoull(argv[1]);

  if (thread_count == 0)
  {
    std::cerr << "Incorrect num of tasks\n";
    return 1;
  }

  data_t values(size, 1);
  
}
