/*
 *  \author João Monteiro n.mec.: 102690
 */

#include "somm22.h"
#include "sim_module.h"

namespace somm22 
{

    namespace group
    {

// ================================================================================== //

        /*
         * \brief Init the module's internal data structure
         */
        void simInit()
        {
            soProbe(501, "%s()\n", __func__);

            /* ACTION POINT: Replace next instruction with your code */
            // Initialize the internal data structures for the sim module
            try{
                // Initialize the number of steps processed to 0
                sim::steps_processed = 0;
                // Initialize the time to 0
                sim::currentTime = 0;
                // Initialize the event mask to 0
                sim::current_event_mask = 0;
            }catch(const somm22::Exception& e){throw Exception(e);}
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
