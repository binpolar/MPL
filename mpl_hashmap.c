#include "mpl_utils.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "mpl_hashmap.h"
#include "cplus_hashmap.h"

// Storage arrays
mpl_edge_t mpl_edges[MPL_MAX_EDGES];
mpl_node_t mpl_nodes[MPL_MAX_NODES];
mpl_route_t mmpl_routes[MPL_MAX_NODES];

// Hashmap descriptors - FIXED initialization syntax
cplus_hashmap_desc_t tedge_descriptor = {
    .data = mpl_edges,
    .data_size = sizeof(mpl_edge_t),
    .data_length = MPL_MAX_EDGES};

cplus_hashmap_desc_t tnode_descriptor = {
    .data = mpl_nodes,
    .data_size = sizeof(mpl_node_t),
    .data_length = MPL_MAX_NODES};

cplus_hashmap_desc_t troutes_descriptor = {
    .data = mmpl_routes,
    .data_size = sizeof(mpl_route_t),
    .data_length = MPL_MAX_NODES};

cplus_hashmap_desc_t *routes_descriptor, *node_descriptor, *edge_descriptor;

// Auto-initialization doesnt work on msvc
/*__attribute__((constructor)) static*/ void init_maps(void)
{
    routes_descriptor = &troutes_descriptor;
    node_descriptor = &tnode_descriptor;
    edge_descriptor = &tedge_descriptor;
    cplus_hashmap_init(edge_descriptor);
    cplus_hashmap_init(node_descriptor);
    cplus_hashmap_init(routes_descriptor);
}

// Edge functions
mpl_edge_t *mpl_get_edge(mpl_node_t *n1, mpl_node_t *n2)
{
    return (mpl_edge_t *)cplus_hashmap_get(edge_descriptor, mpl_get_edge_key(n1, n2));
}

mpl_edge_t *mpl_put_edge(mpl_edge_t *edge) // Changed to pointer
{
    if (!edge)
        return false;
    return cplus_hashmap_put(edge_descriptor, edge);
}

bool mpl_remove_edge(uint32_t key) // Fixed: use cplus_hashmap_remove
{
    return cplus_hashmap_remove(edge_descriptor, key);
}

bool mpl_edge_exists(mpl_node_t *n1, mpl_node_t *n2)
{
    return cplus_hashmap_exists(edge_descriptor, mpl_get_edge_key(n1, n2));
}

// Node functions
mpl_node_t *mpl_get_node(uint32_t key)
{
    return (mpl_node_t *)cplus_hashmap_get(node_descriptor, key);
}

mpl_node_t *mpl_put_node(mpl_node_t *node) // Fixed function name and parameter
{
    if (!node)
        return false;
    return cplus_hashmap_put(node_descriptor, node);
}

bool mpl_remove_node(uint32_t address)
{
    return (mpl_node_t *)cplus_hashmap_remove(node_descriptor, address);
}

bool mpl_node_exists(uint32_t address)
{
    return cplus_hashmap_exists(node_descriptor, address);
}

void mpl_reset_node_costs()
{
    // Initialize all nodes (reset from previous runs)
    for (int i = 0; i < MPL_MAX_NODES; i++)
    {
        // Only reset if node exists in topology
        if (mpl_nodes[i].is_valid)
        {
            mpl_nodes[i].best_cost = UINT32_MAX;
            mpl_nodes[i].best_prev_hop = NULL;
        }
    }
}

// Helper functions
uint16_t mpl_edge_count(void)
{
    uint32_t count = 0;
    for (int i = 0; i < MPL_MAX_EDGES; i++)
    {
        if (mpl_edges[i].is_valid)
            count++;
    }
    return count;
}

uint16_t mpl_node_count(void)
{
    uint32_t count = 0;
    for (int i = 0; i < MPL_MAX_NODES; i++)
    {
        if (mpl_nodes[i].is_valid)
            count++;
    }
    return count;
}

uint16_t mpl_route_count(void)
{
    uint32_t count = 0;
    for (int i = 0; i < MPL_MAX_NODES; i++)
    {
        if (mmpl_routes[i].is_valid)
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

// dolwnlinksk functions
mpl_route_t *mpl_get_route(uint32_t key)
{
    return (mpl_route_t *)cplus_hashmap_get(routes_descriptor, key);
}

mpl_route_t *mpl_put_route(mpl_route_t *route)
{
    if (!route)
        return false;
    return (mpl_route_t *)cplus_hashmap_put(routes_descriptor, route);
}

bool mpl_remove_route(uint32_t key) // Fixed: use cplus_hashmap_remove
{
    return cplus_hashmap_remove(routes_descriptor, key);
}

bool mpl_route_exists(uint32_t key)
{
    return cplus_hashmap_exists(routes_descriptor, key);
}