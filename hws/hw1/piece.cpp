#include <iostream>
#include <vector>
#include "piece.h"

//ChessPiece::


Color otherColor(Color c){
    if(c==Color::BLACK) return Color::WHITE;
    else return Color::BLACK;

}

ChessPiece::ChessPiece(const ChessPiece& other) {
        color = other.color;
        type = other.type;
        row = other.row;
        col = other.col;
}


char ChessPiece:: getSymbol() const {
    Color c = color;
    char res;
    switch (type){
        case ChessPiece::Type::KING: res = (c == Color::WHITE) ?  'K' : 'k';
            break;
        case ChessPiece::Type::QUEEN: res = (c == Color::WHITE) ? 'Q' : 'q';
            break;
        case ChessPiece::Type::BISHOP: res = (c == Color::WHITE) ? 'B' : 'b';
            break;
        case ChessPiece::Type::KNIGHT: res = (c == Color::WHITE) ? 'N' : 'n';
            break;
        case ChessPiece::Type::ROOK: res = (c == Color::WHITE) ? 'R' : 'r';
            break;
        case ChessPiece::Type::PAWN: res = (c == Color::WHITE) ? 'P' : 'p';
            break;
        case ChessPiece::Type::EMPTY: res = (c == Color::NOCOLOR) ? '.' : '0';
            break;
        }
    return res;
}

void ChessPiece::setEmpty(){
    color = Color::NOCOLOR;
    type = ChessPiece::Type::EMPTY;
}

bool ChessPiece::generic_moveValidity(const std::vector<std::vector<ChessPiece>>& board, int t_row, int t_col, Color turn) const {
    if(board[t_row][t_col].getColor() == board[row][col].getColor()) return false;
    if(type==ChessPiece::Type::EMPTY || color!=turn || board[t_row][t_col].getColor() == color) return false;
    else return true;
}

bool ChessPiece::pawn_moveValidity(const std::vector<std::vector<ChessPiece>>& board, int t_row, int t_col) const {
    int rowDiff = abs(row - t_row);
    int colDiff = abs(col - t_col);
        
    if (color == Color::WHITE) {
        if(col == t_col){
            if(t_row - row == 1 && board[t_row][t_col].getType() == ChessPiece::Type::EMPTY) return true;//1 STEP TO EMPTY
            else if(row==1 && t_row == 3 && board[t_row][col].getType() == ChessPiece::Type::EMPTY) return true;//2 STEP
        } else if(colDiff == 1 && t_row-row == 1 && board[t_row][t_col].getType() != ChessPiece::Type::EMPTY) return true;//1 STEP TO ENEMY
    } else {
        if(col == t_col){
            if(t_row - row == -1 && board[t_row][t_col].getType() == ChessPiece::Type::EMPTY) return true;
            else if( row==6 && t_row == 4 && board[t_row][col].getType() == ChessPiece::Type::EMPTY) return true;
        } else if(colDiff == 1 && row - t_row == 1 && board[t_row][t_col].getType() != ChessPiece::Type::EMPTY) return true;
    }
    //std::cout << "Invalid pawn move!" << std::endl;
    return false;
}
bool ChessPiece::rook_moveValidity(const std::vector<std::vector<ChessPiece>>& board, int t_row, int t_col) const {
// Check if the move is horizontal or vertical
    if (row == t_row) {// Horizontal move
        int step = (t_col > col) ? 1 : -1;//WHITE BLACK Handling
        for (int i = col + step; i != t_col; i += step) {
            if (board[row][i].getType() != Type::EMPTY) {
                //std::cout<<"An obstacle blocks that path!"<<std::endl;
                return false; //Obstacle in the path
            }
        }
    } else if (col == t_col) {// Vertical move
        
        int step = (t_row > row) ? 1 : -1;
        for (int i = row + step; i != t_row; i += step) {
            if (board[i][col].getType() != Type::EMPTY) {
                //std::cout<<"An obstacle blocks that path!"<<std::endl;
                return false;
            }
        }
    } else {
        //std::cout<<"Rook can only go straight!"<<std::endl;
        return false;
}
return true;//valid move
}

bool ChessPiece::knight_moveValidity(const std::vector<std::vector<ChessPiece>>& board, int t_row, int t_col) const {

    // Check for a valid L-shaped move for a knight
    int rowDiff = abs(row - t_row);
    int colDiff = abs(col - t_col);
    bool valid = (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
    //if(!valid) std::cout<<"Knight can only move in L shape!"<<std::endl;
    return valid;
}

bool ChessPiece::bishop_moveValidity(const std::vector<std::vector<ChessPiece>>& board, int t_row, int t_col) const{
    // Check if the move is diagonal or not
    if (abs(row - t_row) != abs(col - t_col)) {
        //std::cout<<"Bishop can only move diagonally!"<<std::endl;
        return false; 
    }

    int rowStep = (t_row > row) ? 1 : -1;
    int colStep = (t_col > col) ? 1 : -1;

    // Check for obstacles in the path
    int i = row + rowStep;
    int j = col + colStep;
    while (i != t_row && j != t_col) {
        if (board[i][j].getType() != Type::EMPTY){
            //std::cout<<"An obstacle blocks that path!"<<std::endl;
            return false;
        }
        i += rowStep;
        j += colStep;
    }
    return true;
}

bool ChessPiece::queen_moveValidity(const std::vector<std::vector<ChessPiece>>& board, int t_row, int t_col) const {
    return bishop_moveValidity(board, t_row, t_col) || rook_moveValidity(board, t_row, t_col);
}

bool ChessPiece::king_moveValidity(const std::vector<std::vector<ChessPiece>>& board, int t_row, int t_col) const {
    if(abs(t_row-row)<=1 && abs(t_col-col)<=1 && board[t_row][t_col].getColor() != color){
        std::vector<std::vector<ChessPiece>> dummyBoard = board;
        dummyBoard[row][col].move(dummyBoard, t_row, t_col);
        return !dummyBoard[t_row][t_col].underAttack(dummyBoard);
    }
    return false;
}

bool ChessPiece::checkPieceRule(const std::vector<std::vector<ChessPiece>>& board, int t_row, int t_col) const{
    bool isValidMove;
    switch (type){
    case ChessPiece::Type::PAWN:
        isValidMove = board[row][col].pawn_moveValidity(board, t_row, t_col);
        break;            
    case ChessPiece::Type::ROOK:
        isValidMove = board[row][col].rook_moveValidity(board, t_row, t_col);
        break;
    case ChessPiece::Type::KNIGHT:
        isValidMove = board[row][col].knight_moveValidity(board, t_row, t_col);
        break;
    case ChessPiece::Type::BISHOP:
        isValidMove = board[row][col].bishop_moveValidity(board, t_row, t_col);
        break;
    case ChessPiece::Type::KING:
        isValidMove = board[row][col].king_moveValidity(board, t_row, t_col);
        break;
    case ChessPiece::Type::QUEEN:
        isValidMove = board[row][col].queen_moveValidity(board, t_row, t_col);
        break;
        case ChessPiece::Type::EMPTY:
        isValidMove = false;
        break;    
    }
    return isValidMove;       
}

bool ChessPiece::underAttack(const std::vector<std::vector<ChessPiece>>& board) const {
    bool isUnderAttack = false;
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            if(!(row == i && col == j) && board[i][j].getColor() == otherColor(color) && board[i][j].getType() != Type::EMPTY){
                //std::cout<<(board[i][j].getColor()==Color::WHITE);
                isUnderAttack = board[i][j].checkPieceRule(board, row, col);
                if(isUnderAttack) {
                    //std::cout<<"move: "<<static_cast<char>(j + 'a')<<i+1<<static_cast<char>(col + 'a')<<row+1<<"-s: "<<std::endl;
                    return true;
                }   
            }
        }
    }
    
    return false;
}

void ChessPiece::move(std::vector<std::vector<ChessPiece>>& board, int t_row, int t_col){
    board[t_row][t_col] = board[row][col];
    
    board[row][col].setEmpty();
    board[t_row][t_col].row = t_row;
    board[t_row][t_col].col = t_col;

}

double ChessPiece::getPoints(const std::vector<std::vector<ChessPiece>>& board){
    double res; //= 0.0;
    switch (type){
    case ChessPiece::Type::PAWN:
    res = 1.0;
        break;            
    case ChessPiece::Type::ROOK:
    res = 5.0;
        break;
    case ChessPiece::Type::KNIGHT:
    res = 3.0;
        break;
    case ChessPiece::Type::BISHOP:
    res = 3.0;
        break;
    case ChessPiece::Type::KING:
    res = 1000.0;
        break;
    case ChessPiece::Type::QUEEN:
    res = 9.0;
        break;
    }
    if(underAttack(board)) res /= 2;
    return res;
}

void ChessPiece::printPiece(){
    //std::string typeStr;
    //std::string colorStr;

}