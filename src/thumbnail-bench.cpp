#include <benchmark/benchmark.h>
#include <vips/vips8>

using vips::VImage;

static void BM_jpeg_thumbnail_150x150(benchmark::State &state,
                                      const char *in_file,
                                      const char *out_file) {
    for (auto _ : state) {
        auto thumbnail = VImage::thumbnail(
            in_file, 150, VImage::option()->set("height", 150));
        thumbnail.jpegsave(
            out_file, VImage::option()->set("keep", VIPS_FOREIGN_KEEP_NONE));
    }
}

// clang-format off
BENCHMARK_CAPTURE(BM_jpeg_thumbnail_150x150,
                  original,
                  "images/DSCN0533.jpg",
                  "bin/DSCN0533_150x150.jpg")
        ->Unit(benchmark::kMillisecond)
        ->UseRealTime();

BENCHMARK_CAPTURE(BM_jpeg_thumbnail_150x150,
                  strip,
                  "images/DSCN0533_strip.jpg",
                  "bin/DSCN0533_strip_150x150.jpg")
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
