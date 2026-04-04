#ifndef MPL_HASHMAP_H_
#define MPL_HASHMAP_H_

#define MPL_MAX_EDGES 511 // must be 2^n minus one for efficient modulus ops!!!

#define MPL_MAX_NODES 255 // must be 2^n minus one for efficient modulus ops!!!

#include <stdint.h>
#include <stdbool.h>

// Hashmap descriptors - FIXED initialization syntax
extern struct cplus_hashmap_desc_t *edge_descriptor;

extern struct cplus_hashmap_desc_t *node_descriptor;

extern struct cplus_hashmap_desc_t *routes_descriptor;

void init_maps(void);

struct mpl_node_t;
struct mpl_edge_t;

// Edge functions
struct mpl_edge_t *mpl_get_edge(struct mpl_node_t *n1,struct mpl_node_t *n2);
struct mpl_edge_t *mpl_put_edge(struct mpl_edge_t *edge);
bool mpl_remove_edge(uint32_t key);
bool mpl_edge_exists(struct mpl_node_t *n1,struct mpl_node_t *n2);

// routes functions
struct mpl_route_t *mpl_get_route(uint32_t key);
struct mpl_route_t *mpl_put_route(struct mpl_route_t *route);
bool mpl_remove_route(uint32_t key);
bool mpl_route_exists(uint32_t key);

// Node functions
struct mpl_node_t *mpl_get_node(uint32_t address);
struct mpl_node_t *mpl_put_node(struct mpl_node_t *node);
bool mpl_remove_node(uint32_t address);
bool mpl_node_exists(uint32_t address);
void mpl_reset_node_costs();

// Status functions
bool mpl_edges_full(void);
bool mpl_nodes_full(void);
uint16_t mpl_edge_count(void);
uint16_t mpl_node_count(void);
uint16_t mpl_route_count(void);


#endif