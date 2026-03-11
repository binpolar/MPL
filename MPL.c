#include "MPL.h"
#include "mpl_utils.h"
#include "mpl_hashmap.h"
#include "mpl_pathfinding.h"
#include "cplus/include/cplus_utils.h"

#include <stdint.h>
#include <stdbool.h>

void mpl_init(void); // TODO reset nw data structures

bool mpl_create_edge_if_not_exist(mpl_node_t *node1, mpl_node_t *node2, uint8_t quality)
{
    uint16_t smallest = node1->address < node2->address ? node1->address : node2->address;
    uint16_t biggest = smallest == node1->address ? node2->address : node1->address;

    uint32_t edge_hash = cplus_hash_func(smallest | biggest << 16);

    mpl_edge_t edge;
    edge.addresses_hash = edge_hash; // TODO rename, use cooler curly bras init
    edge.link_quality = quality;
    edge.nodes[0] = node1;
    edge.nodes[1] = node2;
    return mpl_put_edge(&edge);
}

bool mpl_find_route(uint32_t src_addr, uint32_t dest_addr, mpl_route_t *route)
{
    mpl_node_t *src = mpl_get_node(src_addr);
    mpl_node_t *dest = mpl_get_node(dest_addr);

    if (!src || !dest)
        return false;

    // Run Dijkstra
    if (!mpl_findpath(src, dest))
        return false;

    // Reconstruct path walking backwards from dest to src
    return mpl_trace_route(dest, src, route);
}