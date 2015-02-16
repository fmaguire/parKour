#include <mlpack/methods/kmeans/kmeans.hpp>
#include <fstream>
#include <armadillo>
#include <iostream>

arma::Col<size_t> kmeans(arma::mat dataset, int num_clusters){
    
    // Init col vector to store kmeans assingments
    arma::Col<size_t> assignments;
   
    // Init matrix of doubles to store centroids for each cluster
    arma::mat centroids;
    
    // Create kmeans object
    mlpack::kmeans::KMeans<> k;
    
    // Perform kmeans clustering
    k.Cluster(dataset, num_clusters, assignments, centroids);

     
    std::cout << "Cluster centroids: \n" << centroids << '\n';
   
    // Write cluster centroids to log file
    std::ofstream log_file;
    log_file.open("run_log");
    
    for (size_t i = 0; i < centroids.n_cols; i++){
        log_file << "cluster" << i << " centroids: " 
            << centroids(0,i) << ", " <<  centroids(1,i)  << '\n';
    }
    log_file.close();

    return assignments;

}
    
    
