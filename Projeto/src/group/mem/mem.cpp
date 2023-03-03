/*
 *  \author ...
 */

#include "somm22.h"
#include "mem_module.h"

namespace somm22
{
    namespace group 
    {
        namespace mem
        {
            /* ACTION POINT: Declare here your module's internal data structure */
            Memory* busy_list;
            Memory* free_list;
            MemBlock mb;
    
            
        } // end of namespace mem

    } // end of namespace group

} // end of namespace somm22

