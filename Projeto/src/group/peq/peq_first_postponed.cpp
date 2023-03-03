/*
 *  \author João Monteiro n.mec.: 102690
 */

#include "somm22.h"
#include "peq_module.h"

namespace somm22
{

    namespace group 
    {

// ================================================================================== //

        uint32_t peqGetFirstPostponedProcess() 
    {
        soProbe(306, "%s()\n", __func__);

        // Iterate through the peqlist
        for (auto &event : somm22::group::peq::peqlist)
        {
            // Check if the event time is of type POSTPONED
            if (event.eventTime == POSTPONED)
            {
                // Return the PID of the event
                return event.pid;
            }
        }

        // If no event with a POSTPONED event time is found, return 0
        return 0;
    }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

