#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <algorithm>
#include <armadillo>
#include "kmeans.h"

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

    // iterate through fastq generator calculating GC for pair
    //

    
    r1_fp.open(argv[1]);
    r2_fp.open(argv[2]);
   
    // Check supplied files open
    if(r1_fp.is_open() && r2_fp.is_open()){
        
        NR = 0;

        while(std::getline(r1_fp, r1_line), std::getline(r2_fp, r2_line)){
            
            NR++;
            
            GC_r1 = 0;
            GC_r2 = 0;
            AT_r1 = 0;
            AT_r2 = 0;


            // as files are fastq only every 4th line contains sequences
            if(NR % 4 == 2){

                // as PE reads can be different lengths after trimming
                // need to iterate over the length of the longer read
                for(i = 0; i < std::max(r1_line.size(), r2_line.size()); i++){
                    
                    // if we aren't at the end of r1 tally GC at i-th pos
                    if(i < r1_line.size()){

                        if(r1_line[i] == 'G' || r1_line[i] == 'C'){
                            GC_r1++;
                        }

                        if(r2_line[i] == 'G' || r2_line[i] == 'C'){
                            GC_r2++;
                        } 
                    }
                    
                    // if we aren't at the end of r2 tally GC at i-th pos
                    if(i < r2_line.size()){

                        if(r1_line[i] == 'A' || r1_line[i] == 'T'){
                            AT_r1++;
                        }
    
                        if(r2_line[i] == 'A' || r2_line[i] == 'T'){
                            AT_r2++;
                        }
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
    
    arma::mat dataset(2, GC_scores_1.size());

    for(i = 0; i < GC_scores_1.size(); i++){
        dataset(0,i) = GC_scores_1[i];
        dataset(1,i) = GC_scores_2[i];
    }

    int clusters = 2;

    std::cout << dataset << '\n';

    arma::Col<size_t> assignments = kmeans(dataset, clusters);
    
    std::cout << assignments << '\n';

    return 0;
}

