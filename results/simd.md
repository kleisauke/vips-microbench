# Experiment with SIMD intrinsics

See https://github.com/kleisauke/libvips/tree/simd.

## Test image
```bash
$ vipsheader images/x.jpg
images/x.jpg: 5000x5000 uchar, 3 bands, srgb, jpegload
```

## Reduce bench

### TL;DR

~33% faster when using SIMD intrinsics on this benchmark.

### Before

```bash
$ ./bin/vips-microbench-reduce --benchmark_repetitions=10
2021-02-01T11:31:44+01:00
Running ./bin/vips-microbench-reduce
Run on (6 X 4300 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 9216 KiB (x1)
Load Average: 0.50, 0.59, 0.79
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               420 ms         9.23 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               464 ms         16.0 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               457 ms         14.7 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               475 ms         16.8 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               484 ms         17.4 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               472 ms         15.3 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               467 ms         15.4 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               468 ms         15.6 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               463 ms         15.0 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               473 ms         16.6 ms            2
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_mean          464 ms         15.2 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_median        468 ms         15.5 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_stddev       17.2 ms         2.26 ms           10
```

### After

```bash
$ ./bin/vips-microbench-reduce --benchmark_repetitions=10
2021-02-01T11:35:08+01:00
Running ./bin/vips-microbench-reduce
Run on (6 X 4300 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 9216 KiB (x1)
Load Average: 0.51, 0.66, 0.79
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               304 ms         11.3 ms            3
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               312 ms         14.0 ms            3
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               326 ms         14.9 ms            3
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               315 ms         14.1 ms            3
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               321 ms         14.7 ms            3
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               324 ms         15.1 ms            3
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               310 ms         14.0 ms            3
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               314 ms         13.4 ms            3
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               312 ms         14.1 ms            3
BM_jpeg_reduce_lanczos3_150x150/strip/real_time               311 ms         13.4 ms            3
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_mean          315 ms         13.9 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_median        313 ms         14.0 ms           10
BM_jpeg_reduce_lanczos3_150x150/strip/real_time_stddev       6.88 ms         1.08 ms           10
```

## CLI

### TL;DR

- Multi-threaded reduce is ~35% faster when using SIMD intrinsics.
- Single-threaded reduce is ~38% faster when using SIMD intrinsics.
- No significant change in multi-threaded reduceh when using SIMD intrinsics.
- Single-threaded reduceh is ~21% faster when using SIMD intrinsics.
- Pillow-SIMD is still faster than libvips single-threaded.
- orc path has similar timings than the C-path.

### Pillow-SIMD

```bash
# Pillow-SIMD 150x150
$ time python3 -c "from PIL import Image; Image.open('images/x.jpg').resize((150, 150), Image.LANCZOS).save('simd_pillow.jpg')"

real	0m0.172s
user	0m0.147s
sys	0m0.025s

# Pillow-SIMD 5000x150 (reducev)
$ time python3 -c "from PIL import Image; Image.open('images/x.jpg').resize((5000, 150), Image.LANCZOS).save('simd_pillow.jpg')"

real	0m0.209s
user	0m0.181s
sys	0m0.028s

# Pillow-SIMD 150x5000 (reduceh)
$ time python3 -c "from PIL import Image; Image.open('images/x.jpg').resize((150, 5000), Image.LANCZOS).save('simd_pillow.jpg')"

real	0m0.174s
user	0m0.140s
sys	0m0.034s
```

### libvips multi-threaded before

```bash
# libvips 150x150
$ time vips reduce images/x.jpg tn_x.jpg[strip] 33.33 33.33

real	0m0.419s
user	0m0.398s
sys	0m0.030s

# libvips 5000x150 (reducev)
$ time vips reducev images/x.jpg tn_x.jpg[strip] 33.33

real	0m0.418s
user	0m0.391s
sys	0m0.032s

# libvips 5000x150 (reducev - without liborc)
$ time vips reducev images/x.jpg tn_x.jpg[strip] 33.33 --vips-novector

real	0m0.416s
user	0m0.386s
sys	0m0.035s

# libvips 150x5000 (reduceh)
$ time vips reduceh images/x.jpg tn_x.jpg[strip] 33.33

real	0m0.119s
user	0m0.339s
sys	0m0.014s
```

### libvips multi-threaded after

```bash
# libvips 150x150
$ time vips reduce images/x.jpg tn_x.jpg[strip] 33.33 33.33

real	0m0.270s
user	0m0.247s
sys	0m0.029s

# libvips 5000x150 (reducev)
$ time vips reducev images/x.jpg tn_x.jpg[strip] 33.33

real	0m0.267s
user	0m0.237s
sys	0m0.036s

# libvips 150x5000 (reduceh)
$ time vips reduceh images/x.jpg tn_x.jpg[strip] 33.33

real	0m0.117s
user	0m0.268s
sys	0m0.011s
```

### libvips single-threaded before

```bash
# libvips 150x150
$ time vips reduce images/x.jpg tn_x.jpg[strip] 33.33 33.33 --vips-concurrency 1

real	0m0.406s
user	0m0.394s
sys	0m0.012s

# libvips 5000x150 (reducev)
$ time vips reducev images/x.jpg tn_x.jpg[strip] 33.33 --vips-concurrency 1

real	0m0.399s
user	0m0.391s
sys	0m0.011s

# libvips 5000x150 (reducev - without liborc)
$ time vips reducev images/x.jpg tn_x.jpg[strip] 33.33 --vips-novector --vips-concurrency 1

real	0m0.398s
user	0m0.383s
sys	0m0.017s

# libvips 150x5000 (reduceh)
$ time vips reduceh images/x.jpg tn_x.jpg[strip] 33.33  --vips-concurrency 1

real	0m0.342s
user	0m0.335s
sys	0m0.011s
```


### libvips single-threaded after

```bash
# libvips 150x150
$ time vips reduce images/x.jpg tn_x.jpg[strip] 33.33 33.33 --vips-concurrency 1

real	0m0.251s
user	0m0.238s
sys	0m0.013s

# libvips 5000x150 (reducev)
$ time vips reducev images/x.jpg tn_x.jpg[strip] 33.33 --vips-concurrency 1

real	0m0.247s
user	0m0.232s
sys	0m0.018s

# libvips 150x5000 (reduceh)
$ time vips reduceh images/x.jpg tn_x.jpg[strip] 33.33  --vips-concurrency 1

real	0m0.268s
user	0m0.261s
sys	0m0.011s
```
