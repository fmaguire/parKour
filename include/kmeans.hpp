#ifndef PARKOUR_SRC_KMEANS_H_
#define PARKOUR_SRC_KMEANS_H_
#include<armadillo>

arma::Col<size_t> kmeans(arma::mat dataset, int clusters);

#endif // PARKOUR_SRC_KMEANS_H_
