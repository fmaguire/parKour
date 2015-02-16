# parKour
Paired Arrangement of Reads via Kmeans On Unlabelled PE-RNA-Seq reads

parKour performs K-mean clustering on PE fastq formatted sequencing reads based
on the GC bias of the paired reads.

Despite being single threaded, performance is relatively good with 139M 150bp PE
reads (45GB of data) 3-means clustered and output to separate fastq files in 14 hours with 7GB 
max resident memory (10M reads took around 3 minutes on the same hardware).

##Usage:
```
./parKour R1.fastq R2.fastq N_CLUSTERS
```

Which will output 2N fastq files where N is the number of clusters:

```
* cluster0_R1.fq
* cluster0_R2.fq
* cluster1_R1.fq
* cluster1_R2.fq
* ...
* ...
* cluster(N-1)_R1.fq
* cluster(N-1)_R2.fq
```

It will also output a log file "run_log" which records the cluster centroids and number of paired reads assigned to each cluster.

##Dependencies:

   * [mlpack](http://www.mlpack.org/)
   * [armadillo](http://arma.sourceforge.net/) (build with ARMA_64BIT_WORD if 
        you want to use parKour on datasets larger than 2bn PE reads)

##Installation:

   * Ensure dependencies are installed and mlpack is in the `LD_LIBRARY_PATH`
   * `make` (note only tested on 64-bit GNU/Linux systems)
   * To run program on toy dataset run make test

##Future planned enhancements:

   * Optional Overclustering
   * Plotting of clustering
   * Unit tests

##Citations:
```
@inproceedings{bradley1998,
    title     = {Refining initial points for k-means clustering},
    author    = {Bradley, Paul S. and Fayyad, Usama M.},
    booktitle = {Proceedings of the Fifteenth International Conference 
                    on Machine Learning (ICML 1998)},
    volume    = {66},
    year      = {1998}
}

@article{mlpack2013,
    title     = {{MLPACK}: A Scalable {C++} Machine Learning Library},
    author    = {Curtin, Ryan R. and Cline, James R. and Slagle, Neil P. and
                    March, William B. and Ram, P. and Mehta, 
                    Nishant A. and Gray, Alexander G.},
    journal   = {Journal of Machine Learning Research},
    volume    = {14},
    pages     = {801--805},
    year      = {2013}
}

@article{sanderson2010,
    title     = {Armadillo: An Open Source C++ Linear Algebra Library for Fast 
                    Prototyping and Computationally Intensive Experiments},
    author    = {Sanderson, Conrad},
    journal   = {NICTA Technical Report},
    year      = {2010}
}
```
