#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <armadillo>
    
void split_fastq(int num_clusters,
                 arma::Col<size_t> assignments, 
                 char* r1_fn, 
                 char* r2_fn) {
    /* Using a list of cluster assignments split
     * input fastq into 2N output files where
     * N is the number of user specified clusters
     * (one file for each member of pair)
     */

    // Open original input files and init strings for parsing them
    std::ifstream r1_fp;
    std::ifstream r2_fp;
    std::string r1_line;
    std::string r2_line;
    r1_fp.open(r1_fn);
    r2_fp.open(r2_fn);
    
    // Init sstrings to hold cluster file names for output
    std::stringstream output_fn_r1;
    std::stringstream output_fn_r2;

    // Init array of ofstreams to hold output fp
    std::ofstream output_files_r1[num_clusters];
    std::ofstream output_files_r2[num_clusters];
    
    // Iterate over number of clusters and create and open a pair
    // of output files for each cluster
    for (int i = 0; i < num_clusters; i++) {
        output_fn_r1.str("");
        output_fn_r1 << "cluster" << i << "_r1.fq";
        output_files_r1[i].open(output_fn_r1.str());

        output_fn_r2.str("");
        output_fn_r2 << "cluster" << i << "_r2.fq";
        output_files_r2[i].open(output_fn_r2.str());
    }

    // Init counters to keep track of line and read number
    size_t line_number = 0;
    size_t read_number = 0;
    
    // Init array to hold a tally of PE reads assigned to each cluster
    std::vector<size_t> read_tally(num_clusters);

    if(r1_fp.is_open() && r2_fp.is_open()){
        while(std::getline(r1_fp, r1_line), std::getline(r2_fp, r2_line)){
            
            // Each read starts on line 4N so only iterate read_number
            // every 4th line, but don't for first line otherwise
            // first read will get skipped
            if(line_number % 4 == 0 && line_number != 0){
                read_number++;
                // Add one to the read tally for assigned cluster of the new read
                read_tally[assignments[read_number]] += 1;
            }
            
            // Special case hack for tallying first read in input file
            if(line_number == 0){
                read_tally[assignments[read_number]]++;
            }
            
            // Using array of fps write the current line for each input file
            // to the correct output file
            output_files_r1[assignments[read_number]] << r1_line << '\n';
            output_files_r2[assignments[read_number]] << r2_line << '\n';
            
            line_number++;
        }
    }

    r1_fp.close();
    r2_fp.close();
    
    // Append to log file
    std::ofstream log_file;
    log_file.open("run_log", std::fstream::app);
   
    // Close cluster output fp and output tally data to a log_file
    for (int i = 0; i < num_clusters; i++) {
        output_files_r1[i].close();
        output_files_r2[i].close();

        log_file << "Reads assigned to cluster" << i << ": " << read_tally[i] << '\n';
        std::cout << "Reads assigned to cluster" << i << ": " << read_tally[i] << '\n';
    }

    log_file.close();

}
