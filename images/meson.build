images = files(
    'DSCN0533.jpg',
    'DSCN0533_strip.jpg',
    'multi-segment_exif.jpg',
    'x.jpg',
)

foreach image : images
    configure_file(input: image, output: '@PLAINNAME@', copy: true)
endforeach
