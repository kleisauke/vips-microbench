# Improve performance of shrink{h,v} using Highway

See https://github.com/kleisauke/libvips/tree/shrink-highway.

## Test image
```console
$ vipsheader images/x.jpg
images/x.jpg: 10000x10000 uchar, 3 bands, srgb, jpegload
```

## Test environment

* AMD Ryzen 9 7900, 1 CPU, 24 logical and 12 physical cores
* Fedora 41
* ```console
  $ vips --targets
  builtin targets:   AVX3_SPR AVX3_ZEN4 AVX3 AVX2 SSE4 SSE2
  supported targets: AVX3_ZEN4 AVX3_DL AVX3 AVX2 SSE4 SSSE3 SSE2
  ```

## Shrink bench

### TL;DR

On this benchmark, the Highway implementation is:
- ~28% faster than master with one thread;
- ~25% faster than master with multiple threads.

### Single-threaded

#### `master`

```console
$ VIPS_CONCURRENCY=1 ./bin/vips-microbench-shrink --benchmark_repetitions=10
2025-02-10T12:41:31+01:00
Running ./bin/vips-microbench-shrink
Run on (24 X 400 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 1.85, 1.24, 1.32
-----------------------------------------------------------------------------------------------
Benchmark                                                     Time             CPU   Iterations
-----------------------------------------------------------------------------------------------
BM_jpeg_shrink_factor_8/10000x10000/real_time               290 ms         1.87 ms            2
BM_jpeg_shrink_factor_8/10000x10000/real_time               284 ms         1.81 ms            2
BM_jpeg_shrink_factor_8/10000x10000/real_time               287 ms         1.82 ms            2
BM_jpeg_shrink_factor_8/10000x10000/real_time               281 ms         2.58 ms            2
BM_jpeg_shrink_factor_8/10000x10000/real_time               279 ms         1.73 ms            2
BM_jpeg_shrink_factor_8/10000x10000/real_time               278 ms         2.50 ms            2
BM_jpeg_shrink_factor_8/10000x10000/real_time               278 ms         1.88 ms            2
BM_jpeg_shrink_factor_8/10000x10000/real_time               277 ms         2.58 ms            2
BM_jpeg_shrink_factor_8/10000x10000/real_time               279 ms         1.73 ms            2
BM_jpeg_shrink_factor_8/10000x10000/real_time               277 ms         2.60 ms            2
BM_jpeg_shrink_factor_8/10000x10000/real_time_mean          281 ms         2.11 ms           10
BM_jpeg_shrink_factor_8/10000x10000/real_time_median        279 ms         1.88 ms           10
BM_jpeg_shrink_factor_8/10000x10000/real_time_stddev       4.49 ms        0.395 ms           10
BM_jpeg_shrink_factor_8/10000x10000/real_time_cv           1.60 %         18.72 %            10
```

#### `shrink-highway`

```console
$ VIPS_CONCURRENCY=1 ./bin/vips-microbench-shrink --benchmark_repetitions=10
2025-02-10T12:44:35+01:00
Running ./bin/vips-microbench-shrink
Run on (24 X 5447.84 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.49, 0.90, 1.17
-----------------------------------------------------------------------------------------------
Benchmark                                                     Time             CPU   Iterations
-----------------------------------------------------------------------------------------------
BM_jpeg_shrink_factor_8/10000x10000/real_time               208 ms         1.85 ms            3
BM_jpeg_shrink_factor_8/10000x10000/real_time               204 ms         1.85 ms            3
BM_jpeg_shrink_factor_8/10000x10000/real_time               201 ms         1.93 ms            3
BM_jpeg_shrink_factor_8/10000x10000/real_time               202 ms         1.93 ms            3
BM_jpeg_shrink_factor_8/10000x10000/real_time               198 ms         2.41 ms            3
BM_jpeg_shrink_factor_8/10000x10000/real_time               204 ms         2.02 ms            3
BM_jpeg_shrink_factor_8/10000x10000/real_time               201 ms         2.02 ms            3
BM_jpeg_shrink_factor_8/10000x10000/real_time               204 ms         2.48 ms            3
BM_jpeg_shrink_factor_8/10000x10000/real_time               199 ms         1.89 ms            3
BM_jpeg_shrink_factor_8/10000x10000/real_time               198 ms         1.96 ms            3
BM_jpeg_shrink_factor_8/10000x10000/real_time_mean          202 ms         2.03 ms           10
BM_jpeg_shrink_factor_8/10000x10000/real_time_median        202 ms         1.95 ms           10
BM_jpeg_shrink_factor_8/10000x10000/real_time_stddev       2.95 ms        0.226 ms           10
BM_jpeg_shrink_factor_8/10000x10000/real_time_cv           1.46 %         11.13 %            10
```

### Multi-threaded

#### `master`

```console
$ ./bin/vips-microbench-shrink --benchmark_repetitions=10
2025-02-10T12:42:43+01:00
Running ./bin/vips-microbench-shrink
Run on (24 X 400 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 1.00, 1.11, 1.26
-----------------------------------------------------------------------------------------------
Benchmark                                                     Time             CPU   Iterations
-----------------------------------------------------------------------------------------------
BM_jpeg_shrink_factor_8/10000x10000/real_time               313 ms         4.75 ms            2
BM_jpeg_shrink_factor_8/10000x10000/real_time               311 ms         4.41 ms            2
BM_jpeg_shrink_factor_8/10000x10000/real_time               310 ms         3.00 ms            2
BM_jpeg_shrink_factor_8/10000x10000/real_time               304 ms         3.82 ms            2
BM_jpeg_shrink_factor_8/10000x10000/real_time               299 ms         5.09 ms            2
BM_jpeg_shrink_factor_8/10000x10000/real_time               298 ms         3.80 ms            2
BM_jpeg_shrink_factor_8/10000x10000/real_time               299 ms         4.03 ms            2
BM_jpeg_shrink_factor_8/10000x10000/real_time               303 ms         2.80 ms            2
BM_jpeg_shrink_factor_8/10000x10000/real_time               297 ms         3.95 ms            2
BM_jpeg_shrink_factor_8/10000x10000/real_time               307 ms         5.16 ms            2
BM_jpeg_shrink_factor_8/10000x10000/real_time_mean          304 ms         4.08 ms           10
BM_jpeg_shrink_factor_8/10000x10000/real_time_median        303 ms         3.99 ms           10
BM_jpeg_shrink_factor_8/10000x10000/real_time_stddev       5.89 ms        0.797 ms           10
BM_jpeg_shrink_factor_8/10000x10000/real_time_cv           1.94 %         19.54 %            10
```

#### `shrink-highway`

```console
$ ./bin/vips-microbench-shrink --benchmark_repetitions=10
2025-02-10T12:45:07+01:00
Running ./bin/vips-microbench-shrink
Run on (24 X 400 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.35, 0.83, 1.13
-----------------------------------------------------------------------------------------------
Benchmark                                                     Time             CPU   Iterations
-----------------------------------------------------------------------------------------------
BM_jpeg_shrink_factor_8/10000x10000/real_time               237 ms         3.55 ms            3
BM_jpeg_shrink_factor_8/10000x10000/real_time               228 ms         2.87 ms            3
BM_jpeg_shrink_factor_8/10000x10000/real_time               224 ms         2.75 ms            3
BM_jpeg_shrink_factor_8/10000x10000/real_time               224 ms         2.84 ms            3
BM_jpeg_shrink_factor_8/10000x10000/real_time               224 ms         3.05 ms            3
BM_jpeg_shrink_factor_8/10000x10000/real_time               222 ms         2.88 ms            3
BM_jpeg_shrink_factor_8/10000x10000/real_time               232 ms         2.58 ms            3
BM_jpeg_shrink_factor_8/10000x10000/real_time               231 ms         2.86 ms            3
BM_jpeg_shrink_factor_8/10000x10000/real_time               228 ms         3.52 ms            3
BM_jpeg_shrink_factor_8/10000x10000/real_time               222 ms         2.66 ms            3
BM_jpeg_shrink_factor_8/10000x10000/real_time_mean          227 ms         2.96 ms           10
BM_jpeg_shrink_factor_8/10000x10000/real_time_median        226 ms         2.87 ms           10
BM_jpeg_shrink_factor_8/10000x10000/real_time_stddev       5.03 ms        0.331 ms           10
BM_jpeg_shrink_factor_8/10000x10000/real_time_cv           2.21 %         11.19 %            10
```

## Reduce (with `gap=2.0`) bench

### TL;DR

On this benchmark, the Highway implementation is:
- ~32% faster than master with one thread;
- ~28% faster than master with multiple threads.

### Single-threaded

#### `master`

```console
$ VIPS_CONCURRENCY=1 ./bin/vips-microbench-reduce --benchmark_repetitions=10
2025-02-10T12:43:13+01:00
Running ./bin/vips-microbench-reduce
Run on (24 X 400 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.79, 1.05, 1.24
--------------------------------------------------------------------------------------------------------
Benchmark                                                              Time             CPU   Iterations
--------------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               326 ms         2.16 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               321 ms         3.01 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               327 ms         3.32 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               326 ms         3.21 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               329 ms         3.55 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               327 ms         2.22 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               338 ms         2.27 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               318 ms         4.17 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               329 ms         2.12 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               326 ms         2.12 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_mean          327 ms         2.81 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_median        326 ms         2.64 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_stddev       5.49 ms        0.737 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_cv           1.68 %         26.19 %            10
```

#### `shrink-highway`

```console
$ VIPS_CONCURRENCY=1 ./bin/vips-microbench-reduce --benchmark_repetitions=10
2025-02-10T12:46:01+01:00
Running ./bin/vips-microbench-reduce
Run on (24 X 5449.35 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.31, 0.74, 1.08
--------------------------------------------------------------------------------------------------------
Benchmark                                                              Time             CPU   Iterations
--------------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               231 ms         2.21 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               217 ms         2.85 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               226 ms         2.40 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               220 ms         3.52 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               227 ms         3.03 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               224 ms         3.28 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               221 ms         3.34 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               215 ms         2.85 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               221 ms         3.08 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               222 ms         2.76 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_mean          222 ms         2.93 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_median        222 ms         2.94 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_stddev       4.79 ms        0.411 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_cv           2.15 %         14.01 %            10
```

### Multi-threaded

#### `master`

```console
$ ./bin/vips-microbench-reduce --benchmark_repetitions=10
2025-02-10T12:43:30+01:00
Running ./bin/vips-microbench-reduce
Run on (24 X 400 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.86, 1.05, 1.23
--------------------------------------------------------------------------------------------------------
Benchmark                                                              Time             CPU   Iterations
--------------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               375 ms         5.97 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               368 ms         6.07 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               363 ms         5.80 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               353 ms         6.06 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               367 ms         7.22 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               355 ms         5.58 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               353 ms         5.88 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               363 ms         5.43 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               348 ms         6.28 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               366 ms         6.71 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_mean          361 ms         6.10 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_median        363 ms         6.02 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_stddev       8.57 ms        0.530 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_cv           2.37 %          8.68 %            10
```

#### `shrink-highway`

```console
$ ./bin/vips-microbench-reduce --benchmark_repetitions=10
2025-02-10T12:46:23+01:00
Running ./bin/vips-microbench-reduce
Run on (24 X 4350.66 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.29, 0.70, 1.06
--------------------------------------------------------------------------------------------------------
Benchmark                                                              Time             CPU   Iterations
--------------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               274 ms         5.61 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               273 ms         7.43 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               264 ms         6.82 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               259 ms         6.27 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               256 ms         5.56 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               253 ms         6.50 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               263 ms         5.92 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               250 ms         7.93 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               252 ms         4.96 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time               255 ms         5.84 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_mean          260 ms         6.28 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_median        257 ms         6.09 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_stddev       8.50 ms        0.908 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/real_time_cv           3.27 %         14.44 %            10
```
