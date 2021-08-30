
# Project 2 Write-up

## 1
### Comparison Table

## 2
### Serial Time Complexity

The complexity can be outlined by the following table.

![Serial Scaling](img/serial_scaling.png)

The last column shows the relative ratio of time to nbody. Given the
terms, 9, 18, 27, 37... we can roughly say that this routine has O(n^2)
complexity.

This makes sense, given from analytic perspective, we are calculating forces
between each pair of particles, which should naturally arrive at a O(n^2) runtime
assuming a serial computer.

## 3
### Analytic Aritmetic Complexity

## 4
### GPU v. CPU Speedup

## 5
### Amdahl Ceiling n=100000

Using a thread count of 32 and comparing against our serial run...

We have the following equation, where we can solve for the fraction of execution time affected by the speedup. We can use
this to get our percentage of sequential execution (and optimal bound).

![](img/speedup_eq_1.gif)
![](img/eqn_1.gif)

Solving for `p` gives us `0.9868`. Which tells us that our bound (our sequential) is at `1.3%`.

## 6
### Amdahl Ceiling n=500000

Using a thread count of 32...following the same steps as above.

Sequential 500k = 
Parallel32 500k = 

![](img/speedup_eq_1.gif)
![](img/eqn_1.gif)

Solving for `p` gives us `0.9868`. Which tells us that our bound (our sequential) is at `1.3%`.

## 7
### Compute or Memory Bound

## 8
### CPU ICC

Using the timing from the next question (#9). We compare the following

- GCC: 924.647 (from #1)
- ICC: 265.059 (from #9, with vectorization)



## 9
### Vectorized Instructions

The following loops/instructions get vectorized in ICC (made sure to turn on AVX vectorization explicitly as well)

- Inner loop (only) gets vectorized in our force calculation function.
- The position update loop gets fully vectorized.

When comparing vectorization against no vec
- W/vec: 265.058975
- Wo/vec: 


#### Vectorization Report

Intel(R) Advisor can now assist with vectorization and show optimization
report messages with your source code.
See "https://software.intel.com/en-us/intel-advisor-xe" for details.


    Report from: Interprocedural optimizations [ipo]

INLINING OPTION VALUES:
-inline-factor: 100
-inline-min-size: 30
-inline-max-size: 230
-inline-max-total-size: 2000
-inline-max-per-routine: 10000
-inline-max-per-compile: 500000


Begin optimization report for: main(const int, const char **)

    Report from: Interprocedural optimizations [ipo]

INLINE REPORT: (main(const int, const char **)) [1] /home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(39,45)
-> INLINE: (44,27) atoi(const char *)
{{ Inlining of routines from system headers is omitted. Use -qopt-report=3 to view full report. }}
-> INLINE: (45,28) atoi(const char *)
{{ Inlining of routines from system headers is omitted. Use -qopt-report=3 to view full report. }}
-> INLINE: (54,3) randomizeBodies(float *, int)
-> INLINE: (82,5) bodyForce(Body *, float, int)


    Report from: Loop nest, Vector & Auto-parallelization optimizations [loop, vec, par]


LOOP BEGIN at /home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(15,3) inlined into /home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(54,3)
remark #15527: loop was not vectorized: function call to rand(void) cannot be vectorized   [ /home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(16,23) ]
LOOP END

LOOP BEGIN at /home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(21,3) inlined into /home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(82,5)
remark #25236: Loop with pragma of trip count = 3000 ignored for large value
remark #15542: loop was not vectorized: inner loop was already vectorized

LOOP BEGIN at /home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(24,5) inlined into /home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(82,5)
remark #15300: LOOP WAS VECTORIZED
LOOP END

LOOP BEGIN at /home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(24,5) inlined into /home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(82,5)
<Remainder loop for vectorization>
LOOP END
LOOP END

LOOP BEGIN at /home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(85,5)
remark #15300: LOOP WAS VECTORIZED
LOOP END

LOOP BEGIN at /home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(85,5)
<Remainder loop for vectorization>
remark #15301: REMAINDER LOOP WAS VECTORIZED
LOOP END

LOOP BEGIN at /home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(85,5)
<Remainder loop for vectorization>
LOOP END

LOOP BEGIN at /home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(100,3)
remark #15344: loop was not vectorized: vector dependence prevents vectorization. First dependence is shown below. Use level 5 report for details
LOOP END


Non-optimizable loops:


LOOP BEGIN at /home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(76,3)
remark #15543: loop was not vectorized: loop with function call not considered an optimization candidate.   [ /home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(79,5) ]
LOOP END

    Report from: Code generation optimizations [cg]

/home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(25,18):remark #34032: adjacent sparse (strided) loads are not optimized. Details: stride { 24 }, types { F32-V256, F32-V256, F32-V256 }, number of elements { 8 }, select mask { 0x000000007 }.
/home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(86,7):remark #34032: adjacent sparse (strided) loads are not optimized. Details: stride { 24 }, types { F32-V256, F32-V256, F32-V256, F32-V256, F32-V256, F32-V256 }, number of elements { 8 }, select mask { 0x00000003F }.
/home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(86,7):remark #34032: adjacent sparse (strided) loads are not optimized. Details: stride { 24 }, types { F32-V256, F32-V256, F32-V256, F32-V256, F32-V256, F32-V256 }, number of elements { 8 }, select mask { 0x00000003F }.
/home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(88,7):remark #34033: adjacent sparse (strided) stores are not optimized. Details: stride { 24 }, types { F32-V256, F32-V256, F32-V256 }, number of elements { 8 }, select mask { 0x000000007 }.
===========================================================================

Begin optimization report for: randomizeBodies(float *, int)

    Report from: Interprocedural optimizations [ipo]

INLINE REPORT: (randomizeBodies(float *, int)) [3] /home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(14,42)


    Report from: Loop nest, Vector & Auto-parallelization optimizations [loop, vec, par]


LOOP BEGIN at /home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(15,3)
remark #15527: loop was not vectorized: function call to rand(void) cannot be vectorized   [ /home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(16,23) ]
LOOP END
===========================================================================

Begin optimization report for: bodyForce(Body *, float, int)

    Report from: Interprocedural optimizations [ipo]

INLINE REPORT: (bodyForce(Body *, float, int)) [4] /home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(20,42)


    Report from: Loop nest, Vector & Auto-parallelization optimizations [loop, vec, par]


LOOP BEGIN at /home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(21,3)
remark #15542: loop was not vectorized: inner loop was already vectorized

LOOP BEGIN at /home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(24,5)
remark #15300: LOOP WAS VECTORIZED
LOOP END

LOOP BEGIN at /home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(24,5)
<Remainder loop for vectorization>
LOOP END
LOOP END

    Report from: Code generation optimizations [cg]

/home/jab29/scratch-midway2/project-2/src/nbody_cpu_serial.c(25,18):remark #34032: adjacent sparse (strided) loads are not optimized. Details: stride { 24 }, types { F32-V256, F32-V256, F32-V256 }, number of elements { 8 }, select mask { 0x000000007 }.

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

![Memory Util](img/memory_util.png)

The memory never gets fully saturated. For this measurement, I couldn't find
an appropriate memory activity measure, so I used L3 misses (which should yield a memory access)
as an appropriate proxy.

This makes sense though, the memory bandwidth limit for this system is quite high. Additionally,
the false-sharing of bodies in the inner loop shouldn't outpace this bound.

Note: The "actual" column refers to the throughput assuming 32 active threads at the same time (since anything higher
is bounded by the CPU)

## 15
### Max parallel efficiency

(Meausrements in section below).

We hit 32 threads for maximum parallel efficiency. This is illustrated quite so
in our strong-scaling, which hits an exact wall-time of 40s for any number of threads past 32.

This is explained since there are 28 cores that are online on our system. We haven't had
any indication that we reached a memory bound before this limit.

## 16
### Strong-scaling/Weak-scaling

#### Strong Scaling
![StrongScaling](img/strong_scaling.png)

#### Weak Scaling
![WeakScaling](img/weak_scaling.png)

Note: Our weak-scaling assumes a linear input increase when in reality
this refers to a quadratic input increase per thread (due to O(n^2)) complexity of
the algorithm. So the reported as-is weak scaling might be frightening without
this context. We've only reported the parallel efficiency (scaled to threads) because of the complications.

We can see that we saturate performance at 32 threads. This comes from the processor
having 28 on-line CPUs (running for 28 threads yields the same performance). Weak scaling
also shows us that further scaling past 32 leads to unsustainable runtimes.

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

EDIT: After refreshing my mind a bit, shared memory should be faster to access than the default global
memory, hence the reason for this optimization.

#### gpu4

This adds a loop unroll for our loop per gpu thread. A probable way to improve occupancy
by shedding away temporary state variables.

## 19
### Fraction of host/device copy

## 20
### GPU Occupancy

## Addendum
### Resource Stats

#### CPU
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


#### Mem/Cache

Memory Cache and TLB Hierarchy Information.
------------------------------------------------------------------------
TLB Information.
There may be multiple descriptors for each level of TLB
if multiple page sizes are supported.

L1 Data TLB:
Page Size:              4 KB
Number of Entries:     64
Associativity:          4


Cache Information.

L1 Data Cache:
Total size:            32 KB
Line size:             64 B
Number of Lines:      512
Associativity:          8

L1 Instruction Cache:
Total size:            32 KB
Line size:             64 B
Number of Lines:      512
Associativity:          8

L2 Unified Cache:
Total size:           256 KB
Line size:             64 B
Number of Lines:     4096
Associativity:          8

L3 Unified Cache:
Total size:         35840 KB
Line size:             64 B
Number of Lines:   573440
Associativity:         20

mem_info.c                               PASSED