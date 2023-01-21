class Island {
   public:
    // Id of the island
    int id;
    // Number of fishes in the island
    int fish_count;
    // Island on the left side
    Island *south_west;
    // Island on the right side
    Island *south_east;
    // Next island
    Island *next;
    // Total Fishes till this island
    int total_fishes;
};
class Map {
   public:
    // Head of Map
    Island *head;
    // Read txt file that contains map information
    Island *create_map(int *, int);
    // Print map to the screen
    void print_map(Island *);
    // Find maximum number of fish that the fisherman can catch
    void find_max(Island*,Island*);
    // Empty Map
    void empty_map(Island*);
    // Max fish count
    int max_fish_count;

};