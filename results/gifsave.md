# Comparison of different 'gifsave' libraries

Tested commits:
- https://github.com/dloebl/cgif/commit/e3ba2e62613f10c7cac0dc053b86069a668b5beb
- https://github.com/lecram/gifenc/commit/7d53ea9820af3388a1df1a5b16ed4bcc6f6ef7c7

## Results

TL;DR: cgif is ~41% faster than gifenc on this benchmark.

````bash
2021-07-27T12:55:02+02:00
Running ./bin/vips-microbench-gifsave
Run on (6 X 4100.96 MHz CPU s)
CPU Caches:
L1 Data 32 KiB (x6)
L1 Instruction 32 KiB (x6)
L2 Unified 256 KiB (x6)
L3 Unified 9216 KiB (x1)
Load Average: 0.48, 0.84, 0.80
---------------------------------------------------------------------
Benchmark                           Time             CPU   Iterations
---------------------------------------------------------------------
BM_gifenc/real_time             0.703 ms        0.671 ms          993
BM_gifenc/real_time             0.707 ms        0.671 ms          993
BM_gifenc/real_time             0.710 ms        0.674 ms          993
BM_gifenc/real_time             0.703 ms        0.670 ms          993
BM_gifenc/real_time             0.702 ms        0.670 ms          993
BM_gifenc/real_time             0.706 ms        0.674 ms          993
BM_gifenc/real_time             0.710 ms        0.678 ms          993
BM_gifenc/real_time             0.741 ms        0.680 ms          993
BM_gifenc/real_time             0.705 ms        0.672 ms          993
BM_gifenc/real_time             0.702 ms        0.671 ms          993
BM_gifenc/real_time_mean        0.709 ms        0.673 ms           10
BM_gifenc/real_time_median      0.705 ms        0.672 ms           10
BM_gifenc/real_time_stddev      0.012 ms        0.003 ms           10
BM_cgif/real_time               0.414 ms        0.377 ms         1689
BM_cgif/real_time               0.414 ms        0.377 ms         1689
BM_cgif/real_time               0.414 ms        0.377 ms         1689
BM_cgif/real_time               0.414 ms        0.377 ms         1689
BM_cgif/real_time               0.414 ms        0.377 ms         1689
BM_cgif/real_time               0.414 ms        0.377 ms         1689
BM_cgif/real_time               0.414 ms        0.377 ms         1689
BM_cgif/real_time               0.414 ms        0.377 ms         1689
BM_cgif/real_time               0.413 ms        0.377 ms         1689
BM_cgif/real_time               0.414 ms        0.377 ms         1689
BM_cgif/real_time_mean          0.414 ms        0.377 ms           10
BM_cgif/real_time_median        0.414 ms        0.377 ms           10
```
