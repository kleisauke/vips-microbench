# `vips_convf` implemented using SIMD intrinsics

Tested commit: https://github.com/kleisauke/libvips/commit/fdc67705824d7d95aa943b766a61c299e24519fb

```bash
# Prepare test image
$ vips identity t.v 
$ vips replicate t.v x.png 1 256
$ rm t.v

# Prepare blur mask
$ cat <<EOT > blur.mat
3 3 9 1
1 1 1
1 1 1
1 1 1
EOT

# Pillow-SIMD test
$ time python3 -c "from PIL import Image, ImageFilter; Image.open('x.png').filter(ImageFilter.Kernel((3, 3), (1, 1, 1, 1, 1, 1, 1, 1, 1), 9, 1)).save('pillow-simd-blur.png')"

real	0m0.108s
user	0m0.098s
sys	0m0.009s

# libvips SIMD test
$ time vips convf x.png vips-blur.png blur.mat --vips-info
VIPS-INFO: 10:43:18.012: convf: using SIMD path

real	0m0.029s
user	0m0.022s
sys	0m0.010s

# Pillow-SIMD benchmark 5000x5000
$  time python3 -c "from PIL import Image, ImageFilter; Image.open('images/x.jpg').filter(ImageFilter.Kernel((3, 3), (1, 1, 1, 1, 1, 1, 1, 1, 1), 9, 1)).save('pillow-simd-blur.jpg')"

real	0m0.357s
user	0m0.291s
sys	0m0.065s

# libvips SIMD benchmark 5000x5000
$ time vips convf images/x.jpg vips-blur.jpg blur.mat --vips-info
VIPS-INFO: 10:50:12.454: convf: using SIMD path

real	0m0.160s
user	0m0.295s
sys	0m0.030s

# libvips C benchmark 5000x5000
$ time vips convf images/x.jpg vips-blur.jpg blur.mat --vips-info --vips-nosimd
VIPS-INFO: 10:51:08.977: convf: using C path

real	0m0.222s
user	0m0.789s
sys	0m0.025s
```
