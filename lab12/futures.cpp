#include <fstream>
#include <ios>
#include <iostream>
#include <future>
#include <exception>
#include <thread>
#include <vector>

void computeAsciiSum(const std::string& filename, 
                     std::promise<long long> prom) {
    std::ifstream file(filename, std::ios::binary);
    if(!file) {
        std::cout << "error" << std::endl;
        prom.set_exception(std::make_exception_ptr(
                           std::ios_base::failure("Failed to open file")));
        return;
    }

    char c;
    long long sum = 0;
    while(file.get(c)) {
        sum += c;
    }

    prom.set_value(sum);
}


int main(int argc, char* argv[]) {
    std::vector<std::string> filenames(argv + 1, argv + argc);
    std::vector<std::thread> threads;
    std::vector<std::future<long long>> futures;
    threads.reserve(std::thread::hardware_concurrency());
    futures.reserve(argc - 1);


    for(const auto& file : filenames) {
        std::promise<long long> p;
        futures.push_back(p.get_future());
        threads.emplace_back(computeAsciiSum, file, std::move(p));
    }

    for(auto& t : threads) {
        t.join();
    }

    std::vector<long long> sums;
    sums.reserve(futures.size());
    for(auto& f : futures) {
        sums.push_back(f.get());
    }

    for(int i = 0; i < sums.size(); ++i) {
        std::cout << filenames.at(i) << " : " << sums.at(i) << std::endl;
    }

    std::cout << std::endl;

    for(int i = 0; i < sums.size(); ++i) {
        for(int k = i + 1; k < sums.size(); ++k) {
            if(sums[i] == sums[k]) {
                std::cout << filenames.at(i) << " has the same sum -> " << filenames.at(k) << std::endl;
            }
        }
    }
}
