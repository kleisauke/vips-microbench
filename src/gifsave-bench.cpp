#include <benchmark/benchmark.h>
extern "C" {  // TODO(kleisauke): This should be handled in the cgif.h
#include <cgif.h>
}
#include <cstring>
#include <gifenc.h>

static void BM_gifenc(benchmark::State &state) {
    int w = 120, h = 90;  // canvas size
    uint8_t palette[] = {
        0x00, 0x00, 0x00,  // 0 -> black
        0xFF, 0x00, 0x00,  // 1 -> red
        0x00, 0xFF, 0x00,  // 2 -> green
        0x00, 0x00, 0xFF,  // 3 -> blue
    };
    int depth = 2;              // palette depth == log2(# of colors)
    int numFrames = 4 * 6 / 3;  // number of frames
    int numLoops = 0;           //  infinite loop

    for (auto _ : state) {
        // create a GIF
        ge_GIF *gif =
            ge_new_gif("images/gifenc.gif", w, h, palette, depth, numLoops);

        // draw some frames
        for (int i = 0; i < numFrames; i++) {
            for (int j = 0; j < w * h; j++)
                gif->frame[j] = (i * 3 + j) / 6 % 4;
            ge_add_frame(gif, 10);  // append the new frame
        }

        // remember to close the GIF
        ge_close_gif(gif);
    }
}

static void BM_cgif(benchmark::State &state) {
    GIF *gif;
    GIFConfig gifConfig;
    FrameConfig frameConfig;
    uint8_t *imageData;

    int w = 120, h = 90;  // canvas size
    uint8_t palette[] = {
        0x00, 0x00, 0x00,  // 0 -> black
        0xFF, 0x00, 0x00,  // 1 -> red
        0x00, 0xFF, 0x00,  // 2 -> green
        0x00, 0x00, 0xFF,  // 3 -> blue
    };
    uint8_t numColors = 4;      // number of colors in palette
    int numFrames = 4 * 6 / 3;  // number of frames
    uint16_t numLoops = INFINITE_LOOP;

    for (auto _ : state) {
        memset(&gifConfig, 0, sizeof(GIFConfig));
        memset(&frameConfig, 0, sizeof(FrameConfig));
        gifConfig.attrFlags =
            GIF_ATTR_IS_ANIMATED;  // set needed attribution flag
                                   // (as GIF is animated)
        gifConfig.width = w;
        gifConfig.height = h;
        gifConfig.pGlobalPalette = palette;
        gifConfig.numGlobalPaletteEntries = numColors;
        gifConfig.numLoops = numLoops;
        gifConfig.path = "images/cgif.gif";

        // create a GIF
        gif = cgif_newgif(&gifConfig);

        imageData = static_cast<uint8_t *>(malloc(w * h));  // actual image data
        frameConfig.genFlags = FRAME_GEN_USE_DIFF_WINDOW;
        frameConfig.pImageData = imageData;  // set pointer to image data
        frameConfig.delay = 10;              // set time before next frame

        // draw some frames
        for (int i = 0; i < numFrames; i++) {
            for (int j = 0; j < w * h; j++)
                imageData[j] = (i * 3 + j) / 6 % 4;
            cgif_addframe(gif, &frameConfig);  // append the new frame
        }
        free(imageData);

        // write GIF to file
        cgif_close(gif);  // free allocated space at the end of the session
    }
}

// clang-format off
BENCHMARK(BM_gifenc)
    ->Unit(benchmark::kMillisecond)
    ->UseRealTime();

BENCHMARK(BM_cgif)
    ->Unit(benchmark::kMillisecond)
    ->UseRealTime();
// clang-format on

BENCHMARK_MAIN();
