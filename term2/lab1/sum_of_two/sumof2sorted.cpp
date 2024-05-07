#include <iostream>
#include<chrono>
#include<bits/stdc++.h>

void sumof2(int sum, int* arr, size_t N, size_t &ret_1, size_t &ret_2) {
	ret_1 = 0; ret_2 = N-1;
	while(ret_1 < ret_2){
		if(arr[ret_1] + arr[ret_2] < sum)
			++ret_1;
		else if(arr[ret_1] + arr[ret_2] > sum)
			--ret_2;
		else
			return;
	}
	ret_1 = N; ret_2 = N;
	return;
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

	size_t ret_1, ret_2;
	for(size_t i = 0; i < iterations; ++i)
		sumof2(queries[i], arr, arrlen, ret_1, ret_2);

	auto end = std::chrono::steady_clock::now();
	delete[] arr;
	delete[] queries;
	auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	return (double)time_span.count() / iterations;
}

int main(int argc, char **argv){
	if(argc != 4){
		std::cerr << "Sumos2sorted expect 3 arguments(steps amount, iterations, output file) but you are giving" << argc - 1;
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
