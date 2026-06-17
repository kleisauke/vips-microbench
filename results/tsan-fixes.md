# Assorted ThreadSanitizer fixes

See: https://github.com/libvips/libvips/compare/master...kleisauke:tsan-fixes.

Context: https://github.com/libvips/libvips/pull/4981.

## Test image

```console
$ vipsheader images/x.jpg
images/x.jpg: 10000x10000 uchar, 3 bands, srgb, jpegload
```

## Test environment

* AMD Ryzen 9 7900, 1 CPU, 24 logical and 12 physical cores
* Fedora 44
* ```console
  $ vips --targets
  builtin targets:   AVX3_DL AVX3 AVX2 SSE4 SSE2
  supported targets: AVX3_DL AVX3 AVX2 SSE4 SSE2
  ```

## JPEG bench

> [!NOTE]
> This scenario corresponds to the one outlined on the [Speed and memory use](
> https://github.com/libvips/libvips/wiki/Speed-and-memory-use) page.

### TL;DR

No measurable impact on performance on this benchmark.

### Single-threaded

#### `master`

```console
$ VIPS_CONCURRENCY=1 meson test -C build --benchmark jpeg-bench  -v
2026-06-17T11:33:35+02:00
Running ./build/src/jpeg-bench
Run on (24 X 4357.31 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 2.15, 1.50, 0.96
--------------------------------------------------------------------------------------------------------------
Benchmark                                                                    Time             CPU   Iterations
--------------------------------------------------------------------------------------------------------------
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               542 ms         46.3 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               520 ms         40.6 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               527 ms         39.9 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               516 ms         37.6 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               515 ms         38.7 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               507 ms         37.7 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               509 ms         36.3 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               529 ms         38.1 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               513 ms         37.4 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               519 ms         39.5 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_mean          520 ms         39.2 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_median        517 ms         38.4 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_stddev       10.6 ms         2.80 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_cv           2.04 %          7.14 %            10
```

#### `tsan-fixes`

```console
$ VIPS_CONCURRENCY=1 meson test -C build --benchmark jpeg-bench  -v
2026-06-17T11:28:03+02:00
Running ./build/src/jpeg-bench
Run on (24 X 3007.06 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.93, 1.12, 0.67
--------------------------------------------------------------------------------------------------------------
Benchmark                                                                    Time             CPU   Iterations
--------------------------------------------------------------------------------------------------------------
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               535 ms         47.4 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               529 ms         40.1 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               529 ms         39.4 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               517 ms         37.0 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               508 ms         36.6 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               503 ms         37.1 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               518 ms         36.2 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               508 ms         38.4 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               522 ms         38.9 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               512 ms         38.3 ms            1
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_mean          518 ms         38.9 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_median        518 ms         38.3 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_stddev       10.7 ms         3.24 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_cv           2.07 %          8.31 %            10
```

### Multi-threaded

#### `master`

```console
$ meson test -C build --benchmark jpeg-bench  -v
2026-06-17T11:34:26+02:00
Running ./build/src/jpeg-bench
Run on (24 X 5421.93 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 1.20, 1.36, 0.94
--------------------------------------------------------------------------------------------------------------
Benchmark                                                                    Time             CPU   Iterations
--------------------------------------------------------------------------------------------------------------
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               447 ms         49.0 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               440 ms         48.3 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               429 ms         44.7 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               418 ms         47.3 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               413 ms         44.9 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               415 ms         46.5 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               410 ms         46.6 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               419 ms         46.4 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               424 ms         47.1 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               427 ms         49.6 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_mean          424 ms         47.0 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_median        421 ms         46.8 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_stddev       11.9 ms         1.59 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_cv           2.81 %          3.38 %            10
```

#### `tsan-fixes`

```console
$ meson test -C build --benchmark jpeg-bench  -v
2026-06-17T11:28:30+02:00
Running ./build/src/jpeg-bench
Run on (24 X 3007.06 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 1.09, 1.14, 0.69
--------------------------------------------------------------------------------------------------------------
Benchmark                                                                    Time             CPU   Iterations
--------------------------------------------------------------------------------------------------------------
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               429 ms         49.8 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               437 ms         49.4 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               427 ms         45.5 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               425 ms         46.1 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               422 ms         47.1 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               422 ms         45.6 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               424 ms         44.7 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               411 ms         47.2 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               416 ms         46.7 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               422 ms         48.1 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_mean          424 ms         47.0 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_median        423 ms         46.9 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_stddev       7.11 ms         1.67 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_cv           1.68 %          3.55 %            10
```

## Shrink bench

### TL;DR

No measurable impact on performance on this benchmark.

### Single-threaded

#### `master`

```console
$ VIPS_CONCURRENCY=1 meson test -C build --benchmark shrink-bench -v
2026-06-17T11:35:12+02:00
Running ./build/src/shrink-bench
Run on (24 X 5449.85 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.84, 1.23, 0.92
----------------------------------------------------------------------------------------------------------
Benchmark                                                                Time             CPU   Iterations
----------------------------------------------------------------------------------------------------------
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               208 ms         2.62 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               209 ms         3.29 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               207 ms         2.31 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               204 ms         3.05 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               208 ms         2.82 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               207 ms         2.81 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               207 ms         2.36 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               203 ms         2.31 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               203 ms         2.64 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               201 ms         2.48 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_mean          206 ms         2.67 ms           10
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_median        207 ms         2.63 ms           10
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_stddev       2.66 ms        0.328 ms           10
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_cv           1.29 %         12.27 %            10
```

#### `tsan-fixes`

```console
$ VIPS_CONCURRENCY=1 meson test -C build --benchmark shrink-bench -v
2026-06-17T11:29:20+02:00
Running ./build/src/shrink-bench
Run on (24 X 4339.78 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 1.40, 1.24, 0.75
----------------------------------------------------------------------------------------------------------
Benchmark                                                                Time             CPU   Iterations
----------------------------------------------------------------------------------------------------------
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               208 ms         2.08 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               202 ms         2.41 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               203 ms         2.25 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               207 ms         2.82 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               205 ms         2.60 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               207 ms         2.87 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               206 ms         2.43 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               205 ms         2.20 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               205 ms         2.55 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               202 ms         2.23 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_mean          205 ms         2.44 ms           10
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_median        205 ms         2.42 ms           10
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_stddev       2.22 ms        0.267 ms           10
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_cv           1.08 %         10.92 %            10
```

### Multi-threaded

#### `master`

```console
$ meson test -C build --benchmark shrink-bench -v
2026-06-17T11:35:54+02:00
Running ./build/src/shrink-bench
Run on (24 X 5449.61 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.53, 1.10, 0.89
----------------------------------------------------------------------------------------------------------
Benchmark                                                                Time             CPU   Iterations
----------------------------------------------------------------------------------------------------------
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               243 ms         4.71 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               236 ms         4.67 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               232 ms         3.93 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               231 ms         3.03 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               234 ms         3.79 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               229 ms         3.21 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               238 ms         5.19 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               237 ms         4.54 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               235 ms         4.27 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               231 ms         3.60 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_mean          235 ms         4.09 ms           10
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_median        235 ms         4.10 ms           10
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_stddev       4.12 ms        0.701 ms           10
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_cv           1.76 %         17.13 %            10
```

#### `tsan-fixes`

```console
$ meson test -C build --benchmark shrink-bench -v
2026-06-17T11:30:11+02:00
Running ./build/src/shrink-bench
Run on (24 X 3007.06 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 1.11, 1.18, 0.76
----------------------------------------------------------------------------------------------------------
Benchmark                                                                Time             CPU   Iterations
----------------------------------------------------------------------------------------------------------
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               250 ms         5.08 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               243 ms         4.06 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               239 ms         3.78 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               238 ms         2.93 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               238 ms         3.18 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               233 ms         3.40 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               234 ms         3.39 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               237 ms         3.73 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               236 ms         3.33 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               244 ms         5.72 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_mean          239 ms         3.86 ms           10
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_median        238 ms         3.56 ms           10
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_stddev       5.30 ms        0.884 ms           10
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_cv           2.21 %         22.92 %            10
```

## Reduce (with `gap=2.0`) bench

### TL;DR

No measurable impact on performance on this benchmark.

### Single-threaded

#### `master`

```console
$ VIPS_CONCURRENCY=1 meson test -C build --benchmark reduce-bench -v
2026-06-17T11:36:31+02:00
Running ./build/src/reduce-bench
Run on (24 X 4360.29 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.34, 0.99, 0.86
-------------------------------------------------------------------------------------------------------------------
Benchmark                                                                         Time             CPU   Iterations
-------------------------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               239 ms         4.57 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               235 ms         5.02 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               232 ms         4.23 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               233 ms         3.92 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               232 ms         4.51 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               232 ms         4.05 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               232 ms         4.02 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               228 ms         3.53 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               232 ms         4.55 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               227 ms         3.65 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_mean          232 ms         4.21 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_median        232 ms         4.14 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_stddev       3.26 ms        0.459 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_cv           1.40 %         10.92 %            10
```

#### `tsan-fixes`

```console
$ VIPS_CONCURRENCY=1 meson test -C build --benchmark reduce-bench -v
2026-06-17T11:31:17+02:00
Running ./build/src/reduce-bench
Run on (24 X 5406.67 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 1.58, 1.29, 0.83
-------------------------------------------------------------------------------------------------------------------
Benchmark                                                                         Time             CPU   Iterations
-------------------------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               236 ms         4.23 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               232 ms         3.96 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               234 ms         4.17 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               229 ms         3.25 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               230 ms         4.24 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               229 ms         3.65 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               228 ms         4.04 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               230 ms         4.28 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               233 ms         4.14 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               228 ms         4.22 ms            3
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_mean          231 ms         4.02 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_median        230 ms         4.15 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_stddev       2.62 ms        0.326 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_cv           1.13 %          8.12 %            10
```

### Multi-threaded

#### `master`

```console
$ meson test -C build --benchmark reduce-bench -v
2026-06-17T11:37:28+02:00
Running ./build/src/reduce-bench
Run on (24 X 5449.87 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.25, 0.85, 0.82
-------------------------------------------------------------------------------------------------------------------
Benchmark                                                                         Time             CPU   Iterations
-------------------------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               292 ms         5.80 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               287 ms         6.62 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               278 ms         6.47 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               278 ms         6.00 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               279 ms         7.19 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               269 ms         7.34 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               265 ms         6.59 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               263 ms         5.18 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               267 ms         5.37 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               265 ms         6.29 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_mean          274 ms         6.29 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_median        273 ms         6.38 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_stddev       10.2 ms        0.711 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_cv           3.70 %         11.31 %            10
```

#### `tsan-fixes`

```console
$ meson test -C build --benchmark reduce-bench -v
2026-06-17T11:31:57+02:00
Running ./build/src/reduce-bench
Run on (24 X 5449.53 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 1.15, 1.22, 0.82
-------------------------------------------------------------------------------------------------------------------
Benchmark                                                                         Time             CPU   Iterations
-------------------------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               280 ms         5.43 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               271 ms         5.71 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               266 ms         3.61 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               264 ms         6.67 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               279 ms         4.45 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               268 ms         7.77 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               269 ms         6.91 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               273 ms         4.86 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               276 ms         5.50 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               275 ms         6.99 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_mean          272 ms         5.79 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_median        272 ms         5.61 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_stddev       5.30 ms         1.29 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_cv           1.95 %         22.31 %            10
```
