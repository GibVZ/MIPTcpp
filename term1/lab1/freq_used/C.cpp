#include <iostream>
#include<chrono>
#include<bits/stdc++.h>

size_t search(int el, int* arr, size_t N) {
        for(size_t ret = 0; ret < N; ++ret)
        	if(arr[ret] == el)
        		return ret;
        return N;
}

size_t smart_search(int el, int *arr, int *counter_arr, size_t N){
	size_t ret = search(el, arr, N);
	if((ret == 0) || (ret == N))
		return ret;
	++counter_arr[ret];
	if(counter_arr[ret] > counter_arr[ret-1]){
		std::swap(arr[ret], arr[ret-1]);
		std::swap(counter_arr[ret], counter_arr[ret-1]);
		return ret-1;
	}
	return ret;
}

int main(int argc, char **argv){
        if(argc != 3){
                std::cerr << "sumof2 expect 2 arguments(iterations, array lenght) but you are giving" << argc - 1;
                return -1;
        }
        size_t arrlen = atoi(argv[2]);
        size_t iterations = atoi(argv[1]);
        int *arr = new int[arrlen];
        int *queries = new int[iterations];

	for(size_t i = 0l i < arrlen; ++i)
		 arr[i] = std::rand();
        for(size_t i = 0; i < iterations; ++i)
                 queries[i] = std::rand();
        std::sort(arr[0], arr[arrlen-1]);

        auto begin = std::chrono::steady_clock::now();

        for(size_t i = 0; i < iterations; ++i){
                smart_search(queries[i], arr, arrlen);
        }

        auto end = std::chrono::steady_clock::now();
        auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

        std::cout << time_span.count() << std::endl;

	delete[] arr;
	delete[] queries;

	return 0;
}