#include <iostream>
#include<chrono>
#include<bits/stdc++.h>

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

int main(int argc, char **argv){
	if(argc != 3){
		std::cerr << "bin_search expect 2 arguments(iterations, array lenght) but you are giving" << argc - 1;
		return -1;
	}
	size_t arrlen = atoi(argv[2]);
	size_t iterations = atoi(argv[1]);
	int **arr = new int*[iterations];
	int *queries = new int[iterations];
	for(size_t i = 0; i < iterations; ++i){
		arr[i] = new int[arrlen];
		queries[i] = std::rand();
		for(size_t j = 0; j < arrlen; ++j){
			arr[i][j] = std::rand();
		}
		std::sort(arr[i], arr[i]+arrlen);
	}
	auto begin = std::chrono::steady_clock::now();

	for(size_t i = 0; i < iterations; ++i){
		bin_search(queries[i], arr[i], arrlen);
	}
	auto end = std::chrono::steady_clock::now();
	auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

	std::cout << time_span.count() << std::endl;
	
	for(size_t i = 0; i < iterations; ++i)
		delete arr[i];
	delete arr;
	delete queries;
}
