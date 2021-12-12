# Pillow-SIMD convolution bug

Tested commits:
https://github.com/uploadcare/pillow-simd/commit/5bf26ac7cfee72a400990bbe49c4bd54c53cd14b
https://github.com/libvips/libvips/commit/561b670ea2cb1fb6ab5f9f8514b2963916a595a5

```bash
# Prepare test image
$ vips identity t.v
$ vips replicate t.v x.png 1 256
$ rm t.v

$ time python3 -c "from PIL import Image, ImageFilter; Image.open('x.png').filter(ImageFilter.Kernel((3, 3), (0, 0, 0, 0, 1, 0, 0, 0, 0), 1, 1)).save('pillow-simd-identity.png')"

# Prepare identity mask for libvips
$ cat <<EOT > identity.mat
3 3 1 1
0 0 0
0 1 0
0 0 0
EOT

# libvips test
$ time vips convf x.png vips-identity.png identity.mat --vips-info
```
