//--- 2022-2023 Fall YZV201E Assignment 1 ---//
//--------------------------//
//---Name & Surname: Mustafa Bayrak
//---Student Number: 150210339
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//

#include <WordList.h>

#include <iostream>  // For input/output operations

//-------------Word Methods-------------//

Word::Word() {
    word_ = "";
    edit_dist_ = 999;  // An arbitrary number to set the distance as infinite
    next_ = NULL;
}

Word::Word(std::string vocab_word) {
    word_ = vocab_word;
    edit_dist_ = 999;  // An arbitrary number to set the distance as infinite
    next_ = NULL;
}

//-------------WordList Methods-------------//

WordList::WordList() {
    this->head_ = NULL;
}

WordList::~WordList() {
    Word *traverse = head_;

    // To make sure that we clear the memory when the program ends.
    while (traverse != NULL) {
        Word *temp = traverse;
        traverse = traverse->next_;
        delete temp;
    }
}

void WordList::AddWord(std::string word) {
    Word *new_word = new Word(word);
    if (head_ == NULL) {
        head_ = new_word;  // If the list is empty, add the word to the head.
        tail_ = new_word;  // If the list is empty, add the word to the tail.
    } else {
        tail_->next_ = new_word;  // If the list is not empty, add the word to the tail.
        tail_ = new_word;         // If the list is not empty, add the word to the tail.
    }
}

void WordList::PrintWords(int n) {
    Word *traverse = head_;
    int i = 0;
    while (traverse->next_ != NULL && i < n) {
        std::cout << traverse->word_ << std::endl;  // Print the word
        traverse = traverse->next_;
        i++;
    }
}

void WordList::CalcEditDists(std::string miss_word) {
    Word *traverse = new Word();
    traverse = this->head_;
    while (traverse->next_ != NULL) {
        int m = miss_word.length();        // Length of the misspelled word
        int n = traverse->word_.length();  // Length of the word in the list
        std::string word = traverse->word_;
        int D[n + 1][m + 1];
        D[0][0] = 0;
        for (int i = 1; i < m + 1; i++) {
            D[0][i] = D[0][i - 1] + 1;
        }
        for (int i = 1; i < n + 1; i++) {
            D[i][0] = D[i - 1][0] + 1;
        }
        for (int i = 1; i < n + 1; i++) {
            for (int j = 1; j < m + 1; j++) {
                D[i][j] = std::min(D[i - 1][j] + 1, D[i][j - 1] + 1);
                D[i][j] = std::min(D[i][j], D[i - 1][j - 1] + traverse->SubsCost(word[i - 1], miss_word[j - 1]));
            }
        }
        traverse->edit_dist_ = D[n][m];  // Set the edit distance of the word in the list
        traverse = traverse->next_;      // Go to the next word in the list
    }
}

void WordList::PrintEditDists(int count) {
    Word *traverse = head_;
    int i = 0;
    while (traverse->next_ != NULL && i < count) {
        std::cout << traverse->edit_dist_ << std::endl;
        traverse = traverse->next_;
        i++;
    }
}

void WordList::SuggestWords(int count) {
    Word *traverse = head_;
    int length = 0;
    while (traverse->next_ != NULL) {
        length++;                    // Find the length of the list
        traverse = traverse->next_;  // Go to the next word in the list
    }
    traverse = head_;                     // Go back to the head of the list
    int distances_array[length];          // Create an array to store the distances
    std::string words_array[length + 1];  // Create an array to store the words
    int ind = 0;

    while (traverse->next_ != NULL) {
        distances_array[ind] = traverse->edit_dist_;
        words_array[ind] = traverse->word_;
        ind++;
        traverse = traverse->next_;
    }

    // Iterate the array
    for (int i = 0; i < count; i++) {
        int min = 999;  // An arbitrary number to set the minimum as infinite
        int index = -1;
        for (int j = 0; j < length; j++) {
            if (distances_array[j] < min) {
                min = distances_array[j];
                index = j;
            }
        }
        distances_array[index] = 999;                  // Set the minimum as infinite
        std::cout << words_array[index] << std::endl;  // Print the word
    }
}

int Word::SubsCost(char a, char b) {
    if (a == b) {
        return 0;  // If the characters are the same, return 0
    } else {
        return 2;  // If the characters are different, return 2
    }
}