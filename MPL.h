#ifndef _MPL_H_
#define _MPL_H_

#include <stdint.h>
#include <stdbool.h>

struct mpl_node_t;
struct mpl_route_t;

void mpl_init(void); // resets nw data structures

bool mpl_create_or_update_edge(struct mpl_node_t *node1, struct mpl_node_t *node2, uint8_t quality);

bool mpl_create_node_if_not_exist(uint32_t addr1, uint32_t addr2, uint8_t quality);

bool mpl_find_route(uint32_t src_addr, uint32_t dest_addr, struct mpl_route_t *route);

#endif