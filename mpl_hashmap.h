#ifndef MPL_HASHMAP_H_
#define MPL_HASHMAP_H_

#define MPL_MAX_EDGES 2047 // must be 2^n minus one for efficient modulus ops!!!

#define MPL_MAX_NODES 4095 // must be 2^n minus one for efficient modulus ops!!!

#include <stdint.h>
#include <stdbool.h>

// Edge functions
struct mpl_edge_t *mpl_get_edge(uint32_t key);
bool mpl_put_edge(mpl_edge_t *edge);
bool mpl_remove_edge(uint32_t key);
bool mpl_edge_exists(uint32_t key);

// downlinks functions
struct mpl_route_t *mpl_get_downlink(uint32_t key);
bool mpl_put_downlink(mpl_edge_t *edge);
bool mpl_remove_downlink(uint32_t key);
bool mpl_downlink_exists(uint32_t key);

// Node functions
struct mpl_node_t *mpl_get_node(uint32_t address);
bool mpl_put_node(struct mpl_node_t *node);
bool mpl_remove_node(uint32_t address);
bool mpl_node_exists(uint32_t address);
void mpl_reset_node_costs();

// Status functions
bool mpl_edges_full(void);
bool mpl_nodes_full(void);
uint16_t mpl_edge_count(void);
uint16_t mpl_node_count(void);

#endif