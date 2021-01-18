# Experiment with SIMD intrinsics

See https://github.com/kleisauke/libvips/tree/simd.

## Reduce

TL;DR: ~35% faster when using SIMD intrinsics on this benchmark.

### Before

```bash
$ ./bin/vips-microbench-reduce --benchmark_repetitions=10
2021-01-18T16:35:56+01:00
Running ./bin/vips-microbench-reduce
Run on (6 X 4300 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 9216 KiB (x1)
Load Average: 2.33, 2.08, 1.49
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BM_vips_reduce_lanczos3_150x150/strip/real_time               126 ms         6.59 ms            6
BM_vips_reduce_lanczos3_150x150/strip/real_time               125 ms         6.41 ms            6
BM_vips_reduce_lanczos3_150x150/strip/real_time               124 ms         6.14 ms            6
BM_vips_reduce_lanczos3_150x150/strip/real_time               126 ms         6.60 ms            6
BM_vips_reduce_lanczos3_150x150/strip/real_time               126 ms         6.63 ms            6
BM_vips_reduce_lanczos3_150x150/strip/real_time               126 ms         6.44 ms            6
BM_vips_reduce_lanczos3_150x150/strip/real_time               125 ms         6.81 ms            6
BM_vips_reduce_lanczos3_150x150/strip/real_time               126 ms         6.64 ms            6
BM_vips_reduce_lanczos3_150x150/strip/real_time               123 ms         5.72 ms            6
BM_vips_reduce_lanczos3_150x150/strip/real_time               126 ms         6.19 ms            6
BM_vips_reduce_lanczos3_150x150/strip/real_time_mean          125 ms         6.42 ms           10
BM_vips_reduce_lanczos3_150x150/strip/real_time_median        126 ms         6.51 ms           10
BM_vips_reduce_lanczos3_150x150/strip/real_time_stddev       1.13 ms        0.320 ms           10
```

### After

```bash
$ ./bin/vips-microbench-reduce --benchmark_repetitions=10
2021-01-18T16:32:20+01:00
Running ./bin/vips-microbench-reduce
Run on (6 X 4300 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 9216 KiB (x1)
Load Average: 1.59, 1.79, 1.27
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BM_vips_reduce_lanczos3_150x150/strip/real_time              83.4 ms         6.62 ms            8
BM_vips_reduce_lanczos3_150x150/strip/real_time              83.0 ms         6.63 ms            8
BM_vips_reduce_lanczos3_150x150/strip/real_time              83.2 ms         6.83 ms            8
BM_vips_reduce_lanczos3_150x150/strip/real_time              83.8 ms         6.83 ms            8
BM_vips_reduce_lanczos3_150x150/strip/real_time              83.0 ms         6.49 ms            8
BM_vips_reduce_lanczos3_150x150/strip/real_time              82.8 ms         6.49 ms            8
BM_vips_reduce_lanczos3_150x150/strip/real_time              84.1 ms         7.17 ms            8
BM_vips_reduce_lanczos3_150x150/strip/real_time              82.7 ms         6.61 ms            8
BM_vips_reduce_lanczos3_150x150/strip/real_time              82.9 ms         6.47 ms            8
BM_vips_reduce_lanczos3_150x150/strip/real_time              82.9 ms         6.02 ms            8
BM_vips_reduce_lanczos3_150x150/strip/real_time_mean         83.2 ms         6.62 ms           10
BM_vips_reduce_lanczos3_150x150/strip/real_time_median       83.0 ms         6.61 ms           10
BM_vips_reduce_lanczos3_150x150/strip/real_time_stddev      0.449 ms        0.301 ms           10
```
