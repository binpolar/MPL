#include "mpl_utils.h"
#include "mpl_pathfinding.h"
#include "mpl_heap.h"
#include "mpl_hashmap.h"

#include <stddef.h>
#include <stdbool.h>

bool mpl_findpath(mpl_node_t *src, mpl_node_t *dst)
{

    mpl_reset_node_costs();
    mpl_heap_reset();

    // Initialize source
    src->best_cost = 0;
    mpl_heap_entry_t tmp = {
        .cost = 0,
        .node = src};
    mpl_heap_push(&tmp);

    while (!mpl_heap_empty())
    {
        mpl_heap_entry_t current_entry;
        bool success = mpl_heap_pop(&current_entry);
        mpl_node_t *current = current_entry.node;

        // lazy Dijkstra
        if (current_entry.cost != current->best_cost)
            continue;

        // Found destination - first time popped guarantees shortest path
        if (current == dst)
            return true;

        // Check all neighbors
        for (int i = 0; i < MPL_MAX_NEIGHBORS && current->edges[i]; i++)
        {
            mpl_edge_t *edge = current->edges[i];

            // Get the neighbor on the other end of this edge
            mpl_node_t *neighbor = (edge->nodes[0] == current) ? edge->nodes[1] : edge->nodes[0];

            // Calculate new cost via current node
            uint32_t new_cost = current->best_cost + edge->link_quality;

            // If we found a better path to neighbor
            if (new_cost < neighbor->best_cost)
            {
                neighbor->best_cost = new_cost;
                neighbor->best_prev_hop = current;
                mpl_heap_entry_t tmp = {.node = neighbor,
                                        .cost = new_cost};
                mpl_heap_push(&tmp);
            }
        }
    }

    return false; // No path found
}