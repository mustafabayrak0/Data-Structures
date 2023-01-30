/* @Author
 * Student Name: Mustafa Bayrak
 * Student ID : 150210339
 */

/*
 I Added map.txt twice because there was some problems about path.
*/
/* Necessary header files */
#include <map.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

int main() {
    // Open the file
    ifstream file("map.txt");

    // Check if the file opened
    if (!file.is_open()) {
        return 1;
    }

    // Count the number of lines
    int numLines = 0;
    string line;
    while (getline(file, line)) {
        numLines++;
    }

    // Go back to the beginning of the file
    file.clear();
    file.seekg(0, ios::beg);
    int data[numLines][4];

    // Fill the array
    for (int row = 0; row < numLines; row++) {
        for (int col = 0; col < 4; col++) {
            file >> data[row][col];
        }
    }
    // Close the file
    file.close();
    // Create Map object
    Map map;
    // Create a pointer that points to the first element of the array
    int* ptr = &data[0][0];
    // Create the map and return the head of the map
    map.head = map.create_map(ptr, numLines);
    // Print the map
    map.print_map(map.head);
    // Initialize max_fish_count
    map.max_fish_count = 0;
    // Find the maximum number of fish that the fisherman can catch
    map.find_max(map.head, map.head);
    cout << "Max fish count: " << map.max_fish_count << endl;
    // Empty Map
    map.empty_map(map.head);
    return 0;
}
