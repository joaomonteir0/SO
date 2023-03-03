/*
 *  \author all p2g1
 */

#ifndef __SOMM22__MODULE__PCT__GROUP__
#define __SOMM22__MODULE__PCT__GROUP__

#include "somm22.h"

#include <map>
#include <list>
#include <stdio.h>

namespace somm22{
    namespace group{
        
        namespace pct{
            struct PCBlock{
                uint32_t pid;
                uint32_t arrivalTime;
                uint32_t startTime;
                uint32_t duration;
                uint32_t addrSpaceSize;
                void *memAddress;
                const char *stateName;
                ProcessState state;
            };
            extern std::map<uint32_t,PCBlock> pctable;  /* ACTION POINT: Declare here your module's data structure as external */
        } // end of namespace pct
    } // end of namespace group
} // end of namespace somm22

#endif /* __SOMM22__MODULE__PCT__GROUP__ */

