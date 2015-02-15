#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <armadillo>
    
void split_fastq(int num_clusters,
                 arma::Col<size_t> assignments, 
                 char* r1_fn, 
                 char* r2_fn) {

    // open original input files and init strings for parsing them
    std::ifstream r1_fp;
    std::ifstream r2_fp;
    std::string r1_line;
    std::string r2_line;
    r1_fp.open(r1_fn);
    r2_fp.open(r2_fn);
    
    // sstrings to hold file names for output
    std::stringstream output_fn_r1;
    std::stringstream output_fn_r2;

    // ofstreams to hold fh  
    std::ofstream output_files_r1[num_clusters];
    std::ofstream output_files_r2[num_clusters];
    

    for (int i = 0; i < num_clusters; i++) {
        output_fn_r1.str("");
        output_fn_r1 << "cluster" << i << "_r1.fq";
        output_files_r1[i].open(output_fn_r1.str());

        output_fn_r2.str("");
        output_fn_r2 << "cluster" << i << "_r2.fq";
        output_files_r2[i].open(output_fn_r2.str());
    }

    // counters to keep track of line and read number
    size_t line_number = 0;
    size_t read_number = 0;
    
    // array to hold tally of PE reads assigned to each cluster
    std::vector<size_t> read_tally(num_clusters);

    if(r1_fp.is_open() && r2_fp.is_open()){
        while(std::getline(r1_fp, r1_line), std::getline(r2_fp, r2_line)){
 
            if(line_number % 4 == 0 && line_number != 0){
                read_number++;
                read_tally[assignments[read_number]] += 1;
            }

            if(line_number == 0){
                read_tally[assignments[read_number]]++;
            }
            
            output_files_r1[assignments[read_number]] << r1_line << '\n';
            output_files_r2[assignments[read_number]] << r2_line << '\n';
            
            line_number++;
        }
    }

    r1_fp.close();
    r2_fp.close();
 
    std::ofstream log_file;
    log_file.open("run_log", std::fstream::app);
   
    // close outputfp and output tally data
    for (int i = 0; i < num_clusters; i++) {
        output_files_r1[i].close();
        output_files_r2[i].close();

        log_file << "Reads assigned to cluster" << i << ": " << read_tally[i] << '\n';
        std::cout << "Reads assigned to cluster" << i << ": " << read_tally[i] << '\n';
    }

    log_file.close();

}
