#include <iostream>
#include <mutex>
#include <random>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <cctype>
#include <ctime>
#include <thread>
#include <utility>
#include <thread>
#include <chrono>
using namespace std;

template <int N>
struct Array{
    int a[N];
    int i  = 0;
    int value = 1;
	long long sum = 0;

	int f(int x){
		int y = x%11;
		return (y*y+1);
	}

    void genFragment(int begin, int end, unsigned int seed) {
        std::mt19937 rng(seed);
        int start = begin;
		while(start < end){
		    a[start++] = rng();
		}
        start = begin;
		while(start < end){
			a[start] = f(a[start]);
			++start;
		}
    }

	void generateArray(int numOfThreads){
        int fragmentSize = N / numOfThreads;
        std::vector<std::thread> t;
        t.reserve(numOfThreads);
        for(int i = 0; i < numOfThreads; i++) {
            int begin = i * fragmentSize;
            int end = (i == numOfThreads - 1) ? N : begin + fragmentSize;
            t.emplace_back(&Array::genFragment, this, begin, end, i);
        }
        for(auto& x : t) {
            x.join();
        }
	}
	
	long long computeSum(){
	    sum = 0;
		for(int x : a){
            sum += x;
		}
		return sum;
	}
};

int main(){
	srand(2019);
	using A = Array<1000>;
	A array;
	std::thread t1(&A::generateArray, &array, 4);
	// std::thread t2(&A::genFragment, &array, 500, 1000, 1);
//  What happens if you uncomment this line?
    std::thread t2(&A::generateArray, &array, 5);
     t2.join();
	t1.join();

	for(int i=0; i<40; i++){
		cout << array.a[0+i] << "  ";
	}

	long long sum = array.computeSum();
	cout << "\n sum = " << sum << endl;	
}
