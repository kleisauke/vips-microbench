#include <benchmark/benchmark.h>
#include <vips/vips8>

using vips::VImage;

static void BM_jpeg_exif_strip(benchmark::State &state,
                               const char *in_file,
                               const char *out_file) {
    for (auto _ : state) {
        auto image = VImage::new_from_file(
            in_file, VImage::option()->set("access", VIPS_ACCESS_SEQUENTIAL));
        image.jpegsave(out_file,
                       VImage::option()->set("keep", VIPS_FOREIGN_KEEP_NONE));
    }
}

// clang-format off
BENCHMARK_CAPTURE(BM_jpeg_exif_strip,
                  original,
                  "images/multi-segment_exif.jpg",
                  "bin/multi-segment_exif_strip.jpg")
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
