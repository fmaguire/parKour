#ifndef PARKOUR_SRC_FASTQ_OUTPUT_H_
#define PARKOUR_SRC_FASTQ_OUTPUT_H_
#include <armadillo>

void split_fastq(int num_clusters, 
                 arma::Col<size_t> assignments, 
                 char* r1_fn, 
                 char* r2_fn);

#endif //PARKOUR_SRC_FASTQ_OUTPUT_H_
