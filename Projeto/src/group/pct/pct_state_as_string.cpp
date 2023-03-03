/*
 *  \author ...
 */

#include "somm22.h"
#include "pct_module.h"

namespace somm22
{

    namespace group 
    {

// ================================================================================== //

        const char *pctStateAsString(ProcessState state)
        {
            soProbe(291, "%s(\"%u\")\n", __func__, state);

            /* ACTION POINT: Replace next instruction with your code */
            switch (state) {
                case TO_COME:
                    return "TO_COME";
                    break;
                case RUNNING:
                    return "RUNNING";
                    break;
                case SWAPPED:
                    return "SWAPPED";
                    break;
                case FINISHED:
                    return "FINISHED";
                    break;
                case DISCARDED:
                    return "DISCARDED";
                    break;
            }
            return "";
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

