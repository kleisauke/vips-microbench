# Image provenance
`DSCN0533.jpg`:
```
https://raw.githubusercontent.com/bleroy/core-imaging-playground/master/images/DSCN0533.JPG
```

`DSCN0533_strip.jpg`: 
```bash
identify -format '%Q' DSCN0533.jpg
vips copy DSCN0533.jpg DSCN0533_strip.jpg[Q=97,strip=true]
```
