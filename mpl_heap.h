#ifndef MPL_HEAP_H_
#define MPL_HEAP_H_

#define MPL_MAX_HEAP_SIZE 1023 //must be 2^n - 1 for some n


void mpl_heap_push(struct mpl_heap_entry_t node);
struct mpl_heap_entry_t mpl_heap_pop();

bool mpl_heap_empty();
void mpl_heap_reset(void);

#endif