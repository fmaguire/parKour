#include <iostream>
#include <cstdlib>
#include <armadillo>
#include "kmeans.h"
#include "feature_extraction.h"
#include "fastq_output.h"

int main (int argc, char *argv[]) {

    // Check arg input 
    if(argc != 4 || strcmp(argv[1], "-h") == 0) {

        std::cout << "Usage: " << argv[0] << "r1.fastq r2.fastq n_clusters" << '\n';
        std::exit(1);
    }

    char* r1_fn = argv[1];
    char* r2_fn = argv[2];
    int num_clusters = atoi(argv[3]);

    arma::mat dataset = gc_counts(r1_fn, r2_fn);    

    //std::cout << dataset << '\n';
    arma::Col<size_t> assignments = kmeans(dataset, num_clusters);
    //std::cout << assignments << '\n';
   
    split_fastq(num_clusters, assignments, r1_fn, r2_fn);

    return 0;
}
