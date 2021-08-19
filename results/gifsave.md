# Comparison of different 'gifsave' libraries

Tested commits:
- https://github.com/dloebl/cgif/commit/8803d06b14dc5f85a5457898b41cd989722d52cc
- https://github.com/lecram/gifenc/commit/87acd487dfa2f2a638eec751a1d6c2fff60822da

## Results

TL;DR: cgif is ~43% faster than gifenc on this benchmark.

````bash
2021-08-19T19:17:23+02:00
Running ./bin/vips-microbench-gifsave
Run on (6 X 4100.22 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 9216 KiB (x1)
Load Average: 0.53, 0.55, 0.72
---------------------------------------------------------------------
Benchmark                           Time             CPU   Iterations
---------------------------------------------------------------------
BM_gifenc/real_time             0.732 ms        0.699 ms          956
BM_gifenc/real_time             0.733 ms        0.700 ms          956
BM_gifenc/real_time             0.735 ms        0.703 ms          956
BM_gifenc/real_time             0.737 ms        0.704 ms          956
BM_gifenc/real_time             0.735 ms        0.703 ms          956
BM_gifenc/real_time             0.735 ms        0.703 ms          956
BM_gifenc/real_time             0.736 ms        0.703 ms          956
BM_gifenc/real_time             0.748 ms        0.702 ms          956
BM_gifenc/real_time             0.736 ms        0.702 ms          956
BM_gifenc/real_time             0.735 ms        0.701 ms          956
BM_gifenc/real_time_mean        0.736 ms        0.702 ms           10
BM_gifenc/real_time_median      0.735 ms        0.702 ms           10
BM_gifenc/real_time_stddev      0.004 ms        0.001 ms           10
BM_cgif/real_time               0.419 ms        0.381 ms         1671
BM_cgif/real_time               0.419 ms        0.381 ms         1671
BM_cgif/real_time               0.419 ms        0.381 ms         1671
BM_cgif/real_time               0.419 ms        0.381 ms         1671
BM_cgif/real_time               0.419 ms        0.381 ms         1671
BM_cgif/real_time               0.419 ms        0.381 ms         1671
BM_cgif/real_time               0.419 ms        0.382 ms         1671
BM_cgif/real_time               0.419 ms        0.381 ms         1671
BM_cgif/real_time               0.419 ms        0.381 ms         1671
BM_cgif/real_time               0.420 ms        0.382 ms         1671
BM_cgif/real_time_mean          0.419 ms        0.381 ms           10
BM_cgif/real_time_median        0.419 ms        0.381 ms           10
BM_cgif/real_time_stddev        0.000 ms        0.000 ms           10
```
