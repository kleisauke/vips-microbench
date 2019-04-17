#include <benchmark/benchmark.h>
#include <vips/vips8>

using vips::VImage;

static void BM_jpeg_thumbnail_150x150(benchmark::State &state,
                                      const char *in_file,
                                      const char *out_file) {
    for (auto _ : state) {
        auto thumbnail =
            VImage::thumbnail(const_cast<char *>(in_file), 150,
                              VImage::option()->set("height", 150));
        thumbnail.jpegsave(const_cast<char *>(out_file),
                           VImage::option()->set("strip", true));
    }
}

// clang-format off
BENCHMARK_CAPTURE(BM_jpeg_thumbnail_150x150,
                  original,
                  "images/DSCN0533.jpg",
                  "bin/DSCN0533_150x150.jpg")->Unit(benchmark::kMillisecond);
BENCHMARK_CAPTURE(BM_jpeg_thumbnail_150x150,
                  strip,
                  "images/DSCN0533_strip.jpg",
                  "bin/DSCN0533_strip_150x150.jpg")->Unit(benchmark::kMillisecond);
// clang-format on

int main(int argc, char *argv[]) {
    if (VIPS_INIT(argv[0]) != 0) {
        vips_error_exit(nullptr);
    }

    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();

    vips_shutdown();
}
