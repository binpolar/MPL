#ifndef _MPL_H_
#define _MPL_H_

#include <stdint.h>
#include <stdbool.h>

struct mpl_node_t;
struct mpl_route_t;

void mpl_init(void); // resets nw data structures

bool mpl_create_or_update_edge(struct mpl_node_t *node1, struct mpl_node_t *node2, uint8_t quality);

bool mpl_create_node_if_not_exists(uint32_t addr);

struct mpl_route_t * mpl_find_route(struct mpl_node_t *src, struct mpl_node_t *dest);

#endif