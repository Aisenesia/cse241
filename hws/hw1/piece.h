#ifndef PIECE_H
#define PIECE_H

#include <iostream>

enum class Color { WHITE, BLACK, NOCOLOR };

class ChessPiece {
public:
    enum class Type { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, EMPTY };

    ChessPiece(Color c = Color::NOCOLOR, Type t = Type::EMPTY, int r = 0, int co = 0) : color(c), type(t), row(r), col(co) {}
    ChessPiece(const ChessPiece& other);//Copy constructor

    void setType(Type t) {type = t;}
    Type getType() const {return type;}
    void setColor(Color c) {color = c;}
    Color getColor() const {return color;}

    void setRow(int r) {row = r;}
    void setCol(int c) {col = c;}

    void printPiece();



    // returns symbol of piece as a character
    char getSymbol() const; 
    //empties the cell into NOCOLOR and EMPTY
    void setEmpty();
    
    bool generic_moveValidity(const std::vector<std::vector<ChessPiece>>& board, int t_row, int t_col, Color turn) const; //this is written for suggest and checkmate, doMove already checks for these things and prints according error messages

    //returns validity from row, col of the piece to target_row target_col of the board according to piece movesets and attack patterns
    bool pawn_moveValidity(const std::vector<std::vector<ChessPiece>>& board, int t_row, int t_col) const;
    bool rook_moveValidity(const std::vector<std::vector<ChessPiece>>& board, int t_row, int t_col) const;
    bool knight_moveValidity(const std::vector<std::vector<ChessPiece>>& board, int t_row, int t_col) const;
    bool bishop_moveValidity(const std::vector<std::vector<ChessPiece>>& board, int t_row, int t_col) const;
    bool queen_moveValidity(const std::vector<std::vector<ChessPiece>>& board, int t_row, int t_col) const;
    bool king_moveValidity(const std::vector<std::vector<ChessPiece>>& board, int t_row, int t_col) const;

    //finds piece, parses which validity function to call and calls it, returns true if move is valid
    bool checkPieceRule(const std::vector<std::vector<ChessPiece>>& board, int t_row, int t_col) const;
    //for piece checks whether if any other piece from opposing side can attack it or not
    bool underAttack(const std::vector<std::vector<ChessPiece>>& board) const;
    //moves unconditionally and cleans its remnants, validity check for move has been done before calling this
    void move(std::vector<std::vector<ChessPiece>>& board, int t_row, int t_col);
    //calculates points for this piece
    double getPoints(const std::vector<std::vector<ChessPiece>>& board);

private:
    Color color;
    Type type;
    int row;
    int col;
};

Color otherColor(Color);
#endif
