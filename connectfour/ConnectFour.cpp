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

int getPlayerMove(){
    string input = "";
    cout << "Your Move(0-6): ";
    getline(cin, input);
    return atoi(input.c_str());
}

void makeMove(int player, int move){
    board[move][top[move]] = player;
    top[move]++;
}


int calculateUpDown(int move){
    int value = 0;
    
    //give value below possible move (every black piece below is worth 5 points)
    int rowIndex = top[move] - 1;
    int spacesSearched = 3;
    while(spacesSearched > 0){
        if(rowIndex < 0)
            break;
        if(board[move][rowIndex] == 2){
            value += 5;
            if(value >= 15){
                return 1000000;
            }
        }
        else
            break;
        spacesSearched--;
        rowIndex--;
    }
    
    //give value above possible move (every blank space above is worth 1 point)
    if(top[move] < 2)
        value += 3;
    else
        value += top[move];
    
    return value;
}

int calculateLeftRight(int move){
    //value left
    int value = 0;
    int adjacentBlack = 0;
    int columnIndex = move + 1;
    int spacesSearched = 3;
    while(spacesSearched > 0){
        if(columnIndex > 6)
            break;
        else if(board[columnIndex][top[move]] == 0)
            value += 1;
        else if(board[columnIndex][top[move]] == 2){
            value += 5;
            adjacentBlack++;
            if(adjacentBlack >= 3){
                return 1000000;
            }
        }
        else
            break;
        columnIndex++;
        spacesSearched--;
    }
    //value right
    columnIndex = move - 1;
    spacesSearched = 3;
    while(spacesSearched > 0){
        if(columnIndex < 0)
            break;
        else if(board[columnIndex][top[move]] == 0)
            value += 1;
        else if(board[columnIndex][top[move]] == 2){
            value += 5;
            adjacentBlack++;
            if(adjacentBlack >= 3){
                return 1000000;
            }
        }
        else
            break;
        columnIndex++;
        spacesSearched--;
    }
    return value;
    
}

int calculateFowardDiagonal(int move){
    //diagonal up and right
    int value = 0;
    int adjacentBlack = 0;
    int columnIndex = move + 1;
    int rowIndex = top[move] + 1;
    int spacesSearched = 3;
    while(spacesSearched > 0){
        if((columnIndex > 6) || (rowIndex >  5))
            break;
        else if(board[columnIndex][top[move]] == 0)
            value += 1;
        else if(board[columnIndex][top[move]] == 2){
            value += 5;
            adjacentBlack++;
            if(adjacentBlack >= 3){
                return 1000000;
            }
        }
        else
            break;
        columnIndex++;
        rowIndex++;
        spacesSearched--;
    }
    
    //diagonal down and left
    columnIndex = move - 1;
    rowIndex = top[move] - 1;
    spacesSearched = 3;
    while(spacesSearched > 0){
        if((columnIndex < 0) || (rowIndex <  0))
            break;
        else if(board[columnIndex][top[move]] == 0)
            value += 1;
        else if(board[columnIndex][top[move]] == 2){
            value += 5;
            adjacentBlack++;
            if(adjacentBlack >= 3){
                return 1000000;
            }
        }
        else
            break;
        columnIndex--;
        rowIndex--;
        spacesSearched--;
    }
    return value;
}

int calculateBackwardDiagonal(int move){
    //diagonal down and right
    int value = 0;
    int adjacentBlack = 0;
    int columnIndex = move + 1;
    int rowIndex = top[move] - 1;
    int spacesSearched = 3;
    while(spacesSearched > 0){
        if((columnIndex > 6) || (rowIndex <  0))
            break;
        else if(board[columnIndex][top[move]] == 0)
            value += 1;
        else if(board[columnIndex][top[move]] == 2){
            value += 5;
            adjacentBlack++;
            if(adjacentBlack >= 3){
                return 1000000;
            }
        }
        else
            break;
        columnIndex++;
        rowIndex--;
        spacesSearched--;
    }
    
    //diagonal down and left
    columnIndex = move - 1;
    rowIndex = top[move] + 1;
    spacesSearched = 3;
    while(spacesSearched > 0){
        if((columnIndex < 0) || (rowIndex >  5))
            break;
        else if(board[columnIndex][top[move]] == 0)
            value += 1;
        else if(board[columnIndex][top[move]] == 2){
            value += 5;
            adjacentBlack++;
            if(adjacentBlack >= 3){
                return 1000000;
            }
        }
        else
            break;
        columnIndex--;
        rowIndex++;
        spacesSearched--;
    }
    return value;
}

int calculateMoveValue(int move){
    int moveValue = 0;
    moveValue += calculateUpDown(move);
    moveValue += calculateLeftRight(move);
    moveValue += calculateFowardDiagonal(move);
    moveValue += calculateBackwardDiagonal(move);
    return moveValue;
    
}

int computerMove(){
    int moveValue = 0;
    int bestMove = 0;
    int bestMoveValue = 0;

    for(int x = 0; x < 7; x++){
        moveValue = calculateMoveValue(x);
        if(moveValue > bestMoveValue){
            bestMove = x;
            bestMoveValue = moveValue;
        }
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
        int compMove = computerMove();
        makeMove(2, compMove);
        drawBoard();
        //computers turn
    }
    
    return 0;
}

