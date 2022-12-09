#include <stack.h>
#include <stdlib.h>

#include <iostream>

// Add a new node to the stack
void Stack::push(int data) {
    // Create a new node
    Node* new_node = new Node();
    // Set the data of the new node
    new_node->data = data;
    // Set the next node to the top of the stack
    new_node->next = this->top;
    // Set top as new node
    this->top = new_node;
};

// Remove the topmost node from the stack.
void Stack::pop() {
    Node* traverse = this->top;
    top = top->next;
    // Delete the node
    delete traverse;
};

// Return the topmost node of the stack. (itself not value of it)
Node Stack::peek() {
    return *top;
};

// Return the size of the stack
int Stack::size() {
    Node* traverse = top;
    int size = 0;
    while (traverse) {
        size += 1;
        traverse = traverse->next;
    }
    return size;
};

// Print values of all nodes in the stack.
void Stack::print_all() {
    Node* traverse = this->top;
    if (!traverse) {
        std::cout << "Basket is empty." << std::endl;
    }

    while (traverse) {
        std::cout << traverse->data << std::endl;
        traverse = traverse->next;
    }
};

// Return whether stack is empty or not.
bool Stack::is_empty() {
    if (top == nullptr) {
        return true;
    } else {
        return false;
    }
};

// Return whether nodes are sorted from smallest to biggest. (from top to bottom).
bool Stack::is_descending() {
    Node* traverse = this->top;
    if (this->size() > 1) {
        while (traverse->next) {
            if (traverse->data > traverse->next->data) {
                return false;
            }
            traverse = traverse->next;
        }
    }
    return true;
}

// For every two nodes next to each other, check whether their difference is 1. remove second one if it is not.
bool Stack::sequentilized() {
    Node* traverse = this->top;
    Stack* temp_stack = new Stack();
    Node* temp_node;
    while (traverse) {
        if (!temp_stack->top) {
            // Set the new node
            Node* new_node = traverse;
            temp_node = traverse->next;
            // Set the next node to the top of the stack
            new_node->next = temp_stack->top;
            // Set top as new node
            temp_stack->top = new_node;
            traverse = temp_node;
        } else {
            if (traverse->data - temp_stack->top->data == 1) {
                // Set the new node
                Node* new_node = traverse;
                temp_node = traverse->next;
                // Set the next node to the top of the stack
                new_node->next = temp_stack->top;
                // Set top as new node
                temp_stack->top = new_node;
                traverse = temp_node;
            } else {
                temp_node = traverse->next;
                // Delete node
                delete traverse;
            }
            traverse = temp_node;
        }
    }
    traverse = temp_stack->top;
    this->top = nullptr;
    while (traverse) {
        // Set the new node
        Node* new_node = traverse;
        temp_node = traverse->next;
        // Set the next node to the top of the stack
        new_node->next = this->top;
        // Set top as new node
        this->top = new_node;
        traverse = temp_node;
    }
    // delete temporary stack
    delete temp_stack;
    temp_stack->top = nullptr;
    return true;
};

// Get another basket’s nodes and add them to the basket without breaking the order of the nodes.
bool Stack::merge_basket(Stack* add) {
    // Declare temporary stacks
    Stack* temp_first = new Stack();
    Stack* temp_second = new Stack();

    Node* traverse_first = this->top;
    Node* temp_node_first;

    // Move nodes in the first stack to temporary stack
    while (traverse_first) {
        // Set the new node
        Node* new_node = traverse_first;
        temp_node_first = traverse_first->next;
        // Set the next node to the top of the stack
        new_node->next = temp_first->top;
        // Set top as new node
        temp_first->top = new_node;
        traverse_first = temp_node_first;
    }
    traverse_first = temp_first->top;
    this->top = nullptr;

    Node* traverse_second = add->top;
    Node* temp_node_second;

    // Move nodes in the second stack to temporary stack
    while (traverse_second) {
        // Set the new node
        Node* new_node = traverse_second;
        temp_node_second = traverse_second->next;
        // Set the next node to the top of the stack
        new_node->next = temp_second->top;
        // Set top as new node
        temp_second->top = new_node;
        traverse_second = temp_node_second;
    }
    traverse_second = temp_second->top;
    add->top = nullptr;

    // Find total size of temporary stacks to define limit of for loop
    int total_size = temp_first->size() + temp_second->size();

    // Iterate in temporary stacks
    for (int i = 0; i < total_size; i++) {
        // If both stacks have node
        if (traverse_first && traverse_second) {
            // If data of the node in the first stack
            if (traverse_first->data >= traverse_second->data) {
                // Set the new_node
                Node* new_node = traverse_first;
                temp_node_first = traverse_first->next;
                // Set the next_node to the top of the stack
                new_node->next = this->top;
                // Set top as new node
                this->top = new_node;
                traverse_first = temp_node_first;
            }
            // If data of the node in the second stack
            else if (traverse_second->data > traverse_first->data) {
                // Set the new_node
                Node* new_node = traverse_second;
                temp_node_second = traverse_second->next;
                // Set the next_node to the top of the stack
                new_node->next = this->top;
                // Set top as new node
                this->top = new_node;
                traverse_second = temp_node_second;
            }
        }
        // If one of the stacks is empty
        else {
            // If first stack has node
            if (traverse_first) {
                // Set the new_node
                Node* new_node = traverse_first;
                temp_node_first = traverse_first->next;
                // Set the next node to the top of the stack
                new_node->next = this->top;
                // Set top as new node
                this->top = new_node;
                traverse_first = temp_node_first;
            }
            // If the second stack has node
            else if (traverse_second) {
                // Set the new_node
                Node* new_node = traverse_second;
                temp_node_second = traverse_second->next;
                // Set the next node to the top of the stack
                new_node->next = this->top;
                // Set top as new node
                this->top = new_node;
                traverse_second = temp_node_second;
            }
        }
    }
    // Delete temporary stacks
    delete temp_first;
    delete temp_second;
    return true;
};