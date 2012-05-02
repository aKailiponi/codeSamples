/* 
 * File:   ConnectFour.cpp
 * Author: Abraham Kailiponi
 *
 * Created on April 28, 2012, 11:31 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int board[7][6];
int top[7];

//these are used to evaluate the value of a move by checking segments of board
int segment[3] = {0, 0, 0};
int value = 0;

int empty = 0;
int adjacentBlack = 0;
int adjacentRed = 0;
int friendlyBlack = 0;

/* Draws the board.
 */
void drawBoard(){
    for(int y = 5; y >= 0; y--){
            for(int x = 0; x < 7; x++){
                switch(board[x][y]){
                    case 0: 
                        cout << "- ";
                        break;
                        
                    case 1:
                        cout << "R ";
                        break;

                    case 2:
                        cout << "B ";
                        break;
                }
            }
            cout << endl;
        }
        cout << "0 1 2 3 4 5 6" << endl;
}
/* Queries the player for a move.
 */ 
int getPlayerMove(){
    string input = "";
    cout << "Your Move(0-6): ";
    getline(cin, input);
    return atoi(input.c_str());
}

/* Puts a move onto the board.
 */
void makeMove(int player, int move){
    board[move][top[move]] = player;
    top[move]++;
}
/* Resets all the counts used for evaluating the value of a move
 */
void resetEvaluationCounts(){
    empty = 0;
    adjacentBlack = 0;
    adjacentRed = 0;
    friendlyBlack = 0;
}

/* This matches a pattern so we can assign an appropriate values to the evaluation
 * 0 = blank space
 * 1 = Red Piece
 * 2 = Black Piece
 * 3 = Out of Bounds
 * 4 = Don't care whats in that spot
 */
bool pattern(int zero, int one, int two){
    if(zero == segment[0]){
        if(one == segment[1]){
            if((two == 4) || (segment[2] == two)){
                return true;
            }
        }
    }
    return false;
}

/* Reads the pattern of a segment and counts any meaningful spaces.
 */
void countSegment(){
    //patterns that have adjacent black
    if(pattern(2,2,2)){
        adjacentBlack += 3;
    }
    else if(pattern(2,2,0)){
        adjacentBlack += 2;
        empty += 1;
    }
    else if(pattern(2,2,1) || pattern(2,2,3)){
        adjacentBlack += 2;
    }
    else if(pattern(2,0,2)){
        adjacentBlack += 1;
        friendlyBlack += 1;
        empty += 1;
    }
    else if(pattern(2,0,0)){
        adjacentBlack += 1;
        empty += 2;
    }
    else if(pattern(2,0,3) || pattern(2,0,1)){
        adjacentBlack += 1;
        empty += 1;
    }
    else if(pattern(2,1,4) || pattern(2,3,3)){
        adjacentBlack += 1;
    }
    //patterns that have only friendly black
    else if(pattern(0,2,2)){
        friendlyBlack += 2;
        empty += 1;
    }
    else if(pattern(0,0,2) || pattern(0,2,0)){
        friendlyBlack += 1;
        empty += 2;
    }
    else if(pattern(0,2,1) || pattern(0,2,3)){
        friendlyBlack += 1;
        empty += 1;
    }
    //patterns that only posses viable empty spots
    else if(pattern(0,0,0)){
        empty += 3;
    }
    else if(pattern(0,0,1) || pattern(0,0,3)){
        empty += 2;
    }
    else if(pattern(0,1,4) || pattern(0,3,3)){
        empty += 1;
    }
    //patterns that have adjacent red
    else if(pattern(1,1,1)){
        adjacentRed += 3;
    }
    else if(pattern(1,1,3) || pattern(1,1,2)){
        adjacentRed += 2;
    }
    else if(pattern(1,2,4) || pattern(1,3,3)){
        adjacentRed += 1;
    }
    else{
        //the remaining patterns should adjust nothing
    }
}

/* Assigns an overall value to the segment counts
 */
void calculateValue(){
     if(adjacentBlack >= 3){
        value += 1000000;
    }
    else if(adjacentRed >= 3){
        value += 5000;
    }
    else{
        value += (adjacentBlack * 5)  + (friendlyBlack * 3) + empty;
    }
}

void calculateUpDown(int move){
    //count up
    int columnIndex = move;
    int rowIndex = move[top] + 1;
    for(int x = 0; x < 3; x++){
        if(rowIndex > 5)
            segment[x] = 3;
        else
                segment[x] = board[columnIndex][rowIndex];
        rowIndex++;
    }
    countSegment();
    
    //count down
    columnIndex = move;
    rowIndex = move[top] - 1;
    for(int x = 0; x < 3; x++){
        if(rowIndex < 0)
            segment[x] = 3;
        else
                segment[x] = board[columnIndex][rowIndex];
        rowIndex--;
    }
    countSegment();
    
    calculateValue();
    resetEvaluationCounts();
}

void calculateRightLeft(int move){
    //count right
    int columnIndex = move + 1;
    int rowIndex = top[move];
    for(int x = 0; x < 3; x++){
        if(columnIndex > 6)
            segment[x] = 3;
        else
            segment[x] = board[columnIndex][rowIndex];
        columnIndex++;
    }
    countSegment();
    
    //count right
    columnIndex = move - 1;
    rowIndex = top[move];
    for(int x = 0; x < 3; x++){
        if(columnIndex <  0)
            segment[x] = 3;
        else
            segment[x] = board[columnIndex][rowIndex];
        columnIndex--;
    }
    countSegment();
    
    calculateValue();
    resetEvaluationCounts();
}

void calculateFowardDiagonal(int move){
    //count left and up
    int columnIndex = move + 1;
    int rowIndex = top[move] + 1;
    for(int x = 0; x < 3; x++){
        if((columnIndex > 6) || (rowIndex > 5))
            segment[x] = 3;
        else
            segment[x] = board[columnIndex][rowIndex];
        columnIndex++;
        rowIndex++;
    }
    countSegment();
    //count right and down
    columnIndex = move - 1;
    rowIndex = top[move] - 1;
      for(int x = 0; x < 3; x++){
        if((columnIndex < 0) || (rowIndex < 0))
            segment[x] = 3;
        else
            segment[x] = board[columnIndex][rowIndex];
        columnIndex--;
        rowIndex--;
    }
    countSegment();
    
    calculateValue();
    resetEvaluationCounts();
}

int calculateBackwardDiagonal(int move){
     //count left and down
    int columnIndex = move + 1;
    int rowIndex = top[move] - 1;
    for(int x = 0; x < 3; x++){
        if((columnIndex > 6) || (rowIndex < 0))
            segment[x] = 3;
        else
            segment[x] = board[columnIndex][rowIndex];
        columnIndex++;
        rowIndex--;
    }
    countSegment();
    
    //count right and up
    columnIndex = move - 1;
    rowIndex = top[move] + 1;
      for(int x = 0; x < 3; x++){
        if((columnIndex < 0) || (rowIndex > 5))
            segment[x] = 3;
        else
            segment[x] = board[columnIndex][rowIndex];
        columnIndex--;
        rowIndex++;
    }
    countSegment();
    
    calculateValue();
    resetEvaluationCounts();
}

void calculateMoveValue(int move){

    calculateUpDown(move);
    calculateRightLeft(move);
    calculateFowardDiagonal(move);
    calculateBackwardDiagonal(move);
}

int computerMove(){
    int bestMove = 0;
    int bestMoveValue = 0;

    for(int x = 0; x < 7; x++){
        if(top[x] > 5){
            value = 0;
            cout << "MOVE:" << x << " VALUE:" << value << endl;
            continue;
        }
        calculateMoveValue(x);
        cout << "MOVE:" << x << " VALUE:" << value << endl;
        if(value > bestMoveValue){
            bestMove = x;
            bestMoveValue = value;
        }
        value = 0;
    }
    return bestMove;
}

/*
 * 
 */
int main(int argc, char** argv) {

    drawBoard();
    while(1){
        //players turn
        int playerMove = getPlayerMove();
        makeMove(1, playerMove);
        //computers turn
        int compMove = computerMove();
        makeMove(2, compMove);
        //drawBoard
        drawBoard();
    }
    
    return 0;
}

