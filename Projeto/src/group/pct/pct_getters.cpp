/*
 *  \author Joao Rodrigo Faria, n.mec.: 103361
 */

#include "somm22.h"
#include "pct_module.h"

namespace somm22
{

    namespace group 
    {

// ================================================================================== //

        uint32_t pctGetProcessDuration(uint32_t pid)
        {
            soProbe(204, "%s(%d)\n", __func__, pid);

            require(pid > 0, "process ID must be non-zero");
            
            auto search = pct::pctable.find(pid);
            if(search == pct::pctable.end()){
                throw Exception(ESRCH, __func__);
            }
            return search->second.duration;    
        }

// ================================================================================== //

        uint32_t pctGetProcessAddressSpaceSize(uint32_t pid)
        {
            soProbe(205, "%s(%d)\n", __func__, pid);

            require(pid > 0, "process ID must be non-zero");

            auto search = pct::pctable.find(pid);
            if(search == pct::pctable.end()){
                throw Exception(ESRCH, __func__);
            }
            return search->second.addrSpaceSize;
        }

// ================================================================================== //

        void *pctGetProcessMemAddress(uint32_t pid)
        {
            soProbe(206, "%s(%d)\n", __func__, pid);

            require(pid > 0, "process ID must be non-zero");

            auto search = pct::pctable.find(pid);
            if(search == pct::pctable.end()){
                throw Exception(ESRCH, __func__);
            }
            return search->second.memAddress;
        }

// ================================================================================== //

        const char *pctGetStateName(uint32_t pid)
        {
            soProbe(210, "%s(\"%u\")\n", __func__, pid);

            auto search = pct::pctable.find(pid);
            if(search == pct::pctable.end()){
                throw Exception(ESRCH, __func__);
            }
            return search->second.stateName;
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
