/*
 *  \author ...
 */

#include "somm22.h"
#include "mem_module.h"

namespace somm22
{

    namespace group 
    {

// ================================================================================== //

        void memInit(uint32_t mSize, uint32_t osSize, uint32_t cSize, AllocationPolicy allocPolicy) 
        {
            soProbe(401, "%s(0x%x, 0x%x, 0x%x, %s)\n", __func__, mSize, osSize, cSize, memAllocationPolicyAsString(allocPolicy));

            require(mSize > osSize, "memory must be bigger than the one use by OS");
            require((mSize % cSize) == 0, "memory size must be a multiple of chunck size");
            require((osSize % cSize) == 0, "memory size for OS must be a multiple of chunck size");

            /* ACTION POINT: Replace next instruction with your code */
            mem::mb.memSize = mSize;
            mem::mb.memSizeOS = osSize;
            mem::mb.chunkSize = cSize;
            mem::mb.policy = allocPolicy;
            
            mem::free_list = new mem::Memory();
            mem::free_list->pid = 0;
            mem::free_list->start = (char*) 0 + osSize;
            mem::free_list->size = mSize - osSize;
            mem::free_list->next = NULL;
            mem::busy_list = NULL;
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

