# infieri2018

## OpenMP

directive example #pragma omp parallel for

1. The application has the objective of 

2. Identify the most time consuming loop using Intel Advisor

```
icpc -O3 -g -fopenmp  sum.cpp -o sum
time ./sum < sum2.in
```

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


there is a race condition on variable digits

put a lock to solve the problem.
```
omp_lock_t lck;

//omp_init_lock(&lck);
omp_init_lock_with_hint(&lck, omp_lock_hint_speculative);

sum(output, d, n);

omp_destroy_lock(&lck);

```

and lock set and unset 

```
      p_set_lock(&lck); 
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



Offload Over Fabric


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

Nbody example with offload for xeon phi knc can be used without changes in xeon phi knl
