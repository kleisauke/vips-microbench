# RGB

```bash
$ ./bin/vips-microbench-reduce --benchmark_repetitions=10
2019-07-02 20:54:07
Running ./bin/vips-microbench-reduce
Run on (6 X 4300 MHz CPU s)
CPU Caches:
  L1 Data 32K (x6)
  L1 Instruction 32K (x6)
  L2 Unified 256K (x6)
  L3 Unified 9216K (x1)
Load Average: 0.96, 0.95, 0.81
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               398 ms         9.38 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               448 ms         14.4 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               445 ms         14.6 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               437 ms         12.9 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               446 ms         13.4 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               433 ms         11.6 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               420 ms         10.7 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               407 ms         9.79 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               404 ms         8.62 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               404 ms         9.43 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_mean          424 ms         11.5 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_median        427 ms         11.2 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_stddev       20.0 ms         2.21 ms           10
```

# RGB with vectorized reduceh

```bash
2019-07-02 21:02:04
Running ./bin/vips-microbench-reduce
Run on (6 X 4300 MHz CPU s)
CPU Caches:
  L1 Data 32K (x6)
  L1 Instruction 32K (x6)
  L2 Unified 256K (x6)
  L3 Unified 9216K (x1)
Load Average: 0.94, 0.98, 0.90
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               401 ms         8.85 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               448 ms         13.5 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               439 ms         13.4 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               435 ms         13.2 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               435 ms         12.7 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               432 ms         11.2 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               413 ms         10.5 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               416 ms         10.5 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               416 ms         10.6 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               410 ms         9.95 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_mean          424 ms         11.4 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_median        424 ms         10.9 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_stddev       15.3 ms         1.64 ms           10
```

# RGBX

```bash
2019-07-02 21:07:31
Running ./bin/vips-microbench-reduce
Run on (6 X 4300 MHz CPU s)
CPU Caches:
  L1 Data 32K (x6)
  L1 Instruction 32K (x6)
  L2 Unified 256K (x6)
  L3 Unified 9216K (x1)
Load Average: 1.30, 1.24, 1.04
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               502 ms         7.98 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               482 ms         8.42 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               484 ms         8.19 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               487 ms         10.0 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               477 ms         8.88 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               478 ms         8.77 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               490 ms         9.95 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               480 ms         7.91 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               470 ms         7.60 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               474 ms         7.25 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_mean          482 ms         8.50 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_median        481 ms         8.30 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_stddev       9.01 ms        0.929 ms           10
```

# RGBX with vectorized reduceh

```bash
$ ./bin/vips-microbench-reduce --benchmark_repetitions=10
2019-07-02 20:48:54
Running ./bin/vips-microbench-reduce
Run on (6 X 4300 MHz CPU s)
CPU Caches:
  L1 Data 32K (x6)
  L1 Instruction 32K (x6)
  L2 Unified 256K (x6)
  L3 Unified 9216K (x1)
Load Average: 1.07, 1.05, 0.77
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               498 ms         9.83 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               528 ms         10.8 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               508 ms         10.9 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               483 ms         8.83 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               504 ms         9.50 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               487 ms         8.66 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               505 ms         10.2 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               512 ms         10.3 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               506 ms         10.7 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               497 ms         9.30 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_mean          503 ms         9.90 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_median        504 ms         10.0 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_stddev       12.7 ms        0.806 ms           10
```
