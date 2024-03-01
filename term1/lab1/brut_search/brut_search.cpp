#include <iostream>
#include<chrono>


size_t brut_search(int el, int* arr, size_t N) {
	size_t ret = 0;
	while(ret < N){
		if(arr[ret] == el)
			return ret;
		++ret;
	}
	return ret;
}

int main(int argc, char **argv){
	if(argc != 3){
		std::cerr << "Brut_search expect 2 arguments(iterations, array lenght) but you are giving" << argc - 1;
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
	}
	auto begin = std::chrono::steady_clock::now();

	for(size_t i = 0; i < iterations; ++i){
		brut_search(queries[i], arr[i], arrlen);
	}

	auto end = std::chrono::steady_clock::now();
	auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

	std::cout << time_span.count() << std::endl;
}
