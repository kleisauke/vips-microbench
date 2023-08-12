# Experiment with Highway

See https://github.com/kleisauke/libvips/tree/simd-highway.

## Test image
```console
$ vipsheader images/x.jpg
images/x.jpg: 10000x10000 uchar, 3 bands, srgb, jpegload
```

## Test environment

* AMD Ryzen 9 7900, 1 CPU, 24 logical and 12 physical cores
* Fedora 38
* ```console
  $ vips --targets
  builtin targets:   AVX3_SPR AVX3_ZEN4 AVX3 AVX2 SSE4 SSE2
  supported targets: AVX3_ZEN4 AVX3_DL AVX3 AVX2 SSE4 SSSE3 SSE2
  ```

## JPEG bench

> **Note**: This scenario corresponds to the one outlined on the [Speed and memory use](https://github.com/libvips/libvips/wiki/Speed-and-memory-use) page.

### TL;DR

On this benchmark, the Highway implementation is:
- ~2.5x faster than liborc with one thread;
- 15% faster than liborc with multiple threads.

### Single-threaded

#### liborc

```console
$ VIPS_CONCURRENCY=1 ./bin/vips-microbench-jpeg --benchmark_repetitions=10
2023-08-12T12:17:57+02:00
Running ./bin/vips-microbench-jpeg
Run on (24 X 3700 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.37, 0.15, 0.05
---------------------------------------------------------------------------------------------------
Benchmark                                                         Time             CPU   Iterations
---------------------------------------------------------------------------------------------------
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time              1081 ms         17.0 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time              1083 ms         16.2 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time              1082 ms         17.5 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time              1082 ms         17.2 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time              1083 ms         17.0 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time              1083 ms         17.1 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time              1082 ms         16.8 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time              1072 ms         15.9 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time              1082 ms         17.1 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time              1086 ms         17.0 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time_mean         1082 ms         16.9 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time_median       1082 ms         17.0 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time_stddev       3.65 ms        0.482 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time_cv           0.34 %          2.85 %            10
```

#### Highway

```console
$ VIPS_CONCURRENCY=1 ./bin/vips-microbench-jpeg --benchmark_repetitions=10
2023-08-12T12:15:11+02:00
Running ./bin/vips-microbench-jpeg
Run on (24 X 3700 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.00, 0.00, 0.00
---------------------------------------------------------------------------------------------------
Benchmark                                                         Time             CPU   Iterations
---------------------------------------------------------------------------------------------------
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               447 ms         18.1 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               438 ms         17.5 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               434 ms         17.2 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               435 ms         17.3 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               434 ms         17.2 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               432 ms         17.3 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               435 ms         17.3 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               434 ms         17.3 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               435 ms         17.7 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               433 ms         17.7 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time_mean          436 ms         17.5 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time_median        434 ms         17.3 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time_stddev       4.36 ms        0.274 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time_cv           1.00 %          1.57 %            10
```

### Multi-threaded

#### liborc

```console
$ ./bin/vips-microbench-jpeg --benchmark_repetitions=10
2023-08-12T12:18:25+02:00
Running ./bin/vips-microbench-jpeg
Run on (24 X 3700 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.42, 0.19, 0.07
---------------------------------------------------------------------------------------------------
Benchmark                                                         Time             CPU   Iterations
---------------------------------------------------------------------------------------------------
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               436 ms         24.8 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               426 ms         26.3 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               421 ms         25.3 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               421 ms         25.6 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               415 ms         25.1 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               413 ms         25.2 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               422 ms         25.8 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               413 ms         25.5 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               415 ms         25.6 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               410 ms         25.2 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time_mean          419 ms         25.4 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time_median        418 ms         25.4 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time_stddev       7.77 ms        0.416 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time_cv           1.85 %          1.63 %            10
```

#### Highway

```console
$ ./bin/vips-microbench-jpeg --benchmark_repetitions=10
2023-08-12T12:15:28+02:00
Running ./bin/vips-microbench-jpeg
Run on (24 X 3700 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.13, 0.03, 0.01
---------------------------------------------------------------------------------------------------
Benchmark                                                         Time             CPU   Iterations
---------------------------------------------------------------------------------------------------
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               365 ms         24.4 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               356 ms         23.0 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               352 ms         22.8 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               358 ms         24.7 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               354 ms         24.4 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               350 ms         22.3 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               354 ms         25.0 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               345 ms         24.8 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               350 ms         22.2 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time               347 ms         22.7 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time_mean          353 ms         23.6 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time_median        353 ms         23.7 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time_stddev       5.75 ms         1.12 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/real_time_cv           1.63 %          4.73 %            10
```


## Reduce bench

### TL;DR

On this benchmark, the Highway implementation is:
- ~32% faster than liborc with one thread;
- ~16% faster than liborc with multiple threads.

### Single-threaded

#### liborc

```console
$ VIPS_CONCURRENCY=1 ./bin/vips-microbench-reduce --benchmark_repetitions=10
2023-08-12T12:18:53+02:00
Running ./bin/vips-microbench-reduce
Run on (24 X 3700 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.45, 0.22, 0.08
--------------------------------------------------------------------------------------------------------
Benchmark                                                              Time             CPU   Iterations
--------------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               346 ms         4.61 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               349 ms         5.01 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               350 ms         5.01 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               350 ms         4.89 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               347 ms         4.77 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               348 ms         4.41 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               346 ms         4.42 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               348 ms         5.01 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               350 ms         4.76 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               348 ms         4.58 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_mean          348 ms         4.75 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_median        348 ms         4.77 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_stddev       1.53 ms        0.235 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_cv           0.44 %          4.94 %            10
```

#### Highway

```console
$ VIPS_CONCURRENCY=1 ./bin/vips-microbench-reduce --benchmark_repetitions=10
2023-08-12T12:16:19+02:00
Running ./bin/vips-microbench-reduce
Run on (24 X 3700 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.19, 0.07, 0.02
--------------------------------------------------------------------------------------------------------
Benchmark                                                              Time             CPU   Iterations
--------------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               244 ms         2.14 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               243 ms         2.27 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               235 ms         2.37 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               237 ms         2.46 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               236 ms         2.28 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               235 ms         2.29 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               235 ms         2.30 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               236 ms         2.31 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               235 ms         2.30 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               236 ms         2.26 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_mean          237 ms         2.30 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_median        236 ms         2.29 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_stddev       3.54 ms        0.082 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_cv           1.49 %          3.58 %            10
```

### Multi-threaded

#### liborc

```console
$ ./bin/vips-microbench-reduce --benchmark_repetitions=10
2023-08-12T12:19:16+02:00
Running ./bin/vips-microbench-reduce
Run on (24 X 3700 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.46, 0.23, 0.09
--------------------------------------------------------------------------------------------------------
Benchmark                                                              Time             CPU   Iterations
--------------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               348 ms         8.22 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               344 ms         8.53 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               335 ms         8.14 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               334 ms         9.53 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               327 ms         7.67 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               331 ms         8.71 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               327 ms         7.87 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               337 ms         8.46 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               331 ms         9.29 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               332 ms         8.21 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_mean          335 ms         8.46 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_median        333 ms         8.34 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_stddev       6.78 ms        0.586 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_cv           2.03 %          6.92 %            10
```

#### Highway

```console
$ ./bin/vips-microbench-reduce --benchmark_repetitions=10
2023-08-12T12:16:45+02:00
Running ./bin/vips-microbench-reduce
Run on (24 X 3700 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.18, 0.08, 0.03
--------------------------------------------------------------------------------------------------------
Benchmark                                                              Time             CPU   Iterations
--------------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               296 ms         3.71 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               277 ms         3.41 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               279 ms         3.52 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               276 ms         3.34 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               279 ms         3.15 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               274 ms         3.21 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               279 ms         3.16 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               280 ms         3.19 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               273 ms         3.88 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               279 ms         3.91 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_mean          279 ms         3.45 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_median        279 ms         3.38 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_stddev       6.35 ms        0.294 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_cv           2.27 %          8.54 %            10
```
