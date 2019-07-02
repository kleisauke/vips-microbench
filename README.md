# libvips micro-benchmarks

A collection of micro-benchmarks used to measure the performance of libvips.

## Build
```bash
git clone https://github.com/kleisauke/vips-microbench.git
cd vips-microbench
mkdir build && cd build
cmake .. \
  -DCMAKE_BUILD_TYPE=Release
make
```

## Run
```bash
# Disable the CPU frequency scaling while running the benchmark
sudo cpupower frequency-set --governor performance

./bin/vips-microbench-thumbnail --benchmark_repetitions=10
./bin/vips-microbench-reduce --benchmark_repetitions=10

# After benchmarking you can go back to the more conservative option
sudo cpupower frequency-set --governor powersave
```
