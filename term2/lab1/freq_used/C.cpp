#include <iostream>
#include<chrono>
#include<bits/stdc++.h>

size_t search(int el, int* arr, size_t N) {
        for(size_t ret = 0; ret < N; ++ret)
        	if(arr[ret] == el)
        		return ret;
        return N;
}

size_t smart_search(int el, int *arr, size_t *counter_arr, size_t N){
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


std::default_random_engine generator;
std::binomial_distribution<size_t> *distribution;	

int query4(int *arr, size_t arrlen){
	size_t ret = (*distribution)(generator);
	if(ret >= arrlen)
		return -1;
	return arr[ret];
}

double selftest(size_t iterations, size_t arrlen){
	int *arr = new int[arrlen];
	size_t *counter = new size_t[arrlen];
	int *queries = new int[iterations];
	
	distribution = new std::binomial_distribution<size_t> {arrlen, 0.5};
	
	for(size_t i = 0; i < arrlen; ++i){
		arr[i] = std::rand();
		counter[i] = 0;
	}
	for(size_t i = 0; i < iterations; ++i){
		queries[i] = query4(arr, arrlen);
	}
	auto begin =  std::chrono::steady_clock::now();

	for(size_t i = 0; i < iterations; ++i)
		smart_search(queries[i], arr, counter, arrlen);

	auto end = std::chrono::steady_clock::now();
	delete[] arr;
	delete[] queries;
	delete[] counter;
	delete distribution;
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

/*
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
}*/
