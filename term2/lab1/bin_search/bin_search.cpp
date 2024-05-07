#include <iostream>
#include<chrono>
#include<bits/stdc++.h>
#include<fstream>

size_t bin_search(int el, int* arr, size_t N) {
	size_t left_p = 0, right_p = N;
	while(left_p < right_p){
		size_t new_index = (left_p + right_p) / 2;
		if(arr[new_index] == el)
			return new_index;
		if(arr[new_index] > el)
			right_p = new_index;
		else
			left_p = new_index+1;
	}
	return N;
}

int query4(int *arr, size_t arrlen){
	return std::rand();
}

double selftest(size_t iterations, size_t arrlen){
	int *arr = new int[arrlen];
	int *queries = new int[iterations];
	for(size_t i = 0; i < arrlen; ++i){
		arr[i] = std::rand();
	}
	std::sort(arr[0], arr[arrlen - 1]);
	for(size_t i = 0; i < iterations; ++i){
		queries[i] = query4(arr, arrlen);
	}
	auto begin =  std::chrono::steady_clock::now();

	for(size_t i = 0; i < iterations; ++i)
		bin_search(queries[i], arr, arrlen);

	auto end = std::chrono::steady_clock::now();
	delete[] arr;
	delete[] queries;
	auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	return (double)time_span.count() / iterations;
}

int main(int argc, char **argv){
	if(argc != 4){
		std::cerr << "Brut_search expect 3 arguments(steps amount, iterations, output file) but you are giving" << argc - 1;
		return -1;
	}
	size_t steps = atoi(argv[1]);
	size_t iterations = atoi(argv[2]);
	size_t maxlen = 1000000;
	size_t minlen = 100;
	std::ofstream os(argv[3]);
	for(size_t arrlen = minlen; arrlen < maxlen; arrlen+=(maxlen - minlen)/steps){
		os << selftest(iterations, arrlen) << " " << arrlen << "\n";
	}
	os.close();
	return 0;
}
