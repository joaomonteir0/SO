/*
 *  \author ...
 */

#ifndef __SOMM22__MODULE__MEM__GROUP__
#define __SOMM22__MODULE__MEM__GROUP__

#include "somm22.h"

namespace somm22
{
    
    namespace group 
    {


        namespace mem
        {
            /* ACTION POINT: Declare here your module's data structure as external */              
            struct MemBlock{
                uint32_t memSize;
		        uint32_t memSizeOS;
		        uint32_t chunkSize;
                AllocationPolicy policy;
            };
            
            struct Memory {
                uint32_t pid;
                void* start;
                uint32_t size;
                Memory* next;
            };
            
            extern Memory* busy_list;
            extern Memory* free_list;
            extern MemBlock mb;

        } // end of namespace mem

    } // end of namespace group

} // end of namespace somm22

#endif /* __SOMM22__MODULE__MEM__GROUP__ */


