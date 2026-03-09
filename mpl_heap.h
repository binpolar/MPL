#ifndef MPL_HEAP_H_
#define MPL_HEAP_H_

#define MPL_MAX_HEAP_SIZE 1023 // must be 2^n - 1 for some n

bool mpl_heap_push(mpl_heap_entry_t *node);
bool mpl_heap_pop(mpl_heap_entry_t *out_element);

bool mpl_heap_empty();
void mpl_heap_reset(void);

#endif