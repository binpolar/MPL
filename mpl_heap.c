#include "mpl_utils.h"
#include "mpl_heap.h"
#include "cplus_heap.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// Storage for heap entries
static mpl_heap_entry_t heap_storage[MPL_MAX_HEAP_SIZE];

// Heap descriptor
static cplus_heap_desc_t heap_desc;

// Auto-initialization
__attribute__((constructor)) static void init_heap(void)
{
    heap_desc.data = heap_storage;
    heap_desc.data_size = sizeof(mpl_heap_entry_t);
    heap_desc.max_size = MPL_MAX_HEAP_SIZE;
    cplus_heap_init(&heap_desc);
}

bool mpl_heap_push(mpl_heap_entry_t *node)
{
    if (!node)
        return false;
    return cplus_heap_push(&heap_desc, (cplus_heap_entry_t *)node);
}

bool mpl_heap_pop(mpl_heap_entry_t *out_element)
{
    if (!out_element)
        return false;
    return cplus_heap_pop(&heap_desc, (cplus_heap_entry_t *)out_element);
}

bool mpl_heap_peek(mpl_heap_entry_t *out_element) // Optional: peek at min without popping
{
    if (!out_element || cplus_heap_empty(&heap_desc))
    {
        return false;
    }

    // Get root without popping
    cplus_heap_entry_t *root = (cplus_heap_entry_t *)heap_desc.data; // Index 1 in 1-based heap
    memcpy(out_element, root, sizeof(mpl_heap_entry_t));
    return true;
}

bool mpl_heap_empty(void)
{
    return cplus_heap_empty(&heap_desc);
}

uint16_t mpl_heap_size(void) // Optional: get current size
{
    return heap_desc.last_idx - 1; // last_idx is 1-based, so subtract 1
}

bool mpl_heap_full(void) // Optional: check if heap is full
{
    return heap_desc.last_idx >= heap_desc.max_size;
}

void mpl_heap_reset(void)
{
    cplus_heap_reset(&heap_desc);
}

// Debug/utility function to print heap (optional)
void mpl_heap_dump(void)
{
    printf("Heap (size=%d): ", mpl_heap_size());
    for (int i = 1; i < heap_desc.last_idx; i++)
    {
        mpl_heap_entry_t *entry = (mpl_heap_entry_t *)((uint8_t *)heap_desc.data +
                                                       (i * heap_desc.data_size));
        printf("[%d] ", entry->cost);
    }
    printf("\n");
}