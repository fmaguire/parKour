#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <armadillo>

arma::mat gc_counts(char* r1_fn, char* r2_fn){
   
    std::string r1_line;
    std::string r2_line;

    std::ifstream r1_fp;
    std::ifstream r2_fp;

    r1_fp.open(r1_fn);
    r2_fp.open(r2_fn);

    unsigned int line_number = 0;
    unsigned int read_number = 0;
    unsigned int i;
    unsigned int GC_r1, GC_r2;
    unsigned int AT_r1, AT_r2;
   
    // output mat dimensions, initially have 10,000 rows and expand
    // as needed below
    unsigned int nrow = 10000;
    unsigned int ncol = 2;
    
    arma::mat output(ncol, nrow);
   
    if(r1_fp.is_open() && r2_fp.is_open()){
        
        while(std::getline(r1_fp, r1_line), std::getline(r2_fp, r2_line)){
            
            line_number++;
            
            GC_r1 = 0;
            GC_r2 = 0;
            AT_r1 = 0;
            AT_r2 = 0;

            // as files are fastq only every 4th line contains sequences
            if(line_number % 4 == 2){

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
                
                // expand nrows in output matrix by another 10k chunk if the
                // readnumber is reaching the current number of rows
                if(read_number >= nrow){
                    nrow += 10000;
                    output.resize(ncol, nrow);
                }

                output(0, read_number) = (float) GC_r1 / (GC_r1 + AT_r1);
                output(1, read_number) = (float) GC_r2 / (GC_r2 + AT_r2);

                read_number++;
            }
        }

    } else {
        std::cout << "Problem opening files" << '\n';
        exit(1);
    }

    // resize output matrix to correct nrows i.e. number of reads
    output.resize(ncol, read_number);
    
    r1_fp.close();
    r2_fp.close();

    return output;
}

