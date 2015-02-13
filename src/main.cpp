#include <iostream>
#include <fstream>
#include <armadillo>
#include "kmeans.h"
#include "feature_extraction.h"
#include "fastq_output.h"

int main (int argc, char *argv[]) {

    std::ifstream r1_fp;
    std::ifstream r2_fp;

    // Check arg input 
    if(argc != 3 || strcmp(argv[1], "-h") == 0) {

        std::cout << "Usage: " << argv[0] << "r1.fastq r2.fastq" << '\n';
        std::exit(1);
    }

    r1_fp.open(argv[1]);
    r2_fp.open(argv[2]);
   
    arma::mat dataset = gc_counts(r1_fp, r2_fp);    

    r1_fp.close();
    r2_fp.close();

    int clusters = 2;

    std::cout << dataset << '\n';
    arma::Col<size_t> assignments = kmeans(dataset, clusters);
    std::cout << assignments << '\n';
   
    split_fastq(assignments, argv);

    return 0;
}

