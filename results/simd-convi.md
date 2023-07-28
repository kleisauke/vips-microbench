# `vips_convi` using Highway

See https://github.com/kleisauke/libvips/tree/simd-highway.

## Test environment

* AMD Ryzen 9 7900, 1 CPU, 24 logical and 12 physical cores
* Fedora 38

## CLI

```bash
# Prepare test image
$ vips identity t.v
$ vips replicate t.v x.png 1 256
$ rm t.v

# Prepare blur mask
$ cat <<EOT > blur.mat
3 3 9
1 1 1
1 1 1
1 1 1
EOT

# Pillow-SIMD test
$ time python3 -c "from PIL import Image, ImageFilter; Image.open('x.png').filter(ImageFilter.Kernel((3, 3), (1, 1, 1, 1, 1, 1, 1, 1, 1), 9)).save('pillow-simd-blur.png')"

real	0m0.025s
user	0m0.021s
sys	0m0.004s

# libvips Highway test
$ time vips convi x.png vips-blur.png blur.mat --vips-info
VIPS-INFO: 12:55:11.178: threadpool completed with 2 workers
VIPS-INFO: 12:55:11.178: threadpool completed with 2 workers
VIPS-INFO: 12:55:11.178: convi: using vector path
VIPS-INFO: 12:55:11.179: threadpool completed with 5 workers

real	0m0.024s
user	0m0.022s
sys	0m0.002s

# Pillow-SIMD benchmark 5000x5000
$ time python3 -c "from PIL import Image, ImageFilter; Image.open('images/x.jpg').filter(ImageFilter.Kernel((3, 3), (1, 1, 1, 1, 1, 1, 1, 1, 1), 9)).save('pillow-simd-blur.jpg')"

real	0m0.167s
user	0m0.117s
sys	0m0.050s

# libvips Highway benchmark 5000x5000
$ time vips convi images/x.jpg vips-blur.jpg blur.mat --vips-info
VIPS-INFO: 12:56:06.713: threadpool completed with 2 workers
VIPS-INFO: 12:56:06.713: threadpool completed with 2 workers
VIPS-INFO: 12:56:06.713: convi: using vector path
VIPS-INFO: 12:56:06.802: threadpool completed with 4 workers

real	0m0.118s
user	0m0.194s
sys	0m0.028s

# libvips Orc benchmark 5000x5000
$ time vips convi images/x.jpg vips-blur.jpg blur.mat --vips-info
VIPS-INFO: 12:34:44.554: threadpool completed with 2 workers
VIPS-INFO: 12:34:44.554: threadpool completed with 2 workers
VIPS-INFO: 12:34:44.554: convi: using vector path
VIPS-INFO: 12:34:44.642: threadpool completed with 5 workers

real	0m0.116s
user	0m0.244s
sys	0m0.028s

# libvips C benchmark 5000x5000
$ time vips convi images/x.jpg vips-blur.jpg blur.mat --vips-info --vips-novector
VIPS-INFO: 12:35:17.353: threadpool completed with 2 workers
VIPS-INFO: 12:35:17.353: convi: using C path
VIPS-INFO: 12:35:17.353: threadpool completed with 2 workers
VIPS-INFO: 12:35:17.458: threadpool completed with 3 workers

real	0m0.134s
user	0m0.597s
sys	0m0.048s
```
