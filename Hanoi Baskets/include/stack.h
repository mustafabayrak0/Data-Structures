class Node {
   public:
    int data;
    Node *next;
};

class Stack {
   public:
    // topmost Node of Stack
    Node *top;
    // Add a new node to the stack
    void push(int data);
    // Remove the topmost node from the stack.
    void pop();
    // Return the topmost node of the stack.
    Node peek();
    // Return number of nodes in the stack
    int size();
    // Print values of all nodes in the stack
    void print_all();
    //  Return whether stack is empty or not
    bool is_empty();
    // Return whether nodes are sorted from smallest to biggest
    bool is_descending();
    // For every two nodes next to each other, check whether their difference is 1
    bool sequentilized();
    // Get another basket’s nodes and add them to the basket without breaking the order of the nodes
    bool merge_basket(Stack *second);
};
