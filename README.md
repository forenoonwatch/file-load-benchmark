# File Load Benchmark
An ultra-simple benchmark for windows comparing cstdio vs Windows' ReadFile and MapViewOfFile APIs.
To actually simulate a workload actively reading from the file, the test decodes a JPG image from the loaded
memory using STB image.

## Results
On my PC (i7-4790k, Windows 10, build with MinGW GCC 12.2 in -O3 Release):
```
2023-12-07T00:47:47-00:00
Running BenchFile.exe
Run on (8 X 3991 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x4)
  L1 Instruction 32 KiB (x4)
  L2 Unified 256 KiB (x4)
  L3 Unified 8192 KiB (x1)
------------------------------------------------------------
Benchmark                  Time             CPU   Iterations
------------------------------------------------------------
BM_File_Stdio        1965954 ns      1968834 ns          373
BM_File_Windows      2565221 ns      2572791 ns          249
BM_File_MemoryMap    2376846 ns      2321787 ns          249
```

