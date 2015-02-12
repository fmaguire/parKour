#include <mlpack/methods/kmeans/kmeans.hpp>
#include <armadillo>

arma::Col<size_t> kmeans(arma::mat dataset, int clusters){

    arma::Col<size_t> assignments;
    
    arma::mat centroids;
    
    mlpack::kmeans::KMeans<> k;
    
    k.Cluster(dataset, clusters, assignments, centroids);
    
    return assignments;

}
    
    
