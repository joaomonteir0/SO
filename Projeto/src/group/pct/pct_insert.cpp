/*
 *  \author Bárbara Monteiro Moreira, n.mec.: 104056
 */

#include "somm22.h"
#include "pct_module.h"

namespace somm22
{

    namespace group 
    {

// ================================================================================== //

        // inserts a new entry in the process control table
        void pctInsert(uint32_t pid, uint32_t arrivalTime, uint32_t duration, uint32_t addrSpaceSize)
        {
            soProbe(203, "%s(%d, %u, %u, 0x%x)\n", __func__, pid, arrivalTime, duration, addrSpaceSize);

            //pct::pctable.find(pid); //encontra PID na pctable
            //pct::pctable.end()

            // caso em que o PID já existe

            if (pct::pctable.find(pid) != pct::pctable.end()){
                //throw an exception
                throw Exception(ESRCH, __func__);
            }

            // se o pid nao existir, cria a entry com os parametros do pct
            pct::PCBlock entry;

            //atribui os valores aos campos da entry
            entry.pid = pid;
            entry.arrivalTime = arrivalTime;
            entry.duration = duration;
            entry.addrSpaceSize = addrSpaceSize;
            entry.memAddress = NULL;
            entry.stateName = pctStateAsString(TO_COME);

            // make_pair cria um par de objs
            // queremos o par pid, entry
            pct::pctable.insert(std::make_pair(pid, entry));

        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
