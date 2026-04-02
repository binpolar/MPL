#ifndef MPL_HASHMAP_H_
#define MPL_HASHMAP_H_

#define MPL_MAX_EDGES 511 // must be 2^n minus one for efficient modulus ops!!!

#define MPL_MAX_NODES 255 // must be 2^n minus one for efficient modulus ops!!!

#include <stdint.h>
#include <stdbool.h>

// Hashmap descriptors - FIXED initialization syntax
extern struct cplus_hashmap_desc_t *edge_descriptor;

extern struct cplus_hashmap_desc_t *node_descriptor;

extern struct cplus_hashmap_desc_t *downlinks_descriptor;

void init_maps(void);

// Edge functions
struct mpl_edge_t *mpl_get_edge(mpl_node_t *n1, mpl_node_t *n2);
bool mpl_put_edge(mpl_edge_t *edge);
bool mpl_remove_edge(uint32_t key);
bool mpl_edge_exists(mpl_node_t *n1, mpl_node_t *n2);

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