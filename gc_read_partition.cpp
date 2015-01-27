#include <iostream>
#include <fstream>
#include <string.h>

int main (int argc, char *argv[]) {

    std::string r1_line;
    std::string r2_line;

    std::ifstream r1_fp;
    std::ifstream r2_fp;

    int NR;
    int i;
    int GC_r1, GC_r2;
    int AT_r1, AT_r2;
    double GC_prop1;
    double GC_prop2;

    // Check arg input 
    if(argc != 3 || strcmp(argv[1], "-h") == 0) {

        printf("Usage: %s r1.fastq r2.fastq\n", argv[0]);
        return 1;

    }
    
    r1_fp.open(argv[1]);
    r2_fp.open(argv[2]);
   
    // Check supplied files open 
    if(r1_fp.is_open() && r2_fp.is_open()){
        
        NR = 0;

        while(std::getline(r1_fp, r1_line), std::getline(r2_fp, r2_line)){
            
            if(r1_line.size() != r2_line.size()){
                    printf("Files malformed - paired read different length");
            }

            NR++;
            
            GC_r1 = 0;
            GC_r2 = 0;
            AT_r1 = 0;
            AT_r2 = 0;


            if(NR % 4 == 1){

                std::cout << r1_line << '\t' << '\n';
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

                    if(r2_line[i] =='A' || r2_line[i] == 'T'){
                        AT_r2++;
                    }
                }
                
                GC_prop1 = (float) GC_r1 / (GC_r1 + AT_r1);
                GC_prop2 = (float) GC_r2 / (GC_r2 + AT_r2);

                std::cout << GC_prop1 << '\t' << GC_prop2 << '\n';
            }
        }
    }
    else{
        printf("Unable to open files");
        return 1;
    }
        
    r1_fp.close();
    r2_fp.close();
    
    return 0;
}

