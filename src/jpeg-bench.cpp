#include <benchmark/benchmark.h>
#include <vips/vips8>

using vips::VImage;

// From: https://github.com/libvips/vips-bench/blob/master/vips.cc
static void BM_jpeg_crop_shrink_sharpen(benchmark::State &state,
                                        const char *in_file,
                                        const char *out_file) {
    for (auto _ : state) {
        auto in = VImage::new_from_file(in_file);

        // clang-format off
        auto mask = VImage::new_matrixv(3, 3,
                                        -1.0, -1.0, -1.0,
                                        -1.0, 16.0, -1.0,
                                        -1.0, -1.0, -1.0);
        // clang-format on
        mask.set("scale", 8);

        in.extract_area(100, 100, in.width() - 200, in.height() - 200)
            .reduce(1.0 / 0.9, 1.0 / 0.9,
                    VImage::option()->set("kernel", VIPS_KERNEL_LINEAR))
            .conv(mask,
                  VImage::option()->set("precision", VIPS_PRECISION_INTEGER))
            .jpegsave(out_file);
    }
}

// clang-format off
BENCHMARK_CAPTURE(BM_jpeg_crop_shrink_sharpen,
                  10000x10000,
                  "images/x.jpg",
                  "bin/x2.jpg")
        ->Unit(benchmark::kMillisecond)
        ->UseRealTime();
// clang-format on

int main(int argc, char *argv[]) {
    if (VIPS_INIT(argv[0]) != 0) {
        vips_error_exit(nullptr);
    }

    // Disable libvips cache to ensure tests are as fair as they can be
    vips_cache_set_max(0);

    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();

    vips_shutdown();
}
