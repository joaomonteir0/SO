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

        void *memWorstFitAlloc(uint32_t pid, uint32_t size)
        {
            soProbe(407, "%s(%u, 0x%x)\n", __func__, pid, size);

            require(pid > 0, "process ID must be non-zero");
            
            /* ACTION POINT: Replace next instruction with your code */
            mem::Memory* free_temp = mem::free_list;
            mem::Memory* max = NULL;
            while (free_temp!=NULL) {
                if (free_temp->size>=size && (max==NULL || free_temp->size>max->size)) {
                    max = free_temp;
                }
                free_temp = free_temp->next;
            }
            free_temp = max;
            void* addr = free_temp->start;
            free_temp->start = (void*)((intptr_t)free_temp->start + (intptr_t)size);
            free_temp->size = free_temp->size - size;
            
            mem::Memory* node = new mem::Memory();
            node->pid = pid;
            node->start = addr;
            node->size = size;
            node->next = NULL;
            
            if (mem::busy_list==NULL || mem::busy_list->start>addr) {
                node->next = mem::busy_list;
                mem::busy_list = node;
                return addr;
            }
            
            mem::Memory** busy_temp = &(mem::busy_list);
            while ((*busy_temp)->next!=NULL && (*busy_temp)->next->start<addr) {
                busy_temp = &(*busy_temp)->next;
            }
            if ((*busy_temp)->next!=NULL) {
                node->next = (*busy_temp)->next;
            }
            (*busy_temp)->next = node;
            return addr;
        }


// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22
