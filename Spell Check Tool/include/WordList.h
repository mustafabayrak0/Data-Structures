//--- 2022-2023 Fall YZV201E Assignment 1 ---//
//--------------------------//
//---Name & Surname: Mustafa Bayrak
//---Student Number: 150210339
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//

#include <string>  // For string operations

// Class for nodes of the list
class Word {
   public:
    std::string word_;  // Variable to keep the word
    int edit_dist_;     // Variable to keep the edit distance of that word
    Word* next_;        // Pointer to keep the address of the next node

    // Calculate substituion cost. Return 0 if two letters are same,
    // return 2 otherwise.
    int SubsCost(char, char);
    // Calculate edit distance for a node.
    int EditDist(std::string);

    Word();             // Default consturactor
    Word(std::string);  // Constructor for the given word
};

// Class for the list
class WordList {
   public:
    Word* head_;  // Pointer that points to the first node of the list
    Word* tail_;  // Pointer that points to the last node of the list

    // Add all words to the list
    void AddWord(std::string);
    // Print first "n" words from the list
    void PrintWords(int);
    // Calculate edit distances for all words in the list
    void CalcEditDists(std::string);
    // Print first "n" words' edit distance from the list
    void PrintEditDists(int);
    // Print "n" words that has the lowest edit distance
    void SuggestWords(int);

    WordList();   // Default consturactor
    ~WordList();  // Destructor
};