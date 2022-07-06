// ConnectFour.cpp 
// This program runs a text-based game of Connect 4 between 2 players, using a 6x7 board
//
// Author: Sanchit Singhal

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

struct player {
    string name;
    char token;
};

bool valid = true; //tracks whether moves are valid
vector<vector<char> > grid = {}; //game board
player p1, p2; //player1, player2
pair<int, int> lastCoordinate; //tracks the position on grid of the last token placed

void setup(); // initializes variables and gets the game ready to run
void printGrid(); // outputs the contents of the gameboard, the . represents an open spot
void addToken(player p, int col); // adds player's token to the desired column, try again if not valid
bool isFull(int col); // returns whether or not the column can have more tokens added to it
void playTurn(player p); // executes one turn with player P going
bool fullBoard(); // all spots are filled without a win, resulting in a draw

bool checkWinner(char t); // checks to see if there is a row of 4 anywhere
bool horizontal(char t); // checks the horizontal for 4 in a row
bool vertical(char t); // checks the vertical for 4 in a row
bool forwardDiagonal(char t); // checks the forward diagonal /
bool backwardDiagonal(char t); // checks the backward diagonal \

int main()
{
    start:
    setup();
    player p; //local variable, alternates between p1 and p2
    srand((unsigned)time(NULL));
    //randomly decides whether p1 or p2 goes first
    int turn = 0; if (rand() % 2 == 1) turn++;

    while (true) {
        if (turn % 2 == 0) p = p1;
        else p = p2;
        playTurn(p); //player for this turn makes a move
        if (turn >= 4 && checkWinner(p.token)) { //checks if this was winning move, if at least 3-4 moves have been made
            printGrid();
            cout << p.name << " got 4 in a row and is the winner!" << endl;
            goto end; //jump to finish, used to exit loop as well
        }
        if (turn >= 41 && fullBoard()) { //only checks after almost every move has been made
            printGrid(); //full board with no winner from above means it's a draw
            cout << "The game is a draw!" << endl;
            goto end; //jump to finish, used to exit loop as well
        }
        turn++;
    }
    end:
    int again;
    cout << "Would you like to play again? 0 for no, 1 for yes :: "; cin >> again;
    if (again == 1) goto start; //resets everything if playing again
    cout << "Thanks for playing!" << endl;
    return 0;
}

bool checkWinner(char t) { // t represents the player's token, either 'X' or 'O'
    return (horizontal(t) || vertical(t) ) || (forwardDiagonal(t) || backwardDiagonal(t));
    //any of these being true means the player got 4 in a row and won (returns true)
}

bool backwardDiagonal(char t) { // for the \ diagonal
    int i = lastCoordinate.first; int j = lastCoordinate.second;
    while ((i != 0) && (j != 0)) {
        i--; j--; //bring coordinate to top and left most in the \ diagonal
    }
    int count = 0;
    while ((i != 6) && (j != 7)) { //boundaries
        if (grid[i][j] == t) {
            count++;
            if (count >= 4) return true; //stop as soon as 4 in a row is counted
        }
        else count = 0; //go back to 0 if there's a break
        i++; j++; //move one down the diagonal
    }
    return false;
}

bool forwardDiagonal(char t) { // for the / diagonal
    int i = lastCoordinate.first; int j = lastCoordinate.second;
    while ((i != 5) && (j != 0)) {
        i++; j--; //bring coordinate to bottom and left most in the / diagonal
    }
    int count = 0;
    while ((i != -1) && (j != 7)) { //boundaries
        if (grid[i][j] == t) {
            count++;
            if (count >= 4) return true; //stop as soon as 4 in a row is counted
        }
        else count = 0; //go back to 0 if there's a break
        i--; j++; //move one up the diagonal
    }
    return false;
}

bool vertical(char t) {
    int count = 0;
    for (int i = 0; i < 6; i++) { //check every element from 0-5 in the same column
        if (grid[i][lastCoordinate.second] == t) {
            count++;
            if (count >= 4) return true; //stop as soon as 4 in a row is counted
        }
        else count = 0; //go back to 0 if there's a break
    }
    return false;
}

bool horizontal(char t) {
    int count = 0;
    for (int i = 0; i < 7; i++) { //check every element from 0-6 in the same row
        if (grid[lastCoordinate.first][i] == t) {
            count++;
            if (count >= 4) return true; //stop as soon as 4 in a row is counted
        }
        else count = 0; //if there's a break, go back to 0
    }
    return false;
}

bool fullBoard() { // checks whether the board is full or not
    /*
    This method only checks the first row since it's impossible to have
    a filled in spot above a blank spot, and all pieces will fall naturally
    If it sees a blank spot, it returns false
    */
    for (int j = 0; j < 7; j++) { if (grid[0][j] == '.') { return false; } }
    return true;
}

void playTurn(player p) {
    redo:
    valid = true; //keeps track of whether the picked column is a valid choice
    cout << "\n| 1 | 2 | 3 | 4 | 5 | 6 | 7 |" << endl;
    printGrid(); //outputs column numbers for player to easily pick (1-7)
    cout << endl << endl; //subtracting 1 from the player's choice to match with indices 0-6
    int pickedCol; string s;
    cout << p.name << "'s turn. Pick a column 1-7 to drop your piece in. "; 
    try_again:
    getline(cin, s);
    try {
        pickedCol = stoi(s.substr(0, 1));
    }
    catch (invalid_argument) {
        cout << "Not valid. Pick a column 1-7 to drop your piece in. ";
        goto try_again;
    }
    addToken(p, pickedCol);
    if (!valid) goto redo; //runs whole method again, seemed better than utilizing a while
}

void addToken(player p, int col) { //process of adding a player's token
    if (col < 1 || col > 7) {
        cout << "Not a valid column" << endl;
        valid = false; return; //only 7 columns
    }
    for (int i = 5; i >= 0; i--) { //start at bottom
        if (grid[i][col-1] == '.') { //first blank spot is where token is placed
            grid[i][col-1] = p.token; //coordinate is stored (to check around for winning moves)
            lastCoordinate.first = i; lastCoordinate.second = col - 1;
            return;
        }
    } //only gets this far if the chosen column is full
    cout << "The selected column is already full" << endl;
    valid = false; return;
}

bool isFull(int col) { //determines whether the player can place a token in the desired column
    for (int i = 0; i < 6; i++) { //if any spot in the col is open, it is not full
        if (grid[i][col] != '.') return false;
    }
    return true; //none of the spots are open
}

void printGrid() { //iterates through the grid and prints out the board
    cout << "-----------------------------" << endl; //topmost border
    for (int i = 0; i < 6; i++) {
        cout << "| "; //leftmost border
        for (int j = 0; j < 7; j++) {
            cout << grid[i][j] << " | "; //horizontal spacer
        }
        cout << endl << "-----------------------------" << endl; //vertical spacer
    }
}

void setup() { //initializes all variables
    cout << "Welcome to Connect4! The first player to get 4 in a row on the grid will be the winner."; //welcome message
    cout << "If all slots are filled with no winner, the game will be declared a tie! The . represents an open slot on the grid" << endl;
    cout << "Player 1, please enter your name : "; cin >> p1.name; //store player names
    cout << "Player 2, please enter your name: "; cin >> p2.name;
    p1.token = 'X'; p2.token = 'O'; //set token symbols
    for (int i = 0; i < 6; i++) {
        vector<char> vec = {}; 
        for (int j = 0; j < 7; j++) {
            vec.push_back('.'); //create blank grid of size 6x7 filled with .
        }
        grid.push_back(vec);
    }
}
