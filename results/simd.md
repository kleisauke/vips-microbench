# Experiment with Highway

See https://github.com/kleisauke/libvips/tree/simd-highway.

## Test image
```bash
$ vipsheader images/x.jpg
images/x.jpg: 5000x5000 uchar, 3 bands, srgb, jpegload
```

## Test environment

* AMD Ryzen 9 7900, 1 CPU, 24 logical and 12 physical cores
* Fedora 38

## Reduce bench

### TL;DR

~5% faster when using Highway in favor of Orc on this benchmark.

### Before

```bash
$ ./bin/vips-microbench-reduce --benchmark_repetitions=10
2023-07-28T12:28:05+02:00
Running ./bin/vips-microbench-reduce
Run on (24 X 3700 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.37, 0.67, 0.74
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_625x625/strip/real_time              98.1 ms         3.20 ms            7
BM_jpeg_reduce_lanczos3_625x625/strip/real_time              93.2 ms         3.19 ms            7
BM_jpeg_reduce_lanczos3_625x625/strip/real_time              94.0 ms         3.33 ms            7
BM_jpeg_reduce_lanczos3_625x625/strip/real_time              94.9 ms         3.41 ms            7
BM_jpeg_reduce_lanczos3_625x625/strip/real_time              93.3 ms         3.31 ms            7
BM_jpeg_reduce_lanczos3_625x625/strip/real_time              95.4 ms         3.22 ms            7
BM_jpeg_reduce_lanczos3_625x625/strip/real_time              94.1 ms         3.28 ms            7
BM_jpeg_reduce_lanczos3_625x625/strip/real_time              94.3 ms         3.19 ms            7
BM_jpeg_reduce_lanczos3_625x625/strip/real_time              95.4 ms         3.26 ms            7
BM_jpeg_reduce_lanczos3_625x625/strip/real_time              95.7 ms         3.36 ms            7
BM_jpeg_reduce_lanczos3_625x625/strip/real_time_mean         94.8 ms         3.28 ms           10
BM_jpeg_reduce_lanczos3_625x625/strip/real_time_median       94.6 ms         3.27 ms           10
BM_jpeg_reduce_lanczos3_625x625/strip/real_time_stddev       1.43 ms        0.076 ms           10
BM_jpeg_reduce_lanczos3_625x625/strip/real_time_cv           1.50 %          2.33 %            10
```

### After

```bash
$ ./bin/vips-microbench-reduce --benchmark_repetitions=10
2023-07-28T12:37:38+02:00
Running ./bin/vips-microbench-reduce
Run on (24 X 3700 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x12)
  L1 Instruction 32 KiB (x12)
  L2 Unified 1024 KiB (x12)
  L3 Unified 32768 KiB (x2)
Load Average: 0.39, 0.41, 0.57
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BM_jpeg_reduce_lanczos3_625x625/strip/real_time              92.6 ms         2.40 ms            6
BM_jpeg_reduce_lanczos3_625x625/strip/real_time              89.9 ms         2.11 ms            6
BM_jpeg_reduce_lanczos3_625x625/strip/real_time              88.9 ms         2.30 ms            6
BM_jpeg_reduce_lanczos3_625x625/strip/real_time              89.5 ms         2.21 ms            6
BM_jpeg_reduce_lanczos3_625x625/strip/real_time              89.5 ms         2.09 ms            6
BM_jpeg_reduce_lanczos3_625x625/strip/real_time              89.2 ms         2.20 ms            6
BM_jpeg_reduce_lanczos3_625x625/strip/real_time              91.0 ms         2.37 ms            6
BM_jpeg_reduce_lanczos3_625x625/strip/real_time              90.7 ms         2.30 ms            6
BM_jpeg_reduce_lanczos3_625x625/strip/real_time              89.0 ms         2.21 ms            6
BM_jpeg_reduce_lanczos3_625x625/strip/real_time              89.2 ms         2.11 ms            6
BM_jpeg_reduce_lanczos3_625x625/strip/real_time_mean         89.9 ms         2.23 ms           10
BM_jpeg_reduce_lanczos3_625x625/strip/real_time_median       89.5 ms         2.21 ms           10
BM_jpeg_reduce_lanczos3_625x625/strip/real_time_stddev       1.17 ms        0.111 ms           10
BM_jpeg_reduce_lanczos3_625x625/strip/real_time_cv           1.30 %          4.96 %            10
```

## CLI

### TL;DR

- Multi-threaded reduce is ~7% slower when using Highway, probably due to [the extra seq in reducev](https://github.com/libvips/libvips/discussions/2757).
- No significant change in multi-threaded reduceh when using Highway, although user time is faster.
- Single-threaded reduce is ~11% faster when using Highway.
- Single-threaded reduceh is ~56% faster when using Highway(!).
  - This means libvips beats Pillow-SIMD when resizing both horizontally and vertically.

### Pillow-SIMD

```bash
# Pillow-SIMD 625x625
$ time python3 -c "from PIL import Image; Image.open('images/x.jpg').resize((625, 625), Image.LANCZOS).save('simd_pillow.jpg')"

real	0m0.120s
user	0m0.086s
sys	0m0.025s

# Pillow-SIMD 5000x625 (reducev)
$ time python3 -c "from PIL import Image; Image.open('images/x.jpg').resize((5000, 625), Image.LANCZOS).save('simd_pillow.jpg')"

real	0m0.127s
user	0m0.097s
sys	0m0.030s

# Pillow-SIMD 625x5000 (reduceh)
$ time python3 -c "from PIL import Image; Image.open('images/x.jpg').resize((625, 5000), Image.LANCZOS).save('simd_pillow.jpg')"

real	0m0.114s
user	0m0.082s
sys	0m0.031s
```

### libvips multi-threaded before

```bash
# libvips 625x625
$ time vips reduce images/x.jpg tn_x.jpg[strip] 8 8

real	0m0.121s
user	0m0.123s
sys	0m0.031s

# libvips 5000x625 (reducev)
$ time vips reducev images/x.jpg tn_x.jpg[strip] 8

real	0m0.119s
user	0m0.089s
sys	0m0.042s

# libvips 5000x625 (reducev - without Orc)
$ time vips reducev images/x.jpg tn_x.jpg[strip] 8 --vips-novector

real	0m0.252s
user	0m0.235s
sys	0m0.026s

# libvips 625x5000 (reduceh)
$ time vips reduceh images/x.jpg tn_x.jpg[strip] 8

real	0m0.089s
user	0m0.272s
sys	0m0.018s
```

### libvips multi-threaded after

```bash
# libvips 625x625
$ time vips reduce images/x.jpg tn_x.jpg[strip] 8 8

real	0m0.130s
user	0m0.099s
sys	0m0.044s

# libvips 5000x625 (reducev)
$ time vips reducev images/x.jpg tn_x.jpg[strip] 8

real	0m0.123s
user	0m0.100s
sys	0m0.035s

# libvips 625x5000 (reduceh)
$ time vips reduceh images/x.jpg tn_x.jpg[strip] 8

real	0m0.089s
user	0m0.126s
sys	0m0.023s
```

### libvips single-threaded before

```bash
# libvips 625x625
$ time vips reduce images/x.jpg tn_x.jpg[strip] 8 8 --vips-concurrency 1

real	0m0.113s
user	0m0.098s
sys	0m0.016s

# libvips 5000x625 (reducev)
$ time vips reducev images/x.jpg tn_x.jpg[strip] 8 --vips-concurrency 1

real	0m0.092s
user	0m0.089s
sys	0m0.010s

# libvips 5000x625 (reducev - without Orc)
$ time vips reducev images/x.jpg tn_x.jpg[strip] 8 --vips-novector --vips-concurrency 1

real	0m0.222s
user	0m0.216s
sys	0m0.013s

# libvips 625x5000 (reduceh)
$ time vips reduceh images/x.jpg tn_x.jpg[strip] 8  --vips-concurrency 1

real	0m0.251s
user	0m0.249s
sys	0m0.011s
```


### libvips single-threaded after

```bash
# libvips 625x625
$ time vips reduce images/x.jpg tn_x.jpg[strip] 8 8 --vips-concurrency 1

real	0m0.100s
user	0m0.090s
sys	0m0.012s

# libvips 5000x625 (reducev)
$ time vips reducev images/x.jpg tn_x.jpg[strip] 8 --vips-concurrency 1

real	0m0.097s
user	0m0.085s
sys	0m0.018s

# libvips 625x5000 (reduceh)
$ time vips reduceh images/x.jpg tn_x.jpg[strip] 8  --vips-concurrency 1

real	0m0.110s
user	0m0.111s
sys	0m0.008s
```
