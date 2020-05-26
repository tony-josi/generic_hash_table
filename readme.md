## Generic Hash Table

[**Documentation**](https://tonyjosi97.github.io/generic_hash_table/ght__core_8c.html)

Hash Table implementation using [Open addressing](https://en.wikipedia.org/wiki/Open_addressing) & [Double hashing](https://en.wikipedia.org/wiki/Double_hashing) method.

> **Open addressing**
> > Open addressing, or closed hashing, is a method of collision resolution in hash tables. With this method a hash collision is resolved by probing, or searching through alternate locations in the array (the probe sequence) until either the target record is found, or an unused array slot is found, which indicates that there is no such key in the table.

> **Double hashing**
> > Interval between probes is fixed for each record but is computed by another hash function.

### Test Status

Tested with 1 million records

#### TO DO:
* make memcpy to memcpy_s
