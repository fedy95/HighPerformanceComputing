# Matrix multiplication in OpenMP
[Table of contents](https://github.com/fedy95/HighPerformanceComputing/blob/master/README.md)

## Used software
- VMware Workstation 15 Player (15.0.2 build-10952284);
- OS: KDE Neon 5.15 64bit;
- clang: 1:6.0-41-exp5-ubuntu1
- cmake: 3.10.2-1ubuntu2
- g++: 4:7.4.0-1ubuntu2.2
- gcc: 4:7.4.0-1ubuntu2.2
- gcc-multilib: 4:7.4.0-1ubuntu2.2
     
## Used hardware
- CPU: Ryzen 1700 3,82 GHz:
  - Number of processor threads: 8.
- RAM: 16384 MB DDR4-2933MHz:
  - DRAM CAS# Latency: 16,
  - Trcdrd: 17;
  - Trcdwr: 17;
  - DRAM RAS# PRE Time: 17;
  - DRAM RAS# ACT Time: 33.

### Problem
```txt
Input:
A (M,N)
B (N,M)
Task: 
1 .Implement Matrix Multiplication:
1.1) Using SPMD Pattern
1.2) Using OpenMP loop directives with different schedule (type[, chunk]) configurations.
2. Do speedup tests:
2.1) with different amount of data
2.2) with different number of threads
3. Write a report that should include: task definition, brief theory, implementation description, test results (tables, graphics…)

```

### Links
1) http://poodar.me/Configure-OpenMP-&-MPI-in-Clion-on-Mac/
2) https://github.com/MicrosoftDocs/cpp-docs/blob/master/docs/parallel/amp/walkthrough-matrix-multiplication.md
3) http://akira.ruc.dk/~keld/teaching/IPDC_f10/Slides/pdf4x/4_Performance.4x.pdf
4) https://en.cppreference.com/w/cpp/language/destructor
5) https://docs.microsoft.com/en-us/cpp/parallel/openmp/d-using-the-schedule-clause?view=vs-2017
6) https://software.intel.com/ru-ru/articles/getting-started-with-openmp
7) https://software.intel.com/ru-ru/articles/more-work-sharing-with-openmp
8) https://en.wikipedia.org/wiki/SPMD
