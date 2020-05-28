## Generic Hash Table
_______

[**Documentation**](https://tonyjosi97.github.io/generic_hash_table/ght__core_8c.html)
_______

Hash Table implementation using [Open addressing](https://en.wikipedia.org/wiki/Open_addressing) & [Double hashing](https://en.wikipedia.org/wiki/Double_hashing) method.

> **Open addressing**
> > Open addressing, or closed hashing, is a method of collision resolution in hash tables. With this method a hash collision is resolved by probing, or searching through alternate locations in the array (the probe sequence) until either the target record is found, or an unused array slot is found, which indicates that there is no such key in the table.

> **Double hashing**
> > Interval between probes is fixed for each record but is computed by another hash function.

### Test Status

Tested with 1 million records

#### TO DO:
* Make memcpy to memcpy_s

#### Reference

##### [**Amortized analysis**](https://en.wikipedia.org/wiki/Amortized_analysis)

> In computer science, amortized analysis is a method for analyzing a given algorithm's complexity, or how much of a resource, especially time or memory, it takes to execute. The motivation for amortized analysis is that looking at the worst-case run time per operation, rather than per algorithm, can be too pessimistic.

> While certain operations for a given algorithm may have a significant cost in resources, other operations may not be as costly. The amortized analysis considers both the costly and less costly operations together over the whole series of operations of the algorithm. This may include accounting for different types of input, length of the input, and other factors that affect its performance.
