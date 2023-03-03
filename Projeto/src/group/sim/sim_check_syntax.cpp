/*
 *  \author ...
 */

#include "somm22.h"
#include "sim_module.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <ctype.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <unordered_set>

namespace somm22
{

    namespace group
    {

// ================================================================================== //

        // auxiliar functions 

        bool containsDuplicate(int* pids, int size) {
            std::unordered_set<int> pid_set;
            for (int i = 0; i < size; i++) {
                if (pid_set.count(pids[i]) > 0) {
                    return true;
                }
                pid_set.insert(pids[i]);
            }
            return false;
        }

        bool simCheckInputFormat(const char *fname){

            if (fname == NULL){
                printf("File not found!\n");
                exit(1);
            }

            FILE *file_en ;
            int counter = 0 ;
            file_en = fopen(fname,"r") ;
            int pid, arrivalTime, duration, addrSpaceSize;
            char line[100];
            int pids[200];
            
            for (int i = 0; i < 200; i++) {
                pids[i] = 0;
            }


            while(fgets(line,100,file_en)) {

                int start = 0;
                int end = strlen(line) - 1;
                while (isspace(line[start])) {
                    start++;
                }
                while (isspace(line[end]) && end >= 0) {
                    end--;
                }
                if (line[start] == '#') {
                     continue;
                }

                else {
                int fieldCheck = sscanf(line + start, "%u ; %u ; %u ; 0x%d", &pid, &arrivalTime, &duration, &addrSpaceSize);

                if (fieldCheck != 4) {
                    
                    return false;
                }
                
                if ( pid <= 0 ||duration == 0 || addrSpaceSize == 0 || arrivalTime < 0) {
                    return false;
                }
                }

                
                pids[counter] = pid;
                counter++;
            }

            if(containsDuplicate(pids ,counter)){
                 return false;
            }

            else{
                return true;
            }

            fclose(file_en); 
            return 0;

        }

        
// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22