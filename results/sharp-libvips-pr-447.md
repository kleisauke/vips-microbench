# Optimise all C/C++ dependencies for binary size (-Os)

See PR https://github.com/lovell/sharp-libvips/pull/447.

## Test image

```console
$ vipsheader images/x.jpg
images/x.jpg: 10000x10000 uchar, 3 bands, srgb, jpegload
```

## Test environment

* AMD Ryzen 9 7900, 1 CPU, 24 logical and 12 physical cores
* Fedora 45
* ```console
  $ vips --targets
  builtin targets:   AVX3_DL AVX3 AVX2 SSE4 SSE2
  supported targets: AVX3_DL AVX3 AVX2 SSE4 SSE2
  ```

## Test setup

```shell
# Installation prefix
export LIBVIPS_PREFIX=$HOME/sharp-libvips

# Setup pre-built libvips binaries
mkdir -p $LIBVIPS_PREFIX
tar -xzf sharp-libvips-linux-x64.tar.gz -C $LIBVIPS_PREFIX

# Download pkgconfig file
mkdir -p $LIBVIPS_PREFIX/lib/pkgconfig
curl -fsSL https://gist.github.com/kleisauke/8d93635010b371e154275e376272f8d4/raw/vips-cpp.pc \
  -o $LIBVIPS_PREFIX/lib/pkgconfig/vips-cpp.pc

# Update the PKG_CONFIG_PATH environment variable,
# since libvips is installed in a non-standard prefix
export PKG_CONFIG_PATH=$LIBVIPS_PREFIX/lib/pkgconfig

# Ensure dynamic linker finds the pre-built libvips binaries
export LD_LIBRARY_PATH=$LIBVIPS_PREFIX/lib

pkg-config --exists --print-errors "vips-cpp >= 8.18.7" && echo OK
```

## JPEG bench

> [!NOTE]
> This scenario corresponds to the one outlined on the [Speed and memory use](
> https://github.com/libvips/libvips/wiki/Speed-and-memory-use) page.

### TL;DR

No measurable impact on performance on this benchmark.

#### `main`

```console
$ meson test -C build --benchmark jpeg-bench  -v
2026-11-09T12:07:31+01:00
Running ./build/src/jpeg-bench
Run on (24 X 4357.95 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.96, 2.68, 3.28
--------------------------------------------------------------------------------------------------------------
Benchmark                                                                    Time             CPU   Iterations
--------------------------------------------------------------------------------------------------------------
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               465 ms         56.4 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               447 ms         51.5 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               432 ms         49.0 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               433 ms         51.5 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               437 ms         50.8 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               437 ms         52.2 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               440 ms         52.4 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               449 ms         52.3 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               441 ms         50.9 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               436 ms         51.3 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_mean          442 ms         51.8 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_median        439 ms         51.5 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_stddev       9.93 ms         1.88 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_cv           2.25 %          3.62 %            10
```

#### PR #447

```console
$ meson test -C build --benchmark jpeg-bench  -v
2026-11-09T11:56:35+01:00
Running ./build/src/jpeg-bench
Run on (24 X 4124.43 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.94, 2.94, 3.72
--------------------------------------------------------------------------------------------------------------
Benchmark                                                                    Time             CPU   Iterations
--------------------------------------------------------------------------------------------------------------
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               459 ms         51.6 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               452 ms         48.8 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               438 ms         52.2 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               453 ms         51.9 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               431 ms         49.7 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               435 ms         49.2 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               427 ms         50.9 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               437 ms         52.8 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               435 ms         49.9 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time               443 ms         50.2 ms            2
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_mean          441 ms         50.7 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_median        437 ms         50.5 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_stddev       10.6 ms         1.36 ms           10
BM_jpeg_crop_shrink_sharpen/10000x10000/repeats:10/real_time_cv           2.41 %          2.69 %            10
```

## Shrink bench

### TL;DR

No measurable impact on performance on this benchmark.

#### `main`

```console
$ meson test -C build --benchmark shrink-bench -v
026-11-09T12:08:11+01:00
Running ./build/src/shrink-bench
Run on (24 X 4360.14 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 1.01, 2.50, 3.19
----------------------------------------------------------------------------------------------------------
Benchmark                                                                Time             CPU   Iterations
----------------------------------------------------------------------------------------------------------
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               252 ms         2.23 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               253 ms         4.78 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               248 ms         3.33 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               243 ms         3.45 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               245 ms         3.28 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               241 ms         2.18 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               240 ms         2.50 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               237 ms         3.57 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               246 ms         5.07 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               246 ms         4.06 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_mean          245 ms         3.45 ms           10
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_median        246 ms         3.39 ms           10
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_stddev       4.98 ms        0.991 ms           10
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_cv           2.03 %         28.77 %            10
```

#### PR #447

```console
$ meson test -C build --benchmark shrink-bench -v
2026-11-09T11:57:41+01:00
Running ./build/src/shrink-bench
Run on (24 X 3838.07 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.47, 2.42, 3.49
----------------------------------------------------------------------------------------------------------
Benchmark                                                                Time             CPU   Iterations
----------------------------------------------------------------------------------------------------------
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               257 ms         4.80 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               250 ms         3.08 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               253 ms         4.00 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               253 ms         4.68 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               244 ms         2.98 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               251 ms         5.22 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               246 ms         4.16 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               249 ms         2.86 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               247 ms         2.87 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time               241 ms         3.60 ms            3
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_mean          249 ms         3.82 ms           10
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_median        250 ms         3.80 ms           10
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_stddev       4.69 ms        0.878 ms           10
BM_jpeg_shrink_factor_8/10000x10000/repeats:10/real_time_cv           1.88 %         22.96 %            10
```

## Reduce (with `gap=2.0`) bench

### TL;DR

No measurable impact on performance on this benchmark.

#### `main`

```console
$ meson test -C build --benchmark reduce-bench -v
2026-11-09T12:08:42+01:00
Running ./build/src/reduce-bench
Run on (24 X 3007.06 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.66, 2.27, 3.09
-------------------------------------------------------------------------------------------------------------------
Benchmark                                                                         Time             CPU   Iterations
-------------------------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               289 ms         6.64 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               284 ms         6.05 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               266 ms         5.74 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               277 ms         9.40 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               271 ms         5.24 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               273 ms         6.31 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               261 ms         3.96 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               270 ms         7.55 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               267 ms         5.91 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               271 ms         6.18 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_mean          273 ms         6.30 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_median        271 ms         6.12 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_stddev       8.49 ms         1.43 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_cv           3.11 %         22.72 %            10
```

#### PR #447

```console
$ meson test -C build --benchmark reduce-bench -v
Running ./build/src/reduce-bench
Run on (24 X 5446.55 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.79, 2.33, 3.43
-------------------------------------------------------------------------------------------------------------------
Benchmark                                                                         Time             CPU   Iterations
-------------------------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               287 ms         5.43 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               288 ms         4.50 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               273 ms         5.03 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               270 ms         4.75 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               259 ms         6.18 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               272 ms         5.22 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               266 ms         9.44 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               264 ms         6.27 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               276 ms         9.83 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time               269 ms         6.77 ms            2
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_mean          272 ms         6.34 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_median        271 ms         5.81 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_stddev       9.27 ms         1.88 ms           10
BM_jpeg_reduce_lanczos3_factor_8/10000x10000/repeats:10/real_time_cv           3.40 %         29.60 %            10
```
