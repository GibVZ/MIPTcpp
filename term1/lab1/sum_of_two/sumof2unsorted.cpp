#include <iostream>
#include<chrono>


void sumof2(int sum, int* arr, size_t N, size_t &ret_1, size_t &ret_2) {
       for(ret_1 = 0; ret_1 < N - 1; ++ret_1){
		for(ret_2 = ret_1 + 1; ret_2 < N; ++ret_2){
			if(arr[ret_1] + arr[ret_2] == sum)
				return;
		}
       }
}

int main(int argc, char **argv){
/*	int N, sum;
	std::cin >> N >> sum;
	int *arr = new int[N];
	for(size_t i = 0; i < N; ++i)
		std::cin >> arr[i];
	size_t ret_1, ret_2;
	sumof2(sum, arr, N, ret_1, ret_2);
	delete[] arr;
	std::cout << ret_1 << " " << ret_2;
	return 0;
*/
        if(argc != 3){
                std::cerr << "sumof2 expect 2 arguments(iterations, array lenght) but you are giving" << argc - 1;
                return -1;
        }
        size_t arrlen = atoi(argv[2]);
        size_t iterations = atoi(argv[1]);
        int *arr = new int[arrlen];
        int *queries = new int[iterations];

        for(size_t i = 0; i < arrlen; ++i)
        	arr[i] = std::rand();
        for(size_t i = 0; i < iterations; ++i)
                queries[i] = std::rand();
        
        auto begin = std::chrono::steady_clock::now();

        for(size_t i = 0; i < iterations; ++i){
        	size_t ret_1, ret_2;
                sumof2(queries[i], arr, arrlen, ret_1, ret_2);
        }

        auto end = std::chrono::steady_clock::now();
        auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

        std::cout << time_span.count() << std::endl;

        delete[] arr;
        delete[] queries;
	return 0;
}


