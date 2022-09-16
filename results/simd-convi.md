# `vips_convi` implemented using SIMD intrinsics

See https://github.com/kleisauke/libvips/tree/simd-highway.

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

real	0m0.046s
user	0m0.038s
sys	0m0.007s

# libvips SIMD test
$ time vips convi x.png vips-blur.png blur.mat --vips-info
VIPS-INFO: 14:53:55.208: convi: using SIMD path

real	0m0.043s
user	0m0.037s
sys	0m0.008s

# Pillow-SIMD benchmark 5000x5000
$ time python3 -c "from PIL import Image, ImageFilter; Image.open('images/x.jpg').filter(ImageFilter.Kernel((3, 3), (1, 1, 1, 1, 1, 1, 1, 1, 1), 9)).save('pillow-simd-blur.jpg')"

real	0m0.313s
user	0m0.225s
sys	0m0.088s

# libvips SIMD benchmark 5000x5000
$ time vips convi images/x.jpg vips-blur.jpg blur.mat --vips-info
VIPS-INFO: 14:54:35.109: convi: using SIMD path

real	0m0.186s
user	0m0.271s
sys	0m0.034s

# libvips Orc benchmark 5000x5000
$ time vips convi images/x.jpg vips-blur.jpg blur.mat --vips-info
VIPS-INFO: 14:57:43.890: convi: using vector path

real	0m0.193s
user	0m0.332s
sys	0m0.026s

# libvips C benchmark 5000x5000
$ time vips convi images/x.jpg vips-blur.jpg blur.mat --vips-info --vips-novector
VIPS-INFO: 14:57:25.409: convi: using C path

real	0m0.227s
user	0m0.720s
sys	0m0.030s
```
