fs = import('fs')

bench_files = files(
    'exif-bench.cpp',
    'jpeg-bench.cpp',
    'reduce-bench.cpp',
    'shrink-bench.cpp',
    'thumbnail-bench.cpp',
)

foreach bench_src : bench_files
    exe_name = fs.stem(bench_src)

    bench_exe = executable(
        exe_name,
        bench_src,
        dependencies: [benchmark_main_dep, vips_dep],
    )

    benchmark(exe_name, bench_exe)
endforeach
