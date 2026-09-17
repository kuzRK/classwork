#include <cstddef>
#include <iostream>
#include <string>
#include <vector>


  using data_t = std::vector<unsigned long long>;
  using value_t = data_t::value_type;

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Incorrect number of arg\n";
        return 1;
    }

    constexpr size_t size = 1'000'000'000;

    const size_t thread_count = std::stoull(argv[1]);

    if (thread_count == 0) {
        std::cerr << "Incorrect num of tasks\n";
        return 1;
    }

    data_t values(size, 1);
}
