#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <string>
#include "piece.h"

//char arr[] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p','R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'};
//using namespace std;
class ChessBoard {

public:
    ChessBoard();//constructor
    void display(std::ostream& out) const;//prints board into whatever stream is given, prints additional stuff if given stream is std::cout

    bool isValidMoveFormat(const std::string& move_str) const;//checks format for inputted move returns false if invalid format is inputted
    bool playTurn();//plays one turn of the game, return false if game is checkmate'd
    bool parseMove(int* row, int* col, int* t_row, int* t_col); //takes and parses user input boolean to implement proper exit mechanism
    bool checkMate();//checks checkmate status for the board
    void turnSwitch();//switches turn to other color
    ChessPiece& getKing(Color turn);//finds and returns inputted colors king
    bool endMove(int row, int col, int t_row, int t_col, Color c) const;//checks if the move is valid for check reasons
    void suggest();//suggests a move to user
    double score();//calculates overall goodness score of board
    void save();//takes input for filename, saves into file
    ChessBoard load();//takes input for filename, loads a game from file into object and returns that

    //std::vector<std::vector<ChessPiece>>& getb(){return board;}
    //Color getTurn() {return turn;}

    private:
    std::vector<std::vector<ChessPiece>> board;//piece vector
    Color turn = Color::WHITE;// holds the value for current color

};


#endif // BOARD_H
