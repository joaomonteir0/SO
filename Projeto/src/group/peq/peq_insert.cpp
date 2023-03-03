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
        bool compare_events(Event left, Event right){
            return left.eventType < right.eventType;
        }

        void peqInsert(EventType type, uint32_t time, uint32_t pid)
        {
            soProbe(304, "%s(%s, %u, %u)\n", __func__, peqEventTypeAsString(type), time, pid);

            require(pid > 0, "process ID must be non-zero");

            /* ACTION POINT: Replace next instruction with your code */
            //throw Exception(ENOSYS, __func__);

            Event n_event;
            n_event.eventTime = time;
            n_event.eventType = type;
            n_event.pid = pid;

            // check if the pid is already in the peqable map
            // if it is, throw an exception
            std::list<Event>::iterator it;
            for(it = peq::peqlist.begin();it != peq::peqlist.end();++it){
                if(it->pid == n_event.pid){
                    throw Exception(EEXIST, __func__);
                }
            }
            peq::peqlist.push_back(n_event);
            peq::peqlist.sort([](Event left, Event right){return left.eventTime < right.eventTime;});
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
