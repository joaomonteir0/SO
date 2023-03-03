/*
 *  
 */

#ifndef __SOMM22__MODULE__PEQ__GROUP__
#define __SOMM22__MODULE__PEQ__GROUP__

#include "somm22.h"

#include <list>
#include <stdio.h>
#include <map>

namespace somm22
{

    namespace group 
    {

        namespace peq
        {
            /* ACTION POINT: Declare here your module's data structure as external */
            
            struct PeqBlock{
            
            	//used for at least init
                uint32_t pid;
                uint32_t arrivalTime;
                uint32_t startTime;
                uint32_t duration;
                uint32_t addrSpaceSize;
                
            };
            
            extern std::list<Event> peqlist;
        } // end of namespace peq

    } // end of namespace group

} // end of namespace somm22

#endif /* __SOMM22__MODULE__PEQ__GROUP__ */
