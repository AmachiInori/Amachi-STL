# pragma once
# include <stdlib.h>
# include "AMI_type_traits.h"
# include "AMI_iterator.h"

__ASTL_NAMESPACE_START

class __primary_allocator {
    static void * out_of_memory_malloc(_AMI_size_t __size) {
        void (*handler)() = out_of_memory_handler;
        for (;;) {
            void *tempPtV;
            if (handler == 0) __THROW_BAD_ALLOC;
            handler();
            tempPtV = malloc(__size);
            if (tempPtV != nullptr) return tempPtV;
        }
    }
    static void * out_of_memory_realloc(void* __pointer, _AMI_size_t __size) {
        void (*handler)() = out_of_memory_handler;
        void *tempPtV;
        for (;;) {
            if (handler == 0) __THROW_BAD_ALLOC;
            handler();
            tempPtV = realloc(__pointer, __size);
            if (tempPtV != nullptr) return tempPtV;
        }
    }
    static void (*out_of_memory_handler)();

public:
    static void * allocate(_AMI_size_t __size) {
        void *tempPtV = malloc(__size);
        if (tempPtV == 0) {
            tempPtV = out_of_memory_malloc(__size);
        }
        return tempPtV;
    }
    static void deallocate(void *__pointer, _AMI_size_t) {
        free(__pointer);
    }
    static void * reallocate(void *__pointer, _AMI_size_t, _AMI_size_t __new_size) {
        void *tempPtV = realloc(__pointer, __new_size);
        if (tempPtV == 0) {
            tempPtV = out_of_memory_realloc(__pointer, __new_size);
        }
        return tempPtV;
    }
    static void (*set_OOM_handler(void (*new_oom_handler)()))() {
        void (*oldOOM)() = out_of_memory_handler;
        out_of_memory_handler = new_oom_handler;
        return oldOOM;
    }
};
void (*__primary_allocator::out_of_memory_handler)() = 0;

/****************************************/

class __secondary_allocator {
    union list_node {
        union list_node *next;
        char memory_data[1];
    };
    
    static const _AMI_size_t unit = 8;
    static const _AMI_size_t max_bytes = 128;
    static const _AMI_size_t chain_number = max_bytes / unit;

    static _AMI_size_t __round (_AMI_size_t n) { return ((n) + unit - 1) & ~(unit - 1); }
    static _AMI_size_t __find_list_loca (_AMI_size_t __size) {
        return __size / unit;
    } 
    static union list_node* volatile __main_table[chain_number];

    static char *__memory_pool_start;
    static char *__memory_pool_end;
    static _AMI_size_t __used_heap_size;
    static char *__pool_alloc(_AMI_size_t __size, _AMI_size_t &__got_node_number) {
        _AMI_size_t remain_size = __memory_pool_end - __memory_pool_start;
        _AMI_size_t ask_size = __got_node_number * __size;
        char *result;
        if (remain_size >= ask_size) {
            result = __memory_pool_start;
            __memory_pool_start += ask_size;
            return result;
        } else if (remain_size >= __size) {
            __got_node_number = remain_size / __size;
            ask_size = __got_node_number * __size;
            result = __memory_pool_start;
            __memory_pool_start += ask_size;
            return result;
        } else {
            _AMI_size_t __bytes_to_new = 2 * ask_size + __round(__used_heap_size >> 4);
            if (remain_size > 0) {
                union list_node* volatile *target = __main_table + __find_list_loca(__size);
                union list_node* new_node = (union list_node*)__memory_pool_start;
                new_node->next = *target;
                *target = new_node;
                __memory_pool_start += remain_size;
            }
            __memory_pool_start = (char*)malloc(__bytes_to_new);
            if (__memory_pool_start == 0) {
                union list_node* volatile *target;
                for (size_t i = __size; i <= max_bytes; i += unit) {
                    if (__main_table[__find_list_loca(__size)] != 0) {
                        target = __main_table + __find_list_loca(__size);
                        __memory_pool_start = (char*)*target;
                        __memory_pool_end = ((char*)*target + i);
                        __main_table[__find_list_loca(__size)] = __main_table[__find_list_loca(__size)]->next;
                        return __pool_alloc(__size, __bytes_to_new);
                    }
                }
                __memory_pool_end = 0;
                __memory_pool_start = (char*)__primary_allocator::allocate(__bytes_to_new);
            }
            __used_heap_size += __got_node_number * __size;
            __memory_pool_end = __memory_pool_start + __size;
            return __pool_alloc(__size, __bytes_to_new);
        }
    }
    static void *__refill(_AMI_size_t __size) {
        _AMI_size_t __got_nodes = 32;
        char *newChainHead =  __pool_alloc(__size, __got_nodes);
        if (__got_nodes == 1) return newChainHead;
        void *result = newChainHead;
        for (size_t i = 1; i < __got_nodes; i++) {
            union list_node* currentNode = (union list_node*)(newChainHead + i * __size);
            if (i == 1) {
                currentNode->next = 0;
            } else {
                currentNode->next = (union list_node*)(newChainHead + (i - 1) * __size);
            }
        }
        __main_table[__find_list_loca(__size)] = (union list_node*)(newChainHead + (__got_nodes - 1) * __size);
        return result;
    }
public:
    static void * allocate(_AMI_size_t __size) {
        if (__size > max_bytes) return __primary_allocator::allocate(__size);
        union list_node* volatile *target = __main_table + __find_list_loca(__size);
        union list_node* tempPtC = *target;
        if (tempPtC == 0) {
            void *res = __refill(__round(__size));
            return res;
        }
        *target = tempPtC->next;
        return tempPtC;
    }
    static void deallocate(void *__pointer, _AMI_size_t __size) {
        if (__size > max_bytes) {
            return __primary_allocator::deallocate(__pointer, __size);
        }
        union list_node* volatile *target = __main_table + __find_list_loca(__size);
        union list_node* tempPtN = (union list_node*)__pointer;
        tempPtN->next = *target;
        *target = tempPtN;
    }
};
char *__secondary_allocator::__memory_pool_start = 0;
char *__secondary_allocator::__memory_pool_end = 0;
_AMI_size_t __secondary_allocator::__used_heap_size = 0;
typename __secondary_allocator::list_node * volatile
__secondary_allocator::__main_table[chain_number] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

__ASTL_NAMESPACE_END 