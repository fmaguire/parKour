#include<fstream>
#include<iostream>
#include<armadillo>
    
void split_fastq(arma::Col<size_t> assignments, char *argv[]){

    std::ofstream cluster0_r1_fp;
    std::ofstream cluster0_r2_fp;
    std::ofstream cluster1_r1_fp;
    std::ofstream cluster1_r2_fp;

    cluster0_r1_fp.open("cluster0_r1.fq");
    cluster0_r2_fp.open("cluster0_r2.fq");
    cluster1_r1_fp.open("cluster1_r1.fq");
    cluster1_r2_fp.open("cluster1_r2.fq");

    std::ifstream r1_fp;
    std::ifstream r2_fp;
    std::string r1_line;
    std::string r2_line;

    r1_fp.open(argv[1]);
    r2_fp.open(argv[2]);

    unsigned int line_number = 0;
    unsigned int read_number = 0;

    if(r1_fp.is_open() && r2_fp.is_open()){
        while(std::getline(r1_fp, r1_line), std::getline(r2_fp, r2_line)){
 
            if(line_number % 4 == 0 && line_number != 0){
                read_number++;
            }
           
            if(assignments[read_number] == 0){
                cluster0_r1_fp << r1_line << '\n';
                cluster0_r2_fp << r2_line << '\n';
            }

            if(assignments[read_number] == 1){
                cluster1_r1_fp << r1_line << '\n';
                cluster1_r2_fp << r2_line << '\n';
            }
            
            line_number++;
        }
    }

    r1_fp.close();
    r2_fp.close();

    cluster0_r1_fp.close();
    cluster0_r2_fp.close();
    cluster1_r1_fp.close();    
    cluster1_r2_fp.close();
}
