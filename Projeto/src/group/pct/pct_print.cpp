/*
 *  \author Rodrigo Faria n.mec.: 103361 & Bárbara Moreira n.mec: 104056
 */

#include "somm22.h"
#include "pct_module.h"
#include <fstream>
#include <list>

namespace somm22
{

    namespace group 
    {
// ================================================================================== //

        void pctprinter(FILE* fp){
            fprintf(fp, "+====================================================================================+\n");
            fprintf(fp, "|                               Process Control Table                                |\n");
            fprintf(fp, "+-------+-------------+----------+---------------+-----------+-----------------------+\n");
            fprintf(fp, "|  PID  | arrivalTime | duration | addrSpaceSize |   state   | startTime |  memAddr  |\n");
            fprintf(fp, "+-------+-------------+----------+---------------+-----------+-----------------------+\n");


            for (const auto& entry : pct::pctable){

                pct::PCBlock second = entry.second;
                
                if(second.startTime == 9999)
                {
                    fprintf(fp, "|  %3u  | %11u | %8u | %#13x | %9s |   (nil)   | %7p   |\n",
                    second.pid, second.arrivalTime, second.duration, second.addrSpaceSize,
                    pctStateAsString(second.state), reinterpret_cast<void*>(second.memAddress));
                }else{
                    fprintf(fp, "|  %3u  | %11u | %8u | %#13x | %9s | %9u | %7p   |\n",
                    second.pid, second.arrivalTime, second.duration, second.addrSpaceSize,
                    pctStateAsString(second.state), second.startTime, reinterpret_cast<void*>(second.memAddress));
                }
            }

            fprintf(fp, "+====================================================================================+\n\n");
        }

        // print the internal state of the module
        void pctPrint(const char *fname, PrintMode mode)
        {
            soProbe(202, "%s(\"%s\", %s)\n", __func__, fname, (mode == NEW) ? "NEW" : "APPEND");
            
            FILE* fp; 
            // sort by pid
            // std::sort(entries.begin(), entries.end(),
            //     [](const std::pair<uint32_t, pct::PCBlock>& pid1, const std::pair<uint32_t, pct::PCBlock>& pid2)
            //     {
            //         return pid1.first < pid2.first;
            //     });

            if (mode == NEW) // se mode == new
            {
                fp = fopen(fname, "w"); // print to a new file
            }
            else if (mode == APPEND) // if mode == append, append to the end of the file
            {
                fp = fopen(fname, "a"); // append to the end of the file    
            }

            pctprinter(fp);
        } // end of pctPrint





// ================================================================================== //

        void pctLog()
        {
            soProbe(202, "%s()\n", __func__);
            pctprinter(logGetStream());
        }

// ================================================================================== //
    } // end of namespace group

} // end of namespace somm22
