/*
 *  \author Bárbara Monteiro Moreira, n.mec.: 104056
*/

#include "somm22.h"
#include "peq_module.h"
namespace somm22
{
    namespace group
    {
        // indicates the emptyness state of the queue
        bool peqIsEmpty(uint32_t mask)
        {
            const char *maskStr = (mask == 0) ? "ANY" : ((mask == POSTPONED) ? "POSTPONED" : "ARRIVAL | TERMINATE");
            soProbe(303, "%s(%s)\n", __func__, maskStr);

            if (mask == 0){

                return peq::peqlist.empty();

            }

            for (auto &event : peq::peqlist)
            {
                if (event.eventType & mask)
                {
                    return false;
                }
                return true;
            }
            return true;
        }
    } // end of namespace gr6oup
} // end of namespace somm22

