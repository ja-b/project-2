
# Project 2 Write-up

## 1
### Comparison Table

## 2
### Serial Time Complexity

## 3
### Analytic Aritmetic Complexity

## 4
### GPU v. CPU Speedup

## 5
### Amdahl Ceiling n=100000

## 6
### Amdahl Ceiling n=500000

## 7
### Compute or Memory Bound

## 8
### CPU ICC

## 9
### Vectorized Instructions

## 10
### L1/L2/L3 Cache Hit Rate CPU

## 11
### Branch misprediction rate

## 12
### TLB Hit Ratio

## 13
### Hardware Thread Gains

## 14
### Thread count memory saturation

## 15
### Max parallel efficiency

## 16
### Strong-scaling/Weak-scaling

## 17
### L1 miss rate serial v. multicore

## 18
### GPU Optimization Explanation

#### gpu1

This implementation tries to parallelize computation with both CPU threads as well
as GPU threads. CPU for the post-calc position update and GPU for the inter-force calculation.

The CPU threading is straightforward, parallelize the simple (honestly SIMD) update.

The GPU side is broken up across 1 axis of bodies, with each thread responsible for at most
1 body.

#### gpu2

Similar to GPU1 but without openmp for the position update. Probably better considering the relative
cost of position update.

#### gpu3

For the GPU block, write the starting position state for all bodies first as to avoid
possible contention between threads. 

My initial guess is that this would help from false-sharing perspecive (not to mention, correctness?)

The syncthreads is there to converge on a state for each "sublock" of our routine.

#### gpu4

This adds a loop unroll for our loop per gpu thread. A probable way to improve occupancy
by shedding away temporary state variables.

## 19
### Fraction of host/device copy

## 20
### GPU Occupancy

## Addendum
### Resource Stats

jab29@midway2-0121
Architecture:          x86_64
CPU op-mode(s):        32-bit, 64-bit
Byte Order:            Little Endian
CPU(s):                56
On-line CPU(s) list:   0-27
Off-line CPU(s) list:  28-55
Thread(s) per core:    1
Core(s) per socket:    14
Socket(s):             2
NUMA node(s):          2
Vendor ID:             GenuineIntel
CPU family:            6
Model:                 79
Model name:            Intel(R) Xeon(R) CPU E5-2680 v4 @ 2.40GHz
Stepping:              1
CPU MHz:               1200.000
CPU max MHz:           2401.0000
CPU min MHz:           1200.0000
BogoMIPS:              4799.81
Virtualization:        VT-x
L1d cache:             32K
L1i cache:             32K
L2 cache:              256K
L3 cache:              35840K
NUMA node0 CPU(s):     0-13
NUMA node1 CPU(s):     14-27
Flags:                 fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc aperfmperf eagerfpu pni pclmulqdq dtes64 monitor ds_cpl vmx smx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid dca sse4_1 sse4_2 x2apic movbe popcnt aes xsave avx f16c rdrand lahf_lm abm 3dnowprefetch epb cat_l3 cdp_l3 invpcid_single intel_ppin intel_pt tpr_shadow vnmi flexpriority ept vpid fsgsbase tsc_adjust bmi1 hle avx2 smep bmi2 erms invpcid rtm cqm rdt_a rdseed adx xsaveopt cqm_llc cqm_occup_llc cqm_mbm_total cqm_mbm_local dtherm ida arat pln pts
