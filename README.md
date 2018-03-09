# infieri 2018

## Architecture

## Vectorization

### Auto-vectorization

1. Compile autovec application

```
icc autovec.c -o autovec -qopt-report=5 -g -O3
cat autovec.optrpt
```

First loop vectorize automatically 
Second loop can not be vectorized by compiler because it presents depencies 

## OpenMP

### 1. OpenMP Directives
  
  Example of using one pragma to distribute several iterations of a single loops into threads:
  
  #pragma omp parallel for
 
 The application has the objective of 

Execute the serial version of this application:

```
icpc -O3 -g -fopenmp  sum.cpp -o sum
time ./sum < sum2.in
```

 Identify the most time consuming loop using Intel Advisor

 Put the #pragma omp parallel for in top of most time consuming loop of this program.

```
icpc -O3 -g -fopenmp  sum.cpp -o sum
time ./sum < sum.in
```
put the pragma on line 11
```
#ragma omp parallel for	
```
Executing several times returns different answers, 

### 2. Synchronization

there is a race condition on variable digits

put a lock to solve the problem.

1. declare this variable after "using namespace std;"

```
omp_lock_t lck;
```

put this before and after calling function sum

```
...
omp_init_lock(&lck);
sum(output, d, n);
omp_destroy_lock(&lck);
...

```

put (lock set and lock unset ) before and after change the variable digits:
 

```
  omp_set_lock(&lck); 
  digits[digit] += div;
  omp_unset_lock(&lck); 
```

Execute the application again:

```
icpc -O3 -g -fopenmp  sum.cpp -o sum
time ./sum < sum2.in
```

Have you noticed a drop in performance of your program?

Try use hints to create locks

```
change 
omp_init_lock(&lck);
by
omp_init_lock_with_hint(&lck, omp_lock_hint_speculative);

```

Execute the application again:

```
icpc -O3 -g -fopenmp  sum.cpp -o sum
time ./sum < sum2.in
```

### 3. Offload

The offload is a resource to offload a region of code to a device (GPU, Xeon Phi KNC or KNL)

offload Over Fabric


how to setup xeon phi node for offload over fabric:

https://software.intel.com/en-us/articles/how-to-use-offload-over-fabric-with-knights-landing-intel-xeon-phi-processor


Download xppl for host and target:

https://downloadcenter.intel.com/pt-br/download/27406/?product=94035

White Papers about Offload Over Fabric

https://software.intel.com/en-us/articles/how-to-use-offload-over-fabric-with-knights-landing-intel-xeon-phi-processor

https://software.intel.com/en-us/articles/offload-over-fabric-to-intel-xeon-phi-processor-tutorial

Simple example of offload over fabric:

```
icc -qopenmp testHW.c -o testHW
export OFFLOAD_NODES=10.0.0.5

./testHW 
Running on host: phi01.ncc.unesp.br
Running on target: phi05
export OFFLOAD_NODES=10.0.0.6

./testHW 
Running on host: phi01.ncc.unesp.br
Running on target: phi06

testHW.c
```

### 4. Nbody 

  Example with offload for xeon phi knc can be used without changes in xeon phi knl

## MPI

### 1. MPI benchmark

regular TCP/IP connection
```
export I_MPI_FABRICS=TCP
mpirun -host phi03 -n 1 /opt/intel/impi/2018.1.163/bin64/IMB-MPI1 Sendrecv : -host phi01 -n 1 /opt/intel/impi/2018.1.163/bin64/IMB-MPI1 Sendrecv
```
regular TCP/IP connection using Omni-Path IP over IB abstraction

```
export I_MPI_FABRICS=TCP
mpirun -host 10.0.0.3 -n 1 /opt/intel/impi/2018.1.163/bin64/IMB-MPI1 Sendrecv : -host 10.0.0.1 -n 1 /opt/intel/impi/2018.1.163/bin64/IMB-MPI1 Sendrecv
```

PSM2 protocol in top of Omni-path network:

```
unset I_MPI_FABRICS
mpirun -PSM2 -host 10.0.0.3 -n 1 /opt/intel/impi/2018.1.163/bin64/IMB-MPI1 Sendrecv : -host 10.0.0.1 -n 1 /opt/intel/impi/2018.1.163/bin64/IMB-MPI1 Sendrecv
```
### 2. Monitoring Performance of MPI Application

In order to take mode information about performance of a MPI application you can use APS (Application Performance Snapshot), that comes with Vtune.

Execute MPI application with APS

time mpirun -PSM2 -host 10.0.0.3 -n 30 aps ~/mpi/mpi_wave : -host 10.0.0.1 -n 30 ~/mpi/mpi_wave
aps --report=/home/silvio/mpi/aps_result_20180309

## OpenMP/MPI Optimization
