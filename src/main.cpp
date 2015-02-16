#include <iostream>
#include <cstdlib>
#include <armadillo>
#include "kmeans.hpp"
#include "feature_extraction.hpp"
#include "fastq_output.hpp"

int main (int argc, char *argv[]) {

    // Check CLI arg input 
    if(argc != 4 || strcmp(argv[1], "-h") == 0) {

        std::cout << "Usage: " << argv[0] << "r1.fastq r2.fastq n_clusters" << '\n';
        std::exit(1);
    }
   
    // Parse CLI arguments
    char* r1_fn = argv[1];
    char* r2_fn = argv[2];
    int num_clusters = atoi(argv[3]);
    
    /* Iterate over paired input files and
     * create matrix of GC% paired reads:
     *
     *  [r1_1 GC%, r1_2 GC%;
     *   r2_1 GC%, r2_2 GC%;
     *   ...
     *   rN_1 GC%, rN_2 GC%];
     *
     */
    std::cout << "1. Running Feature Extraction" << '\n';
    arma::mat dataset = gc_counts(r1_fn, r2_fn);    
    
    /* Perform k-means clustering on pairs of reads using
     * mlpack kmeans algorith and the user specified number
     * of clusters
     */
    std::cout << "2. Running K-means clustering" << '\n';
    arma::Col<size_t> assignments = kmeans(dataset, num_clusters);
    
    /* Use cluster assignments of pairs of reads from kmeans to split
     * input sequences into a pair of corresponding cluster files
     */
    std::cout << "3. Splitting fastq input based on assignments" << '\n';
    split_fastq(num_clusters, assignments, r1_fn, r2_fn);

    return 0;
}
