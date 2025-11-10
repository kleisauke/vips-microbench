# libvips micro-benchmarks

A collection of micro-benchmarks used to measure the performance of libvips.

## Build

```bash
git clone https://github.com/kleisauke/vips-microbench.git
cd vips-microbench
rm -rf build/
meson setup build
meson compile -C build
```

## Run

```bash
# Disable CPU frequency scaling while running the benchmark
sudo cpupower frequency-set --governor performance

# Or use tuned-adm (RHEL / Fedora specific)
sudo tuned-adm profile throughput-performance

# All benchmarks 
meson test -C build --benchmark -v

# Individual benchmarks
meson test -C build --benchmark exif-bench -v
meson test -C build --benchmark jpeg-bench  -v
meson test -C build --benchmark reduce-bench -v
meson test -C build --benchmark shrink-bench -v
meson test -C build --benchmark thumbnail-bench -v

# After benchmarking you can go back to the more conservative option
sudo cpupower frequency-set --governor powersave
```
