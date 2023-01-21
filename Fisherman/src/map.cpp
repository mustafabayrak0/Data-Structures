#include <map.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>

// Read the txt and return topmost island of the map
Island* Map::create_map(int* data, int length) {
    // Create a pointer to store first element of the array
    int* head = data;
    // Store previous Island
    Island* temp = nullptr;
    // Topmost Island
    Island* top = nullptr;
    // Traverse the array and create islands
    for (int i = 0; i < length; i++) {
        // Create new island object
        Island* new_island = new Island();
        // Assign Id to island
        new_island->id = data[0];
        // Assign fish count to island
        new_island->fish_count = data[1];
        // If top island is not assigned
        if (top == nullptr) {
            // Set current island as top island
            top = new_island;
            // Set temp island
            temp = top;
        }
        if (temp != nullptr) {
            temp->next = new_island;
        }
        // Move temp variable to next island
        temp = temp->next;
        // Move pointer to the first element of the next row
        data += 4;
    }
    // Go back to the first element of the array
    data = head;
    // Variable to traverse islands
    Island* traverse = top;
    // Assign temp to top again
    temp = top;

    // Traverse the array and move islands to the correct positions
    while (traverse) {
        // Go back to the first element of the array
        data = head;
        // Traverse the array
        for (int i = 0; i < length; i++) {
            if (traverse->id == data[0]) {
                if (data[2] != 0) {
                    while (temp) {
                        // If id of the island matches with the id of the south west island
                        if (temp->id == data[2]) {
                            traverse->south_west = temp;
                            break;
                        }
                        temp = temp->next;
                    }
                }
                // Set temp to top again
                temp = top;
                if (data[3] != 0) {
                    while (temp) {
                        // If id of the island matches with the id of the south east island
                        if (temp->id == data[3]) {
                            traverse->south_east = temp;
                            break;
                        }
                        // Move temp to the next island
                        temp = temp->next;
                    }
                }
                temp = top;
                break;
            }
            // Go to the next row
            data += 4;
        }
        // Move traverse to the next island
        traverse = traverse->next;
    }
    return top;
}

// Print the map In-order traversal
void Map::print_map(Island* top) {
    // If top is null return
    if (top == nullptr) {
        return;
    }
    // Traverse left
    print_map(top->south_west);
    // Print current island
    std::cout << "Island ID: " << top->id << ", Fish Count: " << top->fish_count << std::endl;
    // Traverse right
    print_map(top->south_east);
}

void Map::find_max(Island* island, Island* before) {
    // If island is null return
    if (island == nullptr) {
        return;
    }
    // If island is leaf node
    if (island->south_east == nullptr && island->south_west == nullptr) {
        this->max_fish_count = std::max(this->max_fish_count, before->total_fishes + island->fish_count);
    } else {
        // If island is head
        if (island == this->head) {
            island->total_fishes = island->fish_count;
        }
        // If island is not head
        else {
            island->total_fishes = before->total_fishes + island->fish_count;
        }
    }

    // Traverse left
    find_max(island->south_west, island);
    // Traverse right
    find_max(island->south_east, island);
}
// Empty the map
void Map::empty_map(Island* top) {
    if (top == nullptr) {
        return;
    }
    // Traverse left
    empty_map(top->south_west);
    // Traverse right
    empty_map(top->south_east);
    // Delete island
    delete top;
}