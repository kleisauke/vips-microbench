# libvips micro-benchmarks

A collection of micro-benchmarks used to measure the performance of libvips.

## Build
```bash
git clone https://github.com/kleisauke/vips-microbench.git
cd vips-microbench
rm -rf build/
cmake -S . -B build -GNinja -DCMAKE_BUILD_TYPE=Release
cmake --build build -- -j$(nproc)
```

## Run
```bash
# Disable CPU frequency scaling while running the benchmark
sudo cpupower frequency-set --governor performance

# Or use tuned-adm (RHEL / Fedora specific)
sudo tuned-adm profile throughput-performance

./bin/vips-microbench-exif --benchmark_repetitions=10
./bin/vips-microbench-thumbnail --benchmark_repetitions=10
./bin/vips-microbench-reduce --benchmark_repetitions=10
./bin/vips-microbench-jpeg --benchmark_repetitions=10

# After benchmarking you can go back to the more conservative option
sudo cpupower frequency-set --governor powersave
```
