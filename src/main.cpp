#include <iostream>
#include <cstdlib>
#include <armadillo>
#include "kmeans.hpp"
#include "feature_extraction.hpp"
#include "fastq_output.hpp"

int main (int argc, char *argv[]) {

    // Check arg input 
    if(argc != 4 || strcmp(argv[1], "-h") == 0) {

        std::cout << "Usage: " << argv[0] << "r1.fastq r2.fastq n_clusters" << '\n';
        std::exit(1);
    }

    char* r1_fn = argv[1];
    char* r2_fn = argv[2];
    int num_clusters = atoi(argv[3]);

    std::cout << "1. Beginning Feature Extraction" << '\n';
    arma::mat dataset = gc_counts(r1_fn, r2_fn);    
    std::cout << "2. Feature Extraction Complete" << '\n';

    std::cout << "3. Beginning K-means clustering" << '\n';
    arma::Col<size_t> assignments = kmeans(dataset, num_clusters);
    std::cout << "4. K-means clustering complete" << '\n';

    std::cout << "5. Beginning split of fastq input based on assignments" << '\n';
    split_fastq(num_clusters, assignments, r1_fn, r2_fn);
    std::cout << "6. Fastq splitting complete" << '\n';

    return 0;
}
