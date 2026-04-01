#ifndef MPL_UTILS_H_
#define MPL_UTILS_H_
#include <stdbool.h>
#include <stdint.h>

#define MPL_MAX_NEIGHBORS 16
#define MPL_MAX_ROUTE_LEN 32

typedef struct mpl_route_t
{
    uint16_t hops[MPL_MAX_ROUTE_LEN];
    uint8_t hop_count;
    uint32_t total_cost;
} mpl_route_t;

typedef struct mpl_edge_t
{
    uint32_t addresses_hash;
    bool is_valid;

    struct mpl_node_t *nodes[2]; // in future may wanna use 8 bit indices instead
    uint8_t link_quality;

} mpl_edge_t;

typedef struct mpl_node_t
{
    uint32_t address;
    bool is_valid;

    mpl_edge_t *edges[MPL_MAX_NEIGHBORS];
    struct mpl_node_t *best_prev_hop;

    uint32_t best_cost;

} mpl_node_t;

typedef struct mpl_heap_entry_t
{
    uint32_t cost;
    mpl_node_t *node;

} mpl_heap_entry_t;

// TODO CHECK STRUCTs MEM LAYOUT TO MATCH CPLUS ENTRIES Ts

bool mpl_trace_route(mpl_node_t *dest, mpl_node_t *src, mpl_route_t *res);
uint32_t mpl_get_edge_key(mpl_node_t *n1, mpl_node_t *n2);

void mpl_add_edge_to_node(mpl_node_t *node, mpl_edge_t *edge);

#endif