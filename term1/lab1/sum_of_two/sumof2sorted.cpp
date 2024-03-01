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

int main(int argc, char **argv){
        if(argc != 3){
                std::cerr << "sumof2 expect 2 arguments(iterations, array lenght) but you are giving" << argc - 1;
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
                size_t ret_1, ret_2;
                sumof2(queries[i], arr[i], arrlen, ret_1, ret_2);
        }

        auto end = std::chrono::steady_clock::now();
        auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

        std::cout << time_span.count() << std::endl;

        for(size_t i = 0; i < iterations; ++i)
                delete[] arr[i];
        delete[] arr;
        delete[] queries;
        return 0;
}

