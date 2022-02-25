

This microbenchmark illustrates how "false sharing" type performance overheads exist for
memory accesses that are on nearby, but not the same, cache line.

The microbenchmark involves concurrent read/write access to adjacent & different blocks of K bytes of memory
that are K byte aligned for K=64,128,256,512.


Example output on an AWS instance 1-socket 8 physical cores Intel(R) Xeon(R) CPU E5-2666 v3 @ 2.90GHz:

```
$ CILK_NWORKERS=8 ./test_memory_perf
Running on 8 logically parallel tasks using 8 actual worker threads
TEST avg for alignment 64: 0.245000
TEST avg for alignment 128: 0.203000
TEST avg for alignment 256: 0.176000
TEST avg for alignment 512: 0.176000
TEST avg for alignment 64: 0.238000
TEST avg for alignment 128: 0.197000
TEST avg for alignment 256: 0.176000
```

Running on 1 worker (with same number of logical tasks does not have same overhead).

```
$ CILK_NWORKERS=1 ./test_memory_perf
Running on 8 logically parallel tasks using 1 actual worker threads
TEST avg for alignment 64: 0.835000
TEST avg for alignment 128: 0.836000
TEST avg for alignment 256: 0.839000
TEST avg for alignment 512: 0.839000
TEST avg for alignment 64: 0.835000
TEST avg for alignment 128: 0.835000
TEST avg for alignment 256: 0.839000
TEST avg for alignment 512: 0.839000
```
