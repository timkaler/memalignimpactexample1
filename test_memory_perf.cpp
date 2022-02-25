#include <iostream>
#include <thread>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <functional>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

using namespace std;

#ifndef N_CILK_WORKERS
#define N_CILK_WORKERS 8
#endif

__attribute__((weak))
	void mystery(char* bytes) {return; }

__attribute__((weak))
	void pound_cacheline(char* bytes, int idx, int offset) {
		for (int j = 0; j < 1000000; j++) {
			for (int i = 0; i < 64; i++) {
				bytes[i*8 + (idx)*(8*64 + offset*64)] += bytes[i*8 + (idx)*(64*8 + offset*64)] + 1;
				mystery(bytes);
			}
		}
	}

__attribute__((weak))
void bench(char* bytes, int offset) {
	for (int i = 0; i < N_CILK_WORKERS/*__cilkrts_get_nworkers()*/; i++) {
		cilk_spawn pound_cacheline(bytes, i, offset);
	}
		cilk_sync;
}

unsigned long long todval (struct timeval *tp) {
    return tp->tv_sec * 1000 * 1000 + tp->tv_usec;
}

int main() {
  int max_workers = N_CILK_WORKERS;
  printf("Running on nworkers: %d\n", max_workers);
  char* bytes = (char*)aligned_alloc(4096, 4096*max_workers);
  for (int repeat = 0; repeat < 2; repeat++) {
  for (int offset = 1; offset < 16; offset *= 2) {
  unsigned long long runtime_ms_sum = 0;
  for (int iter = 0; iter < 100; iter++) {
    struct timeval t1, t2;
    gettimeofday(&t1,0);
    bench(bytes, offset);
    gettimeofday(&t2,0);
    unsigned long long runtime_ms = (todval(&t2)-todval(&t1))/1000;
    runtime_ms_sum += runtime_ms;
    //printf("TEST: %f\n", runtime_ms/1000.0);
  }
    printf("TEST avg for alignment %d: %f\n", offset*64, (runtime_ms_sum/100)/1000.0);
  }
  }
}
