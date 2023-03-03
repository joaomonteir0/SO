/*
 *  \author ...
 */

#include "somm22.h"
#include "sim_module.h"

namespace somm22
{

    namespace group
    {

// ================================================================================== //

        /*
         * Solution may be based on a state machine with two states, which are related to the
         * type of events that are fetched from the Process Event Queue.
         * The meaningful cases are:
         * - ARRIVAL | TERMINATE
         * - POSTPONED
         */
    
        void simStep(Event event){
            uint32_t pid = event.pid;
            uint32_t req = pctGetProcessAddressSpaceSize(pid);
            sim::currentTime = event.eventTime;

            switch (event.eventType){
            case POSTPONED:
                if (req > memGetMaxAllowableSize()) pctSetProcessState(pid, ProcessState::DISCARDED);
                else{
                    pctSetProcessState(pid, ProcessState::RUNNING);
                    pctSetProcessStartTime(pid, simGetCurrentSimTime());
                    pctSetProcessMemAddress(pid, memAlloc(pid,req));
                    peqInsert(EventType::TERMINATE, pctGetProcessDuration(pid), pid);
                    sim::current_event_mask = ARRIVAL | TERMINATE;
                } 
                break;
            case ARRIVAL:
                if (req > memGetMaxAllowableSize()) pctSetProcessState(pid, ProcessState::DISCARDED);
                else{
                    if (req > memGetBiggestHole() || peqGetFirstPostponedProcess() != 0){
                        pctSetProcessState(pid, ProcessState::SWAPPED);
                        // pctSetProcessStartTime(pid, simGetCurrentSimTime());
                        // pctSetProcessMemAddress(pid, memAlloc(pid,req));
                        peqInsert(EventType::POSTPONED, pctGetProcessDuration(pid), pid);
                    }else{
                        pctSetProcessState(pid, ProcessState::RUNNING);
                        pctSetProcessStartTime(pid, simGetCurrentSimTime());
                        pctSetProcessMemAddress(pid, memAlloc(pid,req));
                        peqInsert(EventType::TERMINATE, pctGetProcessDuration(pid), pid);
                        sim::current_event_mask = ARRIVAL | TERMINATE;
                    }
                }
                break;
            case TERMINATE:{
                pctSetProcessState(pid, ProcessState::FINISHED);
                memFree(pctGetProcessMemAddress(pid));
                uint32_t getpid = peqGetFirstPostponedProcess();
                if(getpid != 0) if (pctGetProcessAddressSpaceSize(getpid) <= memGetBiggestHole()) sim::current_event_mask = POSTPONED;
                break;
            }
                
            default:
                break;
            }
        }

        void simRun(uint32_t cnt)
        {
            soProbe(503, "%s(cnt: %u)\n", __func__, cnt);
            
            if (cnt == 0){
                while(!peqIsEmpty()){
                    simStep(peqFetchNext(simGetCurrentSimMask()));
                    ++sim::steps_processed;
                }
            }else{
                while(sim::steps_processed++ != cnt){
                    simStep(peqFetchNext(simGetCurrentSimMask()));
                }
                sim::steps_processed = 0;
            }
            
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
