#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <armadillo>

int main (int argc, char *argv[]) {

    std::string r1_line;
    std::string r2_line;

    std::ifstream r1_fp;
    std::ifstream r2_fp;

    unsigned int NR;
    unsigned int i;
    unsigned int GC_r1, GC_r2;
    unsigned int AT_r1, AT_r2;
    double GC_prop1;
    double GC_prop2;

    std::vector<double> GC_scores_1;
    std::vector<double> GC_scores_2;

    // Check arg input 
    if(argc != 3 || strcmp(argv[1], "-h") == 0) {

        std::cout << "Usage: " << argv[0] << "r1.fastq r2.fastq" << '\n';
        std::exit(1);

    }
    
    r1_fp.open(argv[1]);
    r2_fp.open(argv[2]);
   
    // Check supplied files open 
    if(r1_fp.is_open() && r2_fp.is_open()){
        
        NR = 0;

        while(std::getline(r1_fp, r1_line), std::getline(r2_fp, r2_line)){
            
            if(r1_line.size() != r2_line.size()){
                std::cout << "Files malformed - paired read different length" << '\n';
            }

            NR++;
            
            GC_r1 = 0;
            GC_r2 = 0;
            AT_r1 = 0;
            AT_r2 = 0;


            if(NR % 4 == 1){
                // code to keep track of names?
                //std::cout << r1_line << '\t' << '\n';
            }

            if(NR % 4 == 2){

                for(i = 0; i < r1_line.size(); i++){
    
                    if(r1_line[i] == '\n' || r2_line[i] == '\n'){
                        break; 
                    }

                    // note this ignores Ns entirely
                    if(r1_line[i] == 'G' || r1_line[i] == 'C'){
                        GC_r1++;
                    }

                    if(r2_line[i] == 'G' || r2_line[i] == 'C'){
                        GC_r2++;
                    } 

                    if(r1_line[i] == 'A' || r1_line[i] == 'T'){
                        AT_r1++;
                    }

                    if(r2_line[i] == 'A' || r2_line[i] == 'T'){
                        AT_r2++;
                    }
                }
                
                GC_prop1 = (float) GC_r1 / (GC_r1 + AT_r1);
                GC_prop2 = (float) GC_r2 / (GC_r2 + AT_r2);
                
                GC_scores_1.push_back(GC_prop1);
                GC_scores_2.push_back(GC_prop2);

            }
        }
    }
    else{
        std::cout << "Unable to open file" << '\n';
        std::exit(1);
    }
        
    r1_fp.close();
    r2_fp.close();

    if(GC_scores_1.size() != GC_scores_2.size()){
        std::cout << "Something's fucky PE vectors are different sizes" << '\n';
        std::exit(1);
    }

    return 0;
}

//#include <mlpack/methods/kmeans/kmeans.hpp>

//using namespace mlpack::kmeans;

// The dataset we are clustering on.
// extern arma::mat dataset;
// // The number of clusters we are obtaining.
// extern size_t clusters;
//
// // A matrix pre-filled with guesses for the initial cluster centroids.
// extern arma::mat centroids;
//
// // This will be filled with the final cluster assignments for each point.
// arma::Col<size_t> assignments;
//
// KMeans<> k;
//
// // Remember, the first boolean indicates that we are not giving initial
// // assignment guesses, and the second boolean indicates that we are giving
// // initial centroid guesses.
// k.Cluster(dataset, clusters, assignments, centroids, false, true);
//
// @inproceedings{bradley1998refining,
//  title={Refining initial points for k-means clustering},
//  author={Bradley, Paul S. and Fayyad, Usama M.},
//  booktitle={Proceedings of the Fifteenth International Conference on Machine
//      Learning (ICML 1998)},
//  volume={66},
//  year={1998}
//}
