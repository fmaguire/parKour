#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <armadillo>

arma::mat gc_counts(char* r1_fn, char* r2_fn){
    /* Calculate GC% for each member of read pairs
     * from input files and output to armadillo matrix
     */
    
    // initialise vars for reading input files and open them
    std::string r1_line;
    std::string r2_line;
    std::ifstream r1_fp;
    std::ifstream r2_fp;
    r1_fp.open(r1_fn);
    r2_fp.open(r2_fn);

    // initialise vars for main loop
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

            // As files are fastq only every 4N+2, N>=0 lines contain sequences
            if(line_number % 4 == 2){

                // As paired reads can be different lengths after trimming 
                // iterate over the length of the longer read
                for(i = 0; i < std::max(r1_line.size(), r2_line.size()); i++){
                    
                    // If we aren't at the end of read 1, keep tallying GC nts 
                    if(i < r1_line.size()){

                        if(r1_line[i] == 'G' || r1_line[i] == 'C'){
                            GC_r1++;
                        }

                        if(r2_line[i] == 'G' || r2_line[i] == 'C'){
                            GC_r2++;
                        } 
                    }
                    
                    // If we aren't at the end of read 2, tally GC at i-th pos
                    if(i < r2_line.size()){

                        if(r1_line[i] == 'A' || r1_line[i] == 'T'){
                            AT_r1++;
                        }
    
                        if(r2_line[i] == 'A' || r2_line[i] == 'T'){
                            AT_r2++;
                        }
                    }
                }
                
                // Expand nrows in output matrix by another 10k chunk if the
                // readnumber is reaching the current number of rows
                if(read_number >= nrow){
                    nrow += 10000;
                    output.resize(ncol, nrow);
                }
                
                // Calculate GC% for both members of pair
                output(0, read_number) = (float) GC_r1 / (GC_r1 + AT_r1);
                output(1, read_number) = (float) GC_r2 / (GC_r2 + AT_r2);

                read_number++;
            }
        }

    } else {
        std::cout << "Problem opening files" << '\n';
        exit(1);
    }

    // Resize output matrix to correct nrows i.e. number of reads
    output.resize(ncol, read_number);
    
    r1_fp.close();
    r2_fp.close();

    // TEMPORARY: log raw matrix to file
    std::ofstream raw_data_fp;
    raw_data_fp.open("raw_data");
    raw_data_fp << output.t() << std::endl;
    raw_data_fp.close();

    return output;
}

