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

int main() {
	return 0;
}

bool checkWinner(char t) { // t represents the player's token, either 'X' or 'O'
    return (horizontal(t) || vertical(t) ) || (forwardDiagonal(t) || backwardDiagonal(t));
    //any of these being true means the player got 4 in a row and won (returns true)
}

bool horizontal(char t) {

	return false;
}
bool vertical(char t) {

	return false;
}
bool forwardDiagonal(char t) {

	return false;
}
bool backwardDiagonal(char t) {

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
	
}

void addToken(player p, int col) {
	
}

bool isFull(int col) { //determines whether the player can place a token in the desired column
    for (int i = 0; i < 6; i++) { //if any spot in the col is open, it is not full
        if (grid[i][col] != '.') return false;
    }
    return true; //none of the spots are open
}

void printGrid() { //iterates through the grid and prints out the board
    for (int i = 0; i < 6; i++) {
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
