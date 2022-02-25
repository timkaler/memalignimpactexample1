

This microbenchmark illustrates how "false sharing" type performance overheads exist for
memory accesses that are on nearby, but not the same, cache line.

The microbenchmark involves concurrent read/write access to adjacent & different blocks of K bytes of memory
that are K byte aligned for K=64,128,256,512.


Example output on an AWS instance 1-socket 8 physical cores Intel(R) Xeon(R) CPU E5-2666 v3 @ 2.90GHz:

```
Running on nworkers: 8
TEST avg for alignment 64: 0.223000
TEST avg for alignment 128: 0.192000
TEST avg for alignment 256: 0.176000
TEST avg for alignment 512: 0.176000
TEST avg for alignment 64: 0.224000
TEST avg for alignment 128: 0.194000
TEST avg for alignment 256: 0.176000
TEST avg for alignment 512: 0.174000
```
