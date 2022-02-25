.PHONY:	all clean

all: test_memory_perf


test_memory_perf: test_memory_perf.cpp
	clang++ -O3 -DN_CILK_WORKERS=8 test_memory_perf.cpp -fopencilk -o test_memory_perf

#test_memory_perf_serial:
#	clang++ -O3 -DN_CILK_WORKERS=1 test_memory_perf.cpp -fopencilk -o test_memory_perf_serial

clean:
	touch test_memory_perf test_memory_perf_serial
	-rm test_memory_perf test_memory_perf_serial
