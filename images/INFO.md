# Image provenance
`DSCN0533.jpg`:
```
https://raw.githubusercontent.com/bleroy/core-imaging-playground/master/images/DSCN0533.JPG
```

`DSCN0533_strip.jpg`:
```bash
identify -format '%Q' DSCN0533.jpg
vips copy DSCN0533.jpg DSCN0533_strip.jpg[Q=97,strip]
```

`multi-segment_exif.jpg`:
```
https://dev.exiv2.org/issues/1232#note-4
```

`sample2.v`:
```
https://github.com/libvips/vips-bench/blob/master/sample2.v
```

`x.jpg`:
```bash
vips colourspace sample2.v t1.v srgb
vips replicate t1.v t2.v 40 30
vips extract_area t2.v x.jpg[strip] 0 0 10000 10000
rm t{1,2}.v
```
