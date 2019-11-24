<center> 

# **CS211 Project3**

Name: Longze Su 

SID: 862188702

## **Parallel Sieve of Eratosthenes for Finding All Prime Numbers within $10^{10}$**


</center> 

### Result

Totol number in $10^{10}$ is 455052511

Processors|sieve_0|sieve_1|sieve_1_1|sieve_2|sieve_3|sieve_3_1|sieve_3_2
-|-|-|-|-|-|-|-
32 (1 node)|52.042357|13.727133|13.649198|13.656898|13.900585|7.015423|3.110836
64 (2 nodes)|14.368390|6.867126|6.941115|6.942078|6.929694|3.514650|1.506547
128 (3 nodes)|7.084161|6.250889|3.525625|6.455842|3.461387|1.811583|0.747701
256 (4 nodes)|3.861867|3.133166|3.083019|3.178725|1.725458|0.871841|<font color=#DC143C>0.395250</font>

### Analysis

<center> 

#### ***Sieve #1***
</center> 

Use two different policy if the prime square is not larger than the low value and the low value is not divisible by the prime. 

First is Sieve_1_1
$$[p*((low\%p+1)\%2+1) - low\%p]>>1$$
Second is Sieve_1
$$[p*((low/p)\%2+1) - low\%p]>>1$$
Theoritically, second is better choice, in the result, we can see that there difference is negotiated. 

When nodes have smaller sizes, sieve_1 improve more effiecncy. While there are more nodes, their efficiencies are similar. 

<center>

#### ***Sieve #2***

</center> 

Sieve 2 is similar to Sieve 1, the communication affect less than we thought. 

<center>

#### ***Sieve #3***

</center> 

Tested three different block sizes: 5000, 12000, 120000
