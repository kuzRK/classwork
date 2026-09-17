#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <future>


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
  std::chrono::time_point< std::chrono::high_resolution_clock > start_;
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
  const size_t block_size = size / thread_count;

  std::vector< std::future< value_t > > futures;
  futures.reserve(thread_count);

  Clicker cl;

  for (size_t i = 0; i < thread_count; ++i)
  {

    const size_t begin = i * block_size;

    const size_t end = (i == thread_count - 1) ? size : begin + block_size;

    futures.emplace_back(
        std::async(
            std::launch::async,
            sum_range,
            std::cref(values),
            begin,
            end));
  }

  value_t sum = 0;

  for (auto &f : futures)
  {
    sum += f.get();
  }

  double time = cl.millisec();

  std::cout << time << '\n';
}
