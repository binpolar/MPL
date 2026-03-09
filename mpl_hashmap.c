#include "mpl_utils.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "mpl_hashmap.h"
#include "cplus_hashmap.h"

// Storage arrays
mpl_edge_t edges[MPL_MAX_EDGES];
mpl_node_t nodes[MPL_MAX_NODES];

// Hashmap descriptors - FIXED initialization syntax
cplus_hashmap_desc_t edge_descriptor = {
    .data = edges,
    .data_size = sizeof(mpl_edge_t),
    .data_length = MPL_MAX_EDGES};

cplus_hashmap_desc_t node_descriptor = {
    .data = nodes,
    .data_size = sizeof(mpl_node_t),
    .data_length = MPL_MAX_NODES};

// Auto-initialization
__attribute__((constructor)) static void init_maps(void)
{
    cplus_hashmap_init(&edge_descriptor);
    cplus_hashmap_init(&node_descriptor);
}

// Edge functions
mpl_edge_t *mpl_get_edge(uint32_t key)
{
    return (mpl_edge_t *)cplus_hashmap_get(&edge_descriptor, key);
}

bool mpl_put_edge(mpl_edge_t *edge) // Changed to pointer
{
    if (!edge)
        return false;
    return cplus_hashmap_put(&edge_descriptor, edge);
}

bool mpl_remove_edge(uint32_t key) // Fixed: use cplus_hashmap_remove
{
    return cplus_hashmap_remove(&edge_descriptor, key);
}

bool mpl_edge_exists(uint32_t key)
{
    return cplus_hashmap_exists(&edge_descriptor, key);
}

// Node functions
mpl_node_t *mpl_get_node(uint32_t key)
{
    return (mpl_node_t *)cplus_hashmap_get(&node_descriptor, key);
}

bool mpl_put_node(mpl_node_t *node) // Fixed function name and parameter
{
    if (!node)
        return false;
    return cplus_hashmap_put(&node_descriptor, node);
}

bool mpl_remove_node(uint32_t address)
{
    return cplus_hashmap_remove(&node_descriptor, address);
}

bool mpl_node_exists(uint32_t address)
{
    return cplus_hashmap_exists(&node_descriptor, address);
}

void mpl_reset_node_costs()
{
    // Initialize all nodes (reset from previous runs)
    for (int i = 0; i < MPL_MAX_NODES; i++)
    {
        // Only reset if node exists in topology
        if (nodes[i].is_valid)
        {
            nodes[i].best_cost = UINT32_MAX;
            nodes[i].best_prev_hop = NULL;
        }
    }
}

// Helper functions
uint32_t mpl_edge_count(void)
{
    uint32_t count = 0;
    for (int i = 0; i < MPL_MAX_EDGES; i++)
    {
        if (edges[i].is_valid)
            count++;
    }
    return count;
}

uint32_t mpl_node_count(void)
{
    uint32_t count = 0;
    for (int i = 0; i < MPL_MAX_NODES; i++)
    {
        if (nodes[i].is_valid)
            count++;
    }
    return count;
}

bool mpl_edges_full(void)
{
    return mpl_edge_count() >= MPL_MAX_EDGES;
}

bool mpl_nodes_full(void)
{
    return mpl_node_count() >= MPL_MAX_NODES;
}

// Reset functions
void mpl_clear_edges(void)
{
    cplus_heap_reset(&edge_descriptor); // or however you clear the hashmap
}

void mpl_clear_nodes(void)
{
    cplus_heap_reset(&node_descriptor); // or however you clear the hashmap
}