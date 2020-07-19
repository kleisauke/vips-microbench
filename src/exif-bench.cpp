#include <benchmark/benchmark.h>
#include <vips/vips8>

using vips::VImage;

static void BM_jpeg_exif_strip(benchmark::State &state,
                                      const char *in_file,
                                      const char *out_file) {
    for (auto _ : state) {
        auto image = VImage::new_from_file(
            const_cast<char *>(in_file),
            VImage::option()->set("access", VIPS_ACCESS_SEQUENTIAL));
        image.jpegsave(const_cast<char *>(out_file),
                       VImage::option()->set("strip", true));
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

    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();

    vips_shutdown();
}
