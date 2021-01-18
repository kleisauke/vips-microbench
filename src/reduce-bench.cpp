#include <benchmark/benchmark.h>
#include <vips/vips8>

using vips::VImage;

static void BM_vips_reduce_lanczos3_150x150(benchmark::State &state,
                                            const char *in_file,
                                            const char *out_file) {
    const double factor = 5000.0 / 150.0;

    for (auto _ : state) {
        auto image = VImage::new_from_file(
            const_cast<char *>(in_file),
            VImage::option()->set("access", VIPS_ACCESS_SEQUENTIAL));
        image =
            image.reduce(factor, factor,
                         VImage::option()->set("kernel", VIPS_KERNEL_LANCZOS3));
        image.jpegsave(const_cast<char *>(out_file),
                       VImage::option()->set("strip", true));
    }
}

// clang-format off
BENCHMARK_CAPTURE(BM_vips_reduce_lanczos3_150x150,
                  strip,
                  "images/x.v",
                  "bin/x_150x150.jpg")
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
