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

        void *memBestFitAlloc(uint32_t pid, uint32_t size)
        {
            soProbe(406, "%s(%u, 0x%x)\n", __func__, pid, size);

            require(pid > 0, "process ID must be non-zero");
            
            /* ACTION POINT: Replace next instruction with your code */
            mem::Memory* free_temp = mem::free_list;
            mem::Memory* min = NULL;
            while (free_temp!=NULL) {
                if (free_temp->size>=size && (min==NULL || free_temp->size<min->size)) {
                    min = free_temp;
                }
                free_temp = free_temp->next;
            }
            free_temp = min;
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
