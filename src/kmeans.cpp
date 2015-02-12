#include <mlpack/methods/kmeans/kmeans.hpp>
#include <armadillo>
#include <iostream>

arma::Col<size_t> kmeans(arma::mat dataset, int clusters){

    arma::Col<size_t> assignments;
    
    arma::mat centroids;
    
    mlpack::kmeans::KMeans<> k;
    
    k.Cluster(dataset, clusters, assignments, centroids);

    std::cout << "Cluster centroids: \n" << centroids << '\n';
    
    return assignments;

}
    
    
