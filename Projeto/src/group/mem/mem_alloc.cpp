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

        void *memAlloc(uint32_t pid, uint32_t size)
        {
            soProbe(403, "%s(%u, 0x%x)\n", __func__, pid, size);

            require(pid > 0, "process ID must be non-zero");

            size = ((size + mem::mb.chunkSize - 1) / mem::mb.chunkSize) * mem::mb.chunkSize;
            
            switch (mem::mb.policy)
            {
                case FirstFit:
                    return memFirstFitAlloc(pid, size);
                    break;
                case NextFit:
                    return memNextFitAlloc(pid, size);
                    break;
                case BestFit:
                    return memBestFitAlloc(pid, size);
                    break;
                case WorstFit:
                    return memWorstFitAlloc(pid, size);
                    break;
                default:
                    return NULL;
            }
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

