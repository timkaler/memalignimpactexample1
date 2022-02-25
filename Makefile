.PHONY:	all clean

all: test_memory_perf


test_memory_perf:
	clang++ -O3 test_memory_perf.cpp -fopencilk -o test_memory_perf


clean:
	./setup.sh make -f Makefile2 clean
	./setup.sh make -f Makefile2_wl clean
	./setup.sh make -f Makefile2_hybrid clean
	./setup.sh make -f Makefile2_PLOCKS clean
	./setup.sh make -f Makefile2_serial clean
	rm -rf build build_wl build_hybrid build_serial build_plocks
