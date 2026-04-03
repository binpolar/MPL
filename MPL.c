#include "MPL.h"
#include "mpl_utils.h"
#include "mpl_hashmap.h"
#include "mpl_pathfinding.h"
#include "cplus/include/cplus_utils.h"

#include <stdint.h>
#include <stdbool.h>

void mpl_init(void); // TODO reset nw data structures

bool mpl_create_or_update_edge(mpl_node_t *node1, mpl_node_t *node2, uint8_t quality)
{

    mpl_edge_t edge, *created_edge;
    edge.addresses_hash = mpl_get_edge_key(node1, node2); // TODO rename, use cooler curly bras init
    edge.link_quality = quality;
    edge.nodes[0] = node1;
    edge.nodes[1] = node2;

    bool ret = mpl_put_edge(&edge);
    created_edge = mpl_get_edge(node1, node2);

    mpl_add_edge_to_node(node1, created_edge);
    mpl_add_edge_to_node(node2, created_edge);

    return ret;
}

bool mpl_create_node_if_not_exists(uint32_t addr)
{
    mpl_node_t node = {0};
    node.address = addr;

    return mpl_put_node(&node);
}

mpl_route_t * mpl_find_route(mpl_node_t *src, mpl_node_t *dest)
{
    // Run Dijkstra
    if (!mpl_findpath(src, dest))
        return false;

    // Reconstruct path walking backwards from dest to src
    mpl_route_t tmp;

    bool ret = mpl_trace_route(dest, src, &tmp);
    tmp.key = dest->address;
    if(ret){
        return mpl_put_route(&tmp);
    }else{
        return false;
    }
}