benchmarks = [
    'exif-bench',
    'jpeg-bench',
    'reduce-bench',
    'shrink-bench',
    'thumbnail-bench',
]

foreach benchmark : benchmarks
    exe = executable(
        benchmark,
        sources: '@0@.cpp'.format(benchmark),
        dependencies: [benchmark_main_dep, vips_dep],
    )

    benchmark(benchmark, exe)
endforeach
