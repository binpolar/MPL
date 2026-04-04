#ifndef MPL_HEAP_H_
#define MPL_HEAP_H_

#define MPL_MAX_HEAP_SIZE 1023 // must be 2^n - 1 for some n

void init_heap(void);

struct mpl_heap_entry_t;

bool mpl_heap_push(struct mpl_heap_entry_t *node);
bool mpl_heap_pop(struct mpl_heap_entry_t *out_element);

bool mpl_heap_empty();
void mpl_heap_reset(void);

#endif