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

        Event peqFetchNext(uint32_t mask)
        {
            // Define a local variable called maskStr and assign it a string value based on the value of mask
            const char *maskStr = (mask == 0) ? "ANY" : ((mask == POSTPONED) ? "POSTPONED" : "ARRIVAL | TERMINATE");
            // Call the soProbe function and pass it two arguments: a string containing the function name and a string containing the value of maskStr
            soProbe(305, "%s(%s)\n", __func__, maskStr);

            /* ACTION POINT: Replace next instruction with your code */
            // Define an iterator called it for a list called peqlist
            std::list<Event>::iterator it;

            // Iterate through peqlist and search for the first event in the list that matches the value of mask
            for (it = somm22::group::peq::peqlist.begin(); it != somm22::group::peq::peqlist.end(); ++it)
            {
                // If mask is not 0
                if ((mask) != 0)
                {
                    // Found a matching event, remove it from the queue and return it
                    Event evt = *it;
                    somm22::group::peq::peqlist.erase(it);
                    return evt;
                }
                if (mask == 0) mask = 0b111;
            }

            // No matching event was found
            throw Exception(EINVAL, __func__);
        }

// ================================================================================== //

        Event peqPeekNext(uint32_t mask)
        {
            const char *maskStr = (mask == 0) ? "ANY" : ((mask == POSTPONED) ? "POSTPONED" : "ARRIVAL | TERMINATE");
            soProbe(305, "%s(%s)\n", __func__, maskStr);

            /* ACTION POINT: Replace next instruction with your code */
            //throw Exception(ENOSYS, __func__);
            
            std::list<Event>::iterator it;

            // Iterate through peqlist and search for the first event in the list that matches the value of mask
            for (it = somm22::group::peq::peqlist.begin(); it != somm22::group::peq::peqlist.end(); ++it)
            {
                // If mask is not 0
                if ((mask) != 0)
                {
                    // Found a matching event, return it
                    Event evt = *it;
                    return evt;
                }
                if (mask == 0) mask = 0b111;
            }

            // No matching event was found
            throw Exception(EINVAL, __func__);
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
