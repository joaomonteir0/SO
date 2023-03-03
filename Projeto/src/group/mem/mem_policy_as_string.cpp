/*
 *  \author Bárbara Monteiro Moreira n.mec.: 104056

 */

#include "somm22.h"
#include "mem_module.h"

namespace somm22
{

    namespace group 
    {

// ================================================================================== //

        const char *memAllocationPolicyAsString(AllocationPolicy policy)
        {
            soProbe(490, "%s(\"%u\")\n", __func__, policy);

            switch(policy){

                case FirstFit:
                    return "FirstFit";
                    break;
                case NextFit:
                    return "NextFit";
                    break;
                case BestFit:
                    return "BestFit";
                    break;
                case WorstFit:
                    return "WorstFit";
                    break;
                default:
                    return "Unknown";
                
            }
            throw Exception(ENOSYS, __func__);
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

