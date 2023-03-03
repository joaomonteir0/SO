/*
 *  \author ...
 */

#include "somm22.h"
#include "peq_module.h"
#include <fstream>
#include <list>
#include <algorithm>


namespace somm22
{

    namespace group 
    {
 
// ================================================================================== //
        
        void peqprinter(FILE* fp)
        {
            fprintf(fp, "+===============================+\n");
            fprintf(fp, "|      Process Event Queue      |\n");
            fprintf(fp, "+-----------+-----------+-------+\n");
            fprintf(fp, "| eventTime | eventType |  PID  |\n");
            fprintf(fp, "+-----------+-----------+-------+\n");
            
            for (auto i = peq::peqlist.begin(); i != peq::peqlist.end(); ++i) {
                auto min = std::min_element(i, peq::peqlist.end(),
                                            [](const Event& a, const Event& b) { return a.pid < b.pid; });
                std::iter_swap(i, min);
            }
            
            for (const auto& entry: peq::peqlist){
                fprintf(fp, "| %9u | %9s |  %3u  |\n",
                entry.eventTime, peqEventTypeAsString(entry.eventType), entry.pid);
            }
            
            fprintf(fp, "+-----------+-----------+-------+\n");
        }
        
        void peqLog()
        {
            soProbe(302, "%s()\n", __func__);

            /* ACTION POINT: Replace next instruction with your code */
            peqprinter(logGetStream());
        }

// ================================================================================== //

        void peqLogEvent(Event *e, const char *msg)
        {
            soProbe(302, "%s(...)\n", __func__);

            // Couldn't find the right format for this print
            fprintf(logGetStream(), "Event: %s\nMessage: %s\n", peqEventTypeAsString(e->eventType), msg);
            peqprinter(logGetStream());
        }

// ================================================================================== //

        void peqPrint(const char *fname, PrintMode mode)
        {
            soProbe(302, "%s(\"%s\", %s)\n", __func__, fname, (mode == NEW) ? "NEW" : "APPEND");

            FILE* fp; 
            
            if (mode == NEW) // se mode == new
            {
                fp = fopen(fname, "w"); // print to a new file
            }
            if (mode == APPEND) // if mode == append, append to the end of the file
            {
                fp = fopen(fname, "a"); // append to the end of the file    
            }

            peqprinter(fp);
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

