# Experiment with RGBX

See [libvips/libvips#1332](https://github.com/libvips/libvips/issues/1332).

## RGB

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

## RGB with vectorized reduceh

```bash
2019-07-04 13:50:16
Running ./bin/vips-microbench-reduce
Run on (6 X 4300 MHz CPU s)
CPU Caches:
  L1 Data 32K (x6)
  L1 Instruction 32K (x6)
  L2 Unified 256K (x6)
  L3 Unified 9216K (x1)
Load Average: 0.90, 0.86, 0.83
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               404 ms         9.30 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               446 ms         13.9 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               441 ms         12.7 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               421 ms         11.1 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               412 ms         10.7 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               415 ms         10.5 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               414 ms         10.7 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               411 ms         9.52 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               413 ms         9.81 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               407 ms         10.4 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_mean          419 ms         10.9 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_median        414 ms         10.6 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_stddev       14.1 ms         1.44 ms           10
```

## RGBX

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

## RGBX with vectorized reduceh

```bash
$ ./bin/vips-microbench-reduce --benchmark_repetitions=10
2019-07-04 13:39:17
Running ./bin/vips-microbench-reduce
Run on (6 X 4300 MHz CPU s)
CPU Caches:
  L1 Data 32K (x6)
  L1 Instruction 32K (x6)
  L2 Unified 256K (x6)
  L3 Unified 9216K (x1)
Load Average: 1.24, 1.02, 0.92
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               511 ms         11.6 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               517 ms         12.9 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               518 ms         14.2 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               510 ms         13.1 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               513 ms         13.4 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               516 ms         13.0 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               500 ms         12.2 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               495 ms         11.6 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               493 ms         10.9 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               483 ms         9.28 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_mean          506 ms         12.2 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_median        510 ms         12.5 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_stddev       12.2 ms         1.43 ms           10
```
