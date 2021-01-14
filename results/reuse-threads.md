# Experiment with reusing threads

See [libvips/libvips#1492](https://github.com/libvips/libvips/issues/1492).

## Thumbnail

TL;DR: 3 to 4% faster when reusing threads on this benchmark.

### Before

```bash
$ ./bin/vips-microbench-thumbnail --benchmark_repetitions=10
2021-01-14T13:51:54+01:00
Running ./bin/vips-microbench-thumbnail
Run on (6 X 4300 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 9216 KiB (x1)
Load Average: 1.19, 1.39, 1.04
----------------------------------------------------------------------------------------------
Benchmark                                                    Time             CPU   Iterations
----------------------------------------------------------------------------------------------
BM_jpeg_thumbnail_150x150/original/real_time              9.75 ms         3.03 ms           71
BM_jpeg_thumbnail_150x150/original/real_time              9.78 ms         3.08 ms           71
BM_jpeg_thumbnail_150x150/original/real_time              9.78 ms         3.10 ms           71
BM_jpeg_thumbnail_150x150/original/real_time              9.80 ms         3.11 ms           71
BM_jpeg_thumbnail_150x150/original/real_time              9.84 ms         3.12 ms           71
BM_jpeg_thumbnail_150x150/original/real_time              9.83 ms         3.11 ms           71
BM_jpeg_thumbnail_150x150/original/real_time              9.83 ms         3.12 ms           71
BM_jpeg_thumbnail_150x150/original/real_time              9.83 ms         3.12 ms           71
BM_jpeg_thumbnail_150x150/original/real_time              9.83 ms         3.12 ms           71
BM_jpeg_thumbnail_150x150/original/real_time              9.83 ms         3.12 ms           71
BM_jpeg_thumbnail_150x150/original/real_time_mean         9.81 ms         3.10 ms           10
BM_jpeg_thumbnail_150x150/original/real_time_median       9.83 ms         3.11 ms           10
BM_jpeg_thumbnail_150x150/original/real_time_stddev      0.030 ms        0.028 ms           10
BM_jpeg_thumbnail_150x150/strip/real_time                 8.30 ms         2.70 ms           82
BM_jpeg_thumbnail_150x150/strip/real_time                 8.22 ms         2.62 ms           82
BM_jpeg_thumbnail_150x150/strip/real_time                 8.18 ms         2.59 ms           82
BM_jpeg_thumbnail_150x150/strip/real_time                 8.17 ms         2.57 ms           82
BM_jpeg_thumbnail_150x150/strip/real_time                 8.17 ms         2.57 ms           82
BM_jpeg_thumbnail_150x150/strip/real_time                 8.16 ms         2.57 ms           82
BM_jpeg_thumbnail_150x150/strip/real_time                 8.17 ms         2.58 ms           82
BM_jpeg_thumbnail_150x150/strip/real_time                 8.17 ms         2.57 ms           82
BM_jpeg_thumbnail_150x150/strip/real_time                 8.17 ms         2.57 ms           82
BM_jpeg_thumbnail_150x150/strip/real_time                 8.20 ms         2.59 ms           82
BM_jpeg_thumbnail_150x150/strip/real_time_mean            8.19 ms         2.59 ms           10
BM_jpeg_thumbnail_150x150/strip/real_time_median          8.17 ms         2.58 ms           10
BM_jpeg_thumbnail_150x150/strip/real_time_stddev         0.042 ms        0.041 ms           10
```

### After

```bash
$ ./bin/vips-microbench-thumbnail --benchmark_repetitions=10
2021-01-14T13:41:55+01:00
Running ./bin/vips-microbench-thumbnail
Run on (6 X 4300 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 9216 KiB (x1)
Load Average: 0.32, 0.36, 0.72
----------------------------------------------------------------------------------------------
Benchmark                                                    Time             CPU   Iterations
----------------------------------------------------------------------------------------------
BM_jpeg_thumbnail_150x150/original/real_time              9.38 ms         2.65 ms           74
BM_jpeg_thumbnail_150x150/original/real_time              9.41 ms         2.71 ms           74
BM_jpeg_thumbnail_150x150/original/real_time              9.43 ms         2.72 ms           74
BM_jpeg_thumbnail_150x150/original/real_time              9.45 ms         2.73 ms           74
BM_jpeg_thumbnail_150x150/original/real_time              9.42 ms         2.72 ms           74
BM_jpeg_thumbnail_150x150/original/real_time              9.44 ms         2.72 ms           74
BM_jpeg_thumbnail_150x150/original/real_time              9.45 ms         2.74 ms           74
BM_jpeg_thumbnail_150x150/original/real_time              9.47 ms         2.75 ms           74
BM_jpeg_thumbnail_150x150/original/real_time              9.46 ms         2.75 ms           74
BM_jpeg_thumbnail_150x150/original/real_time              9.46 ms         2.74 ms           74
BM_jpeg_thumbnail_150x150/original/real_time_mean         9.44 ms         2.72 ms           10
BM_jpeg_thumbnail_150x150/original/real_time_median       9.44 ms         2.72 ms           10
BM_jpeg_thumbnail_150x150/original/real_time_stddev      0.029 ms        0.030 ms           10
BM_jpeg_thumbnail_150x150/strip/real_time                 7.94 ms         2.30 ms           86
BM_jpeg_thumbnail_150x150/strip/real_time                 7.93 ms         2.28 ms           86
BM_jpeg_thumbnail_150x150/strip/real_time                 7.92 ms         2.28 ms           86
BM_jpeg_thumbnail_150x150/strip/real_time                 7.90 ms         2.27 ms           86
BM_jpeg_thumbnail_150x150/strip/real_time                 7.92 ms         2.28 ms           86
BM_jpeg_thumbnail_150x150/strip/real_time                 7.91 ms         2.27 ms           86
BM_jpeg_thumbnail_150x150/strip/real_time                 7.91 ms         2.27 ms           86
BM_jpeg_thumbnail_150x150/strip/real_time                 7.92 ms         2.27 ms           86
BM_jpeg_thumbnail_150x150/strip/real_time                 7.91 ms         2.26 ms           86
BM_jpeg_thumbnail_150x150/strip/real_time                 7.91 ms         2.26 ms           86
BM_jpeg_thumbnail_150x150/strip/real_time_mean            7.92 ms         2.27 ms           10
BM_jpeg_thumbnail_150x150/strip/real_time_median          7.92 ms         2.27 ms           10
BM_jpeg_thumbnail_150x150/strip/real_time_stddev         0.012 ms        0.012 ms           10
```

## Reduce

TL;DR: 5% faster when reusing threads on this benchmark.

### Before

```bash
$ ./bin/vips-microbench-reduce --benchmark_repetitions=10
2021-01-14T14:02:55+01:00
Running ./bin/vips-microbench-reduce
Run on (6 X 4300 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 9216 KiB (x1)
Load Average: 1.27, 2.03, 1.47
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               432 ms         7.39 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               429 ms         8.25 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               420 ms         7.65 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               405 ms         6.30 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               405 ms         7.43 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               401 ms         7.16 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               419 ms         8.46 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               416 ms         8.85 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               418 ms         9.29 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               419 ms         9.05 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_mean          417 ms         7.98 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_median        419 ms         7.95 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_stddev       10.1 ms        0.954 ms           10
```

### After

```bash
$ ./bin/vips-microbench-reduce --benchmark_repetitions=10
2021-01-14T13:46:02+01:00
Running ./bin/vips-microbench-reduce
Run on (6 X 4300 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 9216 KiB (x1)
Load Average: 0.39, 0.49, 0.70
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               395 ms         3.65 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               413 ms         3.67 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               407 ms         3.69 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               400 ms         3.73 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               389 ms         4.17 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               396 ms         4.12 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               392 ms         4.26 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               386 ms         3.86 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               409 ms         4.43 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               418 ms         4.13 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_mean          401 ms         3.97 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_median        398 ms         3.99 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_stddev       10.7 ms        0.282 ms           10
```

## Crop / shrink / sharpen

TL;DR: No significant difference on this benchmark.

### Before

```bash
$ ./bin/vips-microbench-jpeg --benchmark_repetitions=10
2021-01-14T14:34:20+01:00
Running ./bin/vips-microbench-jpeg
Run on (6 X 4300 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 9216 KiB (x1)
Load Average: 1.86, 0.98, 0.75
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               170 ms         7.92 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               170 ms         7.93 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               170 ms         7.87 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               170 ms         7.91 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               170 ms         8.00 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               171 ms         7.87 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               170 ms         7.98 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               170 ms         7.96 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               170 ms         7.98 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               171 ms         7.81 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time_mean          170 ms         7.92 ms           10
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time_median        170 ms         7.92 ms           10
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time_stddev      0.458 ms        0.060 ms           10
```

### After

```bash
$ ./bin/vips-microbench-jpeg --benchmark_repetitions=10
2021-01-14T14:44:27+01:00
Running ./bin/vips-microbench-jpeg
Run on (6 X 4300 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 9216 KiB (x1)
Load Average: 1.93, 1.55, 1.15
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               170 ms         6.92 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               168 ms         6.73 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               169 ms         6.72 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               168 ms         6.73 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               168 ms         6.74 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               169 ms         6.74 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               168 ms         6.63 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               170 ms         6.78 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               168 ms         6.81 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               167 ms         6.74 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time_mean          169 ms         6.75 ms           10
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time_median        168 ms         6.74 ms           10
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time_stddev      0.832 ms        0.073 ms           10
```
