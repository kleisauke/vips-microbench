project(
    'vips-microbench',
    'cpp',
    version: '1.0.0',
    meson_version: '>=0.59',
    default_options: [
        # we use C++11 features
        'cpp_std=c++11',
        # do a release (optimized) build by default
        'buildtype=release',
        # turn off asserts etc. in release mode
        'b_ndebug=if-release',
    ],
)

# if we're optimizing (eg. release mode) we turn off cast checks and g_asserts
if get_option('optimization') not in ['0', 'g']
    add_project_arguments('-DG_DISABLE_CAST_CHECKS', language: 'cpp')
    add_project_arguments('-DG_DISABLE_CHECKS', language: 'cpp')
    add_project_arguments('-DG_DISABLE_ASSERT', language: 'cpp')
endif

cpp = meson.get_compiler('cpp')

vips_dep = dependency('vips-cpp', version: '>=8.11.0')
benchmark_main_dep = dependency(
    'benchmark_main',
    version: '>=1.8.4',
    fallback: ['google-benchmark', 'google_benchmark_main_dep'],
    default_options: 'tests=disabled',
)

summary('Compiler', cpp.get_id(), section: 'Toolchain')
summary('Linker', cpp.get_linker_id(), section: 'Toolchain')

summary('Debugging', get_option('debug'), section: 'Build')
summary('Optimization', get_option('optimization'), section: 'Build')

subdir('images')
subdir('src')
