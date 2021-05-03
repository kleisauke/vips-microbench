# Experiment with reusing threads

See [libvips/libvips#1492](https://github.com/libvips/libvips/issues/1492).

Tested commits:
- https://github.com/libvips/libvips/commit/1423c550ccd9353cd8f331a1cbe8399041262aa2
- https://github.com/kleisauke/libvips/commit/83575e347a22c35d58f1f2ab16dab9cfb7dfae20

## Thumbnail

TL;DR: ~4% faster when reusing threads on this benchmark.

### Before

```bash
$ ./bin/vips-microbench-thumbnail --benchmark_repetitions=10
2021-05-03T13:53:36+02:00
Running ./bin/vips-microbench-thumbnail
Run on (6 X 4099.95 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 9216 KiB (x1)
Load Average: 1.56, 1.77, 1.42
----------------------------------------------------------------------------------------------
Benchmark                                                    Time             CPU   Iterations
----------------------------------------------------------------------------------------------
BM_jpeg_thumbnail_150x150/original/real_time              9.43 ms         2.84 ms           72
BM_jpeg_thumbnail_150x150/original/real_time              9.50 ms         2.87 ms           72
BM_jpeg_thumbnail_150x150/original/real_time              9.55 ms         2.91 ms           72
BM_jpeg_thumbnail_150x150/original/real_time              9.56 ms         2.91 ms           72
BM_jpeg_thumbnail_150x150/original/real_time              9.54 ms         2.91 ms           72
BM_jpeg_thumbnail_150x150/original/real_time              9.55 ms         2.92 ms           72
BM_jpeg_thumbnail_150x150/original/real_time              9.56 ms         2.91 ms           72
BM_jpeg_thumbnail_150x150/original/real_time              9.60 ms         2.92 ms           72
BM_jpeg_thumbnail_150x150/original/real_time              9.57 ms         2.89 ms           72
BM_jpeg_thumbnail_150x150/original/real_time              9.50 ms         2.86 ms           72
BM_jpeg_thumbnail_150x150/original/real_time_mean         9.54 ms         2.89 ms           10
BM_jpeg_thumbnail_150x150/original/real_time_median       9.55 ms         2.91 ms           10
BM_jpeg_thumbnail_150x150/original/real_time_stddev      0.049 ms        0.026 ms           10
BM_jpeg_thumbnail_150x150/strip/real_time                 7.94 ms         2.29 ms           88
BM_jpeg_thumbnail_150x150/strip/real_time                 7.95 ms         2.29 ms           88
BM_jpeg_thumbnail_150x150/strip/real_time                 7.90 ms         2.26 ms           88
BM_jpeg_thumbnail_150x150/strip/real_time                 7.90 ms         2.26 ms           88
BM_jpeg_thumbnail_150x150/strip/real_time                 7.90 ms         2.26 ms           88
BM_jpeg_thumbnail_150x150/strip/real_time                 7.90 ms         2.26 ms           88
BM_jpeg_thumbnail_150x150/strip/real_time                 7.91 ms         2.27 ms           88
BM_jpeg_thumbnail_150x150/strip/real_time                 7.91 ms         2.27 ms           88
BM_jpeg_thumbnail_150x150/strip/real_time                 7.91 ms         2.27 ms           88
BM_jpeg_thumbnail_150x150/strip/real_time                 7.86 ms         2.26 ms           88
BM_jpeg_thumbnail_150x150/strip/real_time_mean            7.91 ms         2.27 ms           10
BM_jpeg_thumbnail_150x150/strip/real_time_median          7.90 ms         2.27 ms           10
BM_jpeg_thumbnail_150x150/strip/real_time_stddev         0.026 ms        0.012 ms           10
```

### After

```bash
$ ./bin/vips-microbench-thumbnail --benchmark_repetitions=10
2021-05-03T13:43:01+02:00
Running ./bin/vips-microbench-thumbnail
Run on (6 X 4100 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 9216 KiB (x1)
Load Average: 0.71, 1.03, 1.06
----------------------------------------------------------------------------------------------
Benchmark                                                    Time             CPU   Iterations
----------------------------------------------------------------------------------------------
BM_jpeg_thumbnail_150x150/original/real_time              9.11 ms         2.48 ms           73
BM_jpeg_thumbnail_150x150/original/real_time              9.13 ms         2.48 ms           73
BM_jpeg_thumbnail_150x150/original/real_time              9.14 ms         2.48 ms           73
BM_jpeg_thumbnail_150x150/original/real_time              9.14 ms         2.48 ms           73
BM_jpeg_thumbnail_150x150/original/real_time              9.16 ms         2.48 ms           73
BM_jpeg_thumbnail_150x150/original/real_time              9.17 ms         2.49 ms           73
BM_jpeg_thumbnail_150x150/original/real_time              9.16 ms         2.48 ms           73
BM_jpeg_thumbnail_150x150/original/real_time              9.16 ms         2.48 ms           73
BM_jpeg_thumbnail_150x150/original/real_time              9.18 ms         2.48 ms           73
BM_jpeg_thumbnail_150x150/original/real_time              9.18 ms         2.48 ms           73
BM_jpeg_thumbnail_150x150/original/real_time_mean         9.15 ms         2.48 ms           10
BM_jpeg_thumbnail_150x150/original/real_time_median       9.16 ms         2.48 ms           10
BM_jpeg_thumbnail_150x150/original/real_time_stddev      0.021 ms        0.002 ms           10
BM_jpeg_thumbnail_150x150/strip/real_time                 7.61 ms         1.92 ms           91
BM_jpeg_thumbnail_150x150/strip/real_time                 7.59 ms         1.91 ms           91
BM_jpeg_thumbnail_150x150/strip/real_time                 7.61 ms         1.92 ms           91
BM_jpeg_thumbnail_150x150/strip/real_time                 7.60 ms         1.91 ms           91
BM_jpeg_thumbnail_150x150/strip/real_time                 7.59 ms         1.91 ms           91
BM_jpeg_thumbnail_150x150/strip/real_time                 7.58 ms         1.91 ms           91
BM_jpeg_thumbnail_150x150/strip/real_time                 7.58 ms         1.91 ms           91
BM_jpeg_thumbnail_150x150/strip/real_time                 7.58 ms         1.91 ms           91
BM_jpeg_thumbnail_150x150/strip/real_time                 7.58 ms         1.91 ms           91
BM_jpeg_thumbnail_150x150/strip/real_time                 7.58 ms         1.91 ms           91
BM_jpeg_thumbnail_150x150/strip/real_time_mean            7.59 ms         1.91 ms           10
BM_jpeg_thumbnail_150x150/strip/real_time_median          7.59 ms         1.91 ms           10
BM_jpeg_thumbnail_150x150/strip/real_time_stddev         0.014 ms        0.003 ms           10
```

## Reduce

TL;DR: ~15% faster when reusing threads on this benchmark.

### Before

```bash
$ ./bin/vips-microbench-reduce --benchmark_repetitions=10
2021-05-03T14:03:25+02:00
Running ./bin/vips-microbench-reduce
Run on (6 X 4100.25 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 9216 KiB (x1)
Load Average: 1.44, 1.60, 1.44
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               427 ms         12.4 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               464 ms         13.6 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               459 ms         15.9 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               445 ms         14.9 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               472 ms         16.6 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               465 ms         16.3 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               466 ms         16.8 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               452 ms         15.4 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               465 ms         16.1 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               441 ms         14.2 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_mean          456 ms         15.2 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_median        461 ms         15.6 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_stddev       14.0 ms         1.43 ms           10
```

### After

```bash
$ ./bin/vips-microbench-reduce --benchmark_repetitions=10
2021-05-03T13:44:15+02:00
Running ./bin/vips-microbench-reduce
Run on (6 X 4099.94 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 9216 KiB (x1)
Load Average: 0.80, 1.00, 1.05
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               393 ms         4.84 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               393 ms         5.46 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               416 ms         5.04 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               411 ms         5.60 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               402 ms         5.21 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               375 ms         4.14 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               382 ms         3.83 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               386 ms         3.85 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               388 ms         3.86 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               386 ms         3.83 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_mean          393 ms         4.57 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_median        390 ms         4.49 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_stddev       12.9 ms        0.734 ms           10
```

## Crop / shrink / sharpen

TL;DR: No significant difference on this benchmark.

### Before

```bash
$ ./bin/vips-microbench-jpeg --benchmark_repetitions=10
2021-05-03T14:02:22+02:00
Running ./bin/vips-microbench-jpeg
Run on (6 X 4100.1 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 9216 KiB (x1)
Load Average: 2.48, 1.74, 1.47
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               169 ms         7.68 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               168 ms         7.87 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               169 ms         7.71 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               168 ms         7.73 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               168 ms         7.57 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               169 ms         7.69 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               168 ms         7.61 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               168 ms         7.69 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               168 ms         7.61 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               168 ms         7.79 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time_mean          168 ms         7.70 ms           10
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time_median        168 ms         7.69 ms           10
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time_stddev      0.544 ms        0.088 ms           10
```

### After

```bash
$ ./bin/vips-microbench-jpeg --benchmark_repetitions=10
2021-05-03T13:46:37+02:00
Running ./bin/vips-microbench-jpeg
Run on (6 X 4100.45 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 9216 KiB (x1)
Load Average: 2.50, 1.43, 1.19
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               168 ms         6.80 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               167 ms         6.79 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               167 ms         6.74 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               167 ms         6.65 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               166 ms         6.62 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               167 ms         6.67 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               167 ms         6.50 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               166 ms         6.73 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               167 ms         6.80 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time               167 ms         6.72 ms            4
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time_mean          167 ms         6.70 ms           10
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time_median        167 ms         6.72 ms           10
BM_jpeg_crop_shrink_sharpen/5000x5000/real_time_stddev      0.622 ms        0.095 ms           10
```
