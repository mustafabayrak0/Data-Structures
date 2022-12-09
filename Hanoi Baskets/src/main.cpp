/* * * * * * * * * * * * * * * * * * * * *
 * ONLY INDICATED PARTS SHOULD BE CHANGED *
 * * * * * * * * * * * * * * * * * * * * */

/* @Author
 * Student Name: Mustafa Bayrak
 * Student ID : 150210339
 */

/* Necessary header files */
#include <stack.h>

#include <cstdlib>
#include <iostream>
#include <limits>

using namespace std;

/* Declaration of the non-member functions */
void print_intro();
void print_basket_info(int);
bool check_end_game();
int get_random_number();
bool get_action();
bool apply_joker();
void empty_baskets();

/* Global stack variables which can be reached anywhere in main.cpp */
Stack basket1, basket2, basket3;

int main() {
    /* Random number generator seed */
    // srand(time(NULL));
    srand(42);  // uncomment this and comment above line out while testing with Calico

    /* Print game intro to the console */
    print_intro();

    /* Variables to store total points and turn number */
    int points = 0, turn = 0;

    /* Initialize stack variables which is declared before */
    basket1.top = nullptr;
    basket2.top = nullptr;
    basket3.top = nullptr;

    /* Boolean variable for end game condition */
    bool end_game = false;

    /* Main loop of the program */
    while (!end_game) {  // while end game condition is NOT met

        system("clear");  // clear console output

        print_basket_info(turn);  // print info of all baskets

        if (!get_action()) {  // users make their move
            points -= 10;     // if users make an illegal move, reduce points
            continue;
        }

        end_game = check_end_game();  // check for end game condition

        /* If game does not end, give user 10 more points */
        if (!end_game) {
            points += 10;
        }

        turn++;  // go to the next turn
    }

    /* When game ends, print final basket info */
    print_basket_info(turn);

    /* Print total points */
    cout << endl;
    cout << "GAME OVER." << endl;
    cout << "Total points: " << points << endl;

    /* Give all allocated memory back */
    empty_baskets();
    return 0;
}

/* Print game intro to the console */
void print_intro() {
    cout << " ____________________  " << endl;
    cout << "|                    | " << endl;
    cout << "|    Hanoi Baskets   | " << endl;
    cout << "|____________________| " << endl;
    cout << " \\/\\/\\/\\/\\/\\/\\/\\/\\/\\/  " << endl;
    cout << "  \\/\\/\\/\\/\\/\\/\\/\\/\\/   " << endl;
    cout << "   \\/\\/\\/\\/\\/\\/\\/\\/    " << endl;
    cout << "    \\/\\/\\/\\/\\/\\/\\/     " << endl;
    cout << "     \\/\\/\\/\\/\\/\\/      " << endl;
    cout << "      \\/\\/\\/\\/\\/       " << endl;
    cout << "       \\/\\/\\/\\/        " << endl;
    cout << endl;
    cout << "Please put incoming numbers to one of three baskets with the goal of obtaining three baskets filled with numbers from highest (at the bottom) to the lowest (at the top)." << endl;
    cout << endl;
    cout << "Press enter to continue.." << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Wait for enter key

    /* If we use cin.get() and user presses other than enter with
    more than one character, we will end up with an endless loop.
    So, we need to force stream to ignore the bad input. */
}

/* Print info of all baskets */
void print_basket_info(int turn) {
    cout << endl;
    cout << "Turn " << turn << ": Baskets look like this:" << endl;

    cout << "Basket 1:" << endl;
    ;
    basket1.print_all();

    cout << "Basket 2:" << endl;
    ;
    basket2.print_all();

    cout << "Basket 3:" << endl;
    ;
    basket3.print_all();

    cout << endl;
}

/* Check for end game condition */
bool check_end_game() {
    bool check = !(basket1.is_descending() && basket2.is_descending() && basket3.is_descending());
    return check;
}

/* Get a random number between 0-10 */
int get_random_number() {
    int random = rand() % 10;
    cout << "Incoming number: " << random << endl;

    return random;
}

/* Users make their move */
bool get_action() {
    int number = get_random_number();  // get a random number between 0-10
    cout << endl;
    cout << "Press 0 to see jokers." << endl;
    cout << "Where to put the incoming number: ";
    int index;
    cin >> index;  // get input from the user for the next move

    /* If given input is not integer (illegal move), error will occur.
    Clean stream buffer and ignore the bad input. */
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        index = -1;
    }
    switch (index) {
        case 0:
            apply_joker();
            break;
        case 1:
            basket1.push(number);
            break;
        case 2:
            basket2.push(number);
            break;
        case 3:
            basket3.push(number);
            break;
        default:
            break;
    }
    /* TODO */
    if (index != 1 && index != 2 && index != 3) {
        return false;
    }
    return true;
}

/* User chooses to use a joker */
bool apply_joker() {
    cout << endl;
    cout << "Choose a joker: " << endl;
    cout << "1. Merge baskets: move elements from second basket to the first basket without breaking the order of the elements. (highest at the bottom, lowest at the top)" << endl;
    cout << "2. Sequentialize basket: remove elements which break consecutiveness from a basket." << endl;
    cout << endl;
    int index;
    cin >> index;

    /* If given input is not integer (illegal move), error will occur.
    Clean stream buffer and ignore the bad input. */
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        index = -1;
    }
    // Call functions with appropriate elements according to the input
    if (index == 1) {
        int first_basket;
        int second_basket;
        Stack *main;
        Stack *add;
        cout << "Choose first basket: ";
        cin >> first_basket;
        cout << "Choose second basket: ";
        cin >> second_basket;
        switch (first_basket) {
            case 1:
                main = &basket1;
                break;
            case 2:
                main = &basket2;

                break;
            case 3:
                main = &basket3;

                break;

            default:
                break;
        }
        switch (second_basket) {
            case 1:
                add = &basket1;
                break;
            case 2:
                add = &basket2;
                break;
            case 3:
                add = &basket3;
                break;
            default:
                break;
        }
        (*main).merge_basket(add);
    } else if (index == 2) {
        cout << "Which basket should be sequentilized: ";
        int choose;
        cin >> choose;
        switch (choose) {
            case 1:
                basket1.sequentilized();
                break;
            case 2:
                basket2.sequentilized();
                break;
            case 3:
                basket3.sequentilized();
                break;
            default:
                break;
        }
    }
    return true;
}

/* Empty all baskets */
void empty_baskets() {
    while (basket1.top) {
        basket1.pop();
    }
    while (basket2.top) {
        basket2.pop();
    }
    while (basket3.top) {
        basket3.pop();
    }
}