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

        void memFree(void *addr)
        {
            soProbe(408, "%s(addr: %p)\n", __func__, addr);

            require(addr != NULL, "addr must be non-null");
            
            /* ACTION POINT: Replace next instruction with your code */
            
            uint32_t size = 0;
            
            if (mem::busy_list->start==addr) {
                size = mem::busy_list->size;
                mem::busy_list = mem::busy_list->next;
            }
            else {
                mem::Memory** prev = &(mem::busy_list);
                mem::Memory** busy_temp = &(mem::busy_list->next);
                while ((*busy_temp)->start!=addr) {
                    prev = busy_temp;
                    busy_temp = &(*busy_temp)->next;
                }
                size = (*busy_temp)->size;
                (*prev)->next = (*busy_temp)->next;
            }
            
            mem::Memory* node = new mem::Memory();
            node->pid = 0;
            node->start = addr;
            node->size = size;
            node->next = NULL;
            
            mem::Memory** free_temp;
            if (mem::free_list==NULL || mem::free_list->start>addr) {
                node->next = mem::free_list;
                mem::free_list = node;
            }
            else {
                free_temp = &(mem::free_list);
                while ((*free_temp)->next!=NULL && (*free_temp)->next->start<addr) {
                    free_temp = &(*free_temp)->next;
                }
                if ((*free_temp)->next!=NULL) {
                    node->next = (*free_temp)->next;
                }
                (*free_temp)->next = node;
            }
            
            free_temp = &(mem::free_list);
            while (*free_temp!=NULL && (*free_temp)->next!=NULL) {
                if ((*free_temp)->next->start==(void*)((intptr_t)(*free_temp)->start + (intptr_t)(*free_temp)->size)) {
                    (*free_temp)->size = (*free_temp)->size + (*free_temp)->next->size;
                    (*free_temp)->next = (*free_temp)->next->next;
                    free_temp = &(mem::free_list);
                }
                else free_temp = &(*free_temp)->next;
            }
        }

// ================================================================================== //

    } // end of namespace group

} // end of namespace somm22

