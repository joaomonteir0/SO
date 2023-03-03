/*
 *  \author ...
 */

#include "somm22.h"
#include "peq_module.h"

namespace somm22
{

    namespace group 
    {

// ================================================================================== //

        const char *peqEventTypeAsString(EventType type)
        {
            soProbe(397, "%s(\"0x%x\")\n", __func__, type);

            /* ACTION POINT: Replace next instruction with your code */
            //throw Exception(ENOSYS, __func__);
            switch(type){
            	case ARRIVAL:
            		return "ARRIVAL";
            		break;
            	case POSTPONED:
            		return "POSTPONED";
            		break;
            	case TERMINATE:
            		return "TERMINATE";
            		break;
            	default:
            		throw Exception(EINVAL, __func__);
        	}
	}
// ================================================================================== //
        /*
        *  \author Joao Rodrigo Faria, n.mec.: 103361
        */

        const char *peqEventMaskAsString(uint32_t mask)
        {
            soProbe(397, "%s(\"0x%x\")\n", __func__, mask);

            require((mask | 0b111) == 0b111, "wrong event mask");

            switch(mask){
                case 0b111:
                    return "ARRIVAL | POSTPONED | TERMINATE";
                    break;
                case 0b110:
                    return "ARRIVAL | POSTPONED";
                    break;
                case 0b011:
                    return "POSTPONED | TERMINATE";
                    break;
                case 0b101:
                    return "ARRIVAL | TERMINATE";
                    break;
                case 0b100:
                    return "ARRIVAL";
                    break;
                case 0b010:
                    return "POSTPONED";
                    break;
                case 0b001:
                    return "TERMINATE";
                    break;
                case 0:
                    return "ANY";
                    break;
                default:
                    throw Exception(EINVAL, __func__);
            }
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

