# Experiment with SIMD intrinsics

See https://github.com/kleisauke/libvips/tree/simd-highway.

## Test image
```bash
$ vipsheader images/x.jpg
images/x.jpg: 5000x5000 uchar, 3 bands, srgb, jpegload
```

## Reduce bench

### TL;DR

~52% faster when using SIMD intrinsics on this benchmark.

### Before

```bash
$ ./bin/vips-microbench-reduce --benchmark_repetitions=10
2022-09-16T14:19:17+02:00
Running ./bin/vips-microbench-reduce
Run on (6 X 4200.02 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 9216 KiB (x1)
Load Average: 0.58, 0.79, 0.86
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               418 ms         4.38 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               443 ms         6.08 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               430 ms         3.80 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               431 ms         4.17 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               406 ms         5.00 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               395 ms         3.88 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               417 ms         3.86 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               418 ms         3.85 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               405 ms         3.82 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               410 ms         3.85 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_mean          418 ms         4.27 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_median        418 ms         3.87 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_stddev       14.1 ms        0.739 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_cv           3.39 %         17.30 %            10
```

### After

```bash
$ ./bin/vips-microbench-reduce --benchmark_repetitions=10
2022-09-16T14:15:59+02:00
Running ./bin/vips-microbench-reduce
Run on (6 X 4161.78 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 9216 KiB (x1)
Load Average: 0.71, 0.91, 0.90
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               225 ms         4.94 ms            3
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               199 ms         3.87 ms            3
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               207 ms         3.90 ms            3
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               202 ms         4.94 ms            3
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               194 ms         3.71 ms            3
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               199 ms         4.68 ms            3
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               198 ms         3.56 ms            3
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               197 ms         3.90 ms            3
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               195 ms         4.24 ms            3
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               194 ms         5.17 ms            3
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_mean          201 ms         4.29 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_median        198 ms         4.07 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_stddev       9.23 ms        0.588 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_cv           4.59 %         13.69 %            10
```

## CLI

### TL;DR

- Multi-threaded reduce is ~33% faster when using SIMD intrinsics.
- Single-threaded reduce is ~40% faster when using SIMD intrinsics.
- No significant change in multi-threaded reduceh when using SIMD intrinsics.
- Single-threaded reduceh is ~32% slower(!) when using SIMD intrinsics.
- Pillow-SIMD is still faster than libvips single-threaded.
- orc reducev has similar timings than its C equivalent.

### Pillow-SIMD

```bash
# Pillow-SIMD 150x150
$ time python3 -c "from PIL import Image; Image.open('images/x.jpg').resize((150, 150), Image.LANCZOS).save('simd_pillow.jpg')"

real	0m0.190s
user	0m0.146s
sys	0m0.044s

# Pillow-SIMD 5000x150 (reducev)
$ time python3 -c "from PIL import Image; Image.open('images/x.jpg').resize((5000, 150), Image.LANCZOS).save('simd_pillow.jpg')"

real	0m0.224s
user	0m0.170s
sys	0m0.053s

# Pillow-SIMD 150x5000 (reduceh)
$ time python3 -c "from PIL import Image; Image.open('images/x.jpg').resize((150, 5000), Image.LANCZOS).save('simd_pillow.jpg')"

real	0m0.192s
user	0m0.149s
sys	0m0.042s
```

### libvips multi-threaded before

```bash
# libvips 150x150
$ time vips reduce images/x.jpg tn_x.jpg[strip] 33.33 33.33

real	0m0.443s
user	0m0.417s
sys	0m0.037s

# libvips 5000x150 (reducev)
$ time vips reducev images/x.jpg tn_x.jpg[strip] 33.33

real	0m0.439s
user	0m0.408s
sys	0m0.037s

# libvips 5000x150 (reducev - without liborc)
$ time vips reducev images/x.jpg tn_x.jpg[strip] 33.33 --vips-novector

real	0m0.438s
user	0m0.408s
sys	0m0.037s

# libvips 150x5000 (reduceh)
$ time vips reduceh images/x.jpg tn_x.jpg[strip] 33.33

real	0m0.149s
user	0m0.367s
sys	0m0.021s
```

### libvips multi-threaded after

```bash
# libvips 150x150
$ time vips reduce images/x.jpg tn_x.jpg[strip] 33.33 33.33

real	0m0.296s
user	0m0.220s
sys	0m0.098s

# libvips 5000x150 (reducev)
$ time vips reducev images/x.jpg tn_x.jpg[strip] 33.33

real	0m0.249s
user	0m0.210s
sys	0m0.045s

# libvips 150x5000 (reduceh)
$ time vips reduceh images/x.jpg tn_x.jpg[strip] 33.33

real	0m0.150s
user	0m0.490s
sys	0m0.020s
```

### libvips single-threaded before

```bash
# libvips 150x150
$ time vips reduce images/x.jpg tn_x.jpg[strip] 33.33 33.33 --vips-concurrency 1

real	0m0.427s
user	0m0.405s
sys	0m0.022s

# libvips 5000x150 (reducev)
$ time vips reducev images/x.jpg tn_x.jpg[strip] 33.33 --vips-concurrency 1

real	0m0.420s
user	0m0.390s
sys	0m0.032s

# libvips 5000x150 (reducev - without liborc)
$ time vips reducev images/x.jpg tn_x.jpg[strip] 33.33 --vips-novector --vips-concurrency 1

real	0m0.419s
user	0m0.398s
sys	0m0.023s

# libvips 150x5000 (reduceh)
$ time vips reduceh images/x.jpg tn_x.jpg[strip] 33.33  --vips-concurrency 1

real	0m0.359s
user	0m0.353s
sys	0m0.010s
```


### libvips single-threaded after

```bash
# libvips 150x150
$ time vips reduce images/x.jpg tn_x.jpg[strip] 33.33 33.33 --vips-concurrency 1

real	0m0.255s
user	0m0.205s
sys	0m0.050s

# libvips 5000x150 (reducev)
$ time vips reducev images/x.jpg tn_x.jpg[strip] 33.33 --vips-concurrency 1

real	0m0.246s
user	0m0.203s
sys	0m0.045s

# libvips 150x5000 (reduceh)
$ time vips reduceh images/x.jpg tn_x.jpg[strip] 33.33  --vips-concurrency 1

real	0m0.475s
user	0m0.462s
sys	0m0.017s
```
