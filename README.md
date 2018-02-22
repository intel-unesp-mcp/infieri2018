# infieri2018

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
