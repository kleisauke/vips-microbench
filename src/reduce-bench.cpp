#include <benchmark/benchmark.h>
#include <vips/vips8>

using vips::VImage;

static void BM_jpeg_reduce_lanczos3_factor_8(benchmark::State &state,
                                             const char *in_file,
                                             const char *out_file) {
    const double factor = 8;  // 10000.0 / 1250.0

    for (auto _ : state) {
        auto image = VImage::new_from_file(
            in_file, VImage::option()->set("access", VIPS_ACCESS_SEQUENTIAL));
        image = image.reduce(factor, factor,
                             VImage::option()
                                 ->set("kernel", VIPS_KERNEL_LANCZOS3)
                                 ->set("gap", 2.0));
        image.jpegsave(out_file);
    }
}

// clang-format off
BENCHMARK_CAPTURE(BM_jpeg_reduce_lanczos3_factor_8,
                  10000x10000,
                  "images/x.jpg",
                  "bin/x_1250x1250.jpg")
    ->Unit(benchmark::kMillisecond)
    ->UseRealTime();
// clang-format on

int main(int argc, char *argv[]) {
    benchmark::MaybeReenterWithoutASLR(argc, argv);

    if (VIPS_INIT(argv[0]))
        vips_error_exit(nullptr);

    // Disable libvips cache to ensure tests are as fair as they can be
    vips_cache_set_max(0);

    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();

    vips_shutdown();
}
