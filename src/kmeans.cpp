#include <mlpack/methods/kmeans/kmeans.hpp>
#include <fstream>
#include <armadillo>
#include <iostream>

arma::Col<size_t> kmeans(arma::mat dataset, int num_clusters){
    
    // col vector to store kmeans assingments
    arma::Col<size_t> assignments;
   
    // matrix of doubles to store centroids for each cluster
    arma::mat centroids;
    
    mlpack::kmeans::KMeans<> k;
    
    // kmeans clustering
    k.Cluster(dataset, num_clusters, assignments, centroids);


    std::cout << "Cluster centroids: \n" << centroids << '\n';
   
    // logging cluster centroids
    std::ofstream log_file;
    log_file.open("run_log");

    std::cout << "num cent: "centroids.n_rows << 
    for (size_t i = 0; i < centroids.n_rows; i++){
        log_file << "cluster" << i << " centroids:" << centroids(0,i) << "," <<  centroids(1,i)  << '\n';
    }
    log_file.close();

    return assignments;

}
    
    
