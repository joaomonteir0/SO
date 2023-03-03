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

        uint32_t memGetBiggestHole()
        {
            soProbe(409, "%s()\n", __func__);       
            
            uint32_t size = 0;
            mem::Memory* iterator = mem::free_list;

            while (iterator != (void*)0){
            	if (iterator->size > size) size = iterator->size;
                iterator = iterator->next;
            }
            
            return size;
        }

// ================================================================================== //

        uint32_t memGetMaxAllowableSize()
        {
            soProbe(409, "%s()\n", __func__);
            return mem::mb.memSize - mem::mb.memSizeOS;
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
