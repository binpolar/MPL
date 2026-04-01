#include "mpl_utils.h"
#include <stdbool.h>

bool mpl_trace_route(mpl_node_t *dest, mpl_node_t *src, mpl_route_t *res)
{
    mpl_node_t *current = dest;
    uint8_t count = 0;
    // Walk backwards to count hops
    while (current && current != src)
    {
        count++;
        current = current->best_prev_hop;
    }

    if (!current)
        return false; // No path found
    count++;          // Include source

    res->hop_count = count;
    res->total_cost = dest->best_cost;

    // Fill array in forward order
    current = dest;
    for (int i = count - 1; i >= 0; i--)
    {
        res->hops[i] = current->address;
        current = current->best_prev_hop;
    }
}

uint32_t mpl_get_edge_key(mpl_node_t *n1, mpl_node_t *n2)
{
    uint16_t smallest = n1->address < n2->address ? n1->address : n2->address;
    uint16_t biggest = smallest == n1->address ? n2->address : n1->address;

    uint32_t edge_hash = smallest | (biggest << 16);
    return edge_hash;
}