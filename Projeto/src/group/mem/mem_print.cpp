/*
 *  \author Rodrigo Faria n.mec.: 103361 & Bárbara Moreira n.mec: 104056
 */

#include "somm22.h"
#include "mem_module.h"

namespace somm22
{

    namespace group 
    {
        
        void memprinter(FILE* fp){
            fprintf(fp, "+==============================+\n");
            fprintf(fp, "|  Memory Management busy list |\n");
            fprintf(fp, "+-------+-----------+----------+\n");
            fprintf(fp, "|  PID  |   start   |   size   |\n");
            fprintf(fp, "+-------+-----------+----------+\n");
            
            mem::Memory* busy_temp = mem::busy_list;
            while (busy_temp!=NULL) {
                fprintf(fp, "|   %3u | %9p | %#8x |\n", busy_temp->pid, busy_temp->start, busy_temp->size);
                busy_temp = busy_temp->next;
            }

            fprintf(fp, "+==============================+\n\n");

            fprintf(fp, "+==============================+\n");
            fprintf(fp, "|  Memory Management free list |\n");
            fprintf(fp, "+-------+-----------+----------+\n");
            fprintf(fp, "|  PID  |   start   |   size   |\n");
            fprintf(fp, "+-------+-----------+----------+\n");
            
            mem::Memory* free_temp = mem::free_list;
            while (free_temp!=NULL) {
                fprintf(fp, "|  ---  | %9p | %#8x |\n", free_temp->start, free_temp->size);
                free_temp = free_temp->next;
            }
            
            fprintf(fp, "+==============================+\n\n");
        }

// ================================================================================== //

        void memLog()
        {
            soProbe(402, "%s()\n", __func__);

            memprinter(logGetStream());
        }

// ================================================================================== //

        void memPrint(const char *fname, PrintMode mode)
        {
            soProbe(402, "%s(\"%s\", %s)\n", __func__, fname, (mode == NEW) ? "NEW" : "APPEND");
            
            FILE* fp; 
            
            if (mode == NEW) // se mode == new
            {
                fp = fopen(fname, "w"); // print to a new file
            }
            if (mode == APPEND) // if mode == append, append to the end of the file
            {
                fp = fopen(fname, "a"); // append to the end of the file    
            }

            memprinter(fp);
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
