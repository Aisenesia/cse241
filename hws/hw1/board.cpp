#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "piece.h"
#include "board.h"




ChessBoard::ChessBoard(){
    //resizes board so it has 8 vectors of pieces
    board.resize(8);

    // Black pieces
    board[7].push_back({Color::BLACK, ChessPiece::Type::ROOK, 7, 0});
    board[7].push_back({Color::BLACK, ChessPiece::Type::KNIGHT, 7, 1});
    board[7].push_back({Color::BLACK, ChessPiece::Type::BISHOP, 7, 2});
    board[7].push_back({Color::BLACK, ChessPiece::Type::QUEEN, 7, 3});
    board[7].push_back({Color::BLACK, ChessPiece::Type::KING, 7, 4});
    board[7].push_back({Color::BLACK, ChessPiece::Type::BISHOP, 7, 5});
    board[7].push_back({Color::BLACK, ChessPiece::Type::KNIGHT, 7, 6});
    board[7].push_back({Color::BLACK, ChessPiece::Type::ROOK, 7, 7});

    for (int i = 0; i < 8; ++i) {
        board[6].push_back({Color::BLACK, ChessPiece::Type::PAWN, 6, i});
    }
    
    for (int i = 2; i < 6; ++i){
        board[i].resize(8);//resizes current line to 8 to be able to modify it
        for(int j = 0; j < 8; ++j){
            board[i][j].setEmpty();//assigns with correct empty values
        }
    }

    board[0].push_back({Color::WHITE, ChessPiece::Type::ROOK, 0, 0});
    board[0].push_back({Color::WHITE, ChessPiece::Type::KNIGHT, 0, 1});
    board[0].push_back({Color::WHITE, ChessPiece::Type::BISHOP, 0, 2});
    board[0].push_back({Color::WHITE, ChessPiece::Type::QUEEN, 0, 3});
    board[0].push_back({Color::WHITE, ChessPiece::Type::KING, 0, 4});
    board[0].push_back({Color::WHITE, ChessPiece::Type::BISHOP, 0, 5});
    board[0].push_back({Color::WHITE, ChessPiece::Type::KNIGHT, 0, 6});
    board[0].push_back({Color::WHITE, ChessPiece::Type::ROOK, 0, 7});

    for (int i = 0; i < 8; ++i) {
        board[1].push_back({Color::WHITE, ChessPiece::Type::PAWN, 1, i});
    }
    
}
void ChessBoard::display(std::ostream& out) const {
    bool fflag = false;
    if(&out == &std::cout) fflag = true;
    if(fflag) out << ((turn == Color::WHITE) ? "[whites turn]" : "[blacks turn]") << std::endl;
    for (int i = 7; i >= 0; --i) {
        if(fflag) out << i + 1 << "|";
        for (int j = 0; j < 8; ++j) {
            char symbol = board[i][j].getSymbol();
            out << ' ' << symbol;
        }
        out << "\n";
    }
    if(&out == &std::cout){
        std::cout << "  -----------------\n";
        std::cout << "   a b c d e f g h\n";
    }
    
}
bool ChessBoard::isValidMoveFormat(const std::string& move_str) const {
    return (move_str.size() == 4 && isalpha(move_str[0]) && (move_str[1]>'0' && move_str[1]<'9') && isalpha(move_str[2]) && (move_str[3]>'0' && move_str[3]<'9') && !(move_str[1] == move_str[3] && move_str[0] == move_str[2]));
}//in g2h3 checks if g and h is letters, if 2 and 3 is between 1 and 9 and if g2 == h3

bool ChessBoard::parseMove(int* row, int* col, int* t_row, int* t_col){
    std::string move_str;
        //std::cin.ignore();

    bool valid = false;
    int flag = true;
    
    do{
        if(flag) std::cout << "Enter your move: ";
        std::getline(std::cin, move_str);//GETLINE IS USED HERE
        if (move_str == "suggest") {
            suggest(); flag = true;
        }else if(move_str == "save"){
            save(); flag = true;
        }
        else if(move_str == "exit") return false;
        else{
            valid = isValidMoveFormat(move_str);
            if (!valid){
                std::cout<<"Informatted input! Enter proper move: "; 
                flag = false;
            }
        }
    }while((!valid));
    //isValidMoveFormat(move_str) && std::cout<<"Informatted input! Enter proper move: "
    *row = move_str[1]-'1'; *col = move_str[0]-'a';
    *t_row = move_str[3]-'1'; *t_col = move_str[2]-'a';
    return true;
}
bool ChessBoard::playTurn(){
    bool isValidMove = false;
    int row, col, t_row, t_col;
    Color color;
    ChessPiece::Type type;
    if(getKing(turn).underAttack(board) == true) std::cout<<"[check] ";
    display(std::cout);
    do{
        
        isValidMove = true;
        if(!parseMove(&row, &col, &t_row, &t_col)) return false; //parses user input into row col
        
        color = board[row][col].getColor();
        type = board[row][col].getType();
        
        if(type==ChessPiece::Type::EMPTY){
            std::cout << "There isn't any piece there!"<<std::endl;
            isValidMove = false;
        }
        if(color!=turn){
            std::cout << "You can't move, not your turn!"<<std::endl;
            isValidMove = false;
        }
        if(isValidMove && board[t_row][t_col].getColor() == turn){
            std::cout << "You can't move upon your own piece!"<<std::endl;
            isValidMove = false;
        }
        
        //std::cout<<"test";
        if(isValidMove && !board[row][col].checkPieceRule(board, t_row, t_col)){
            //we dont need to check for rules if isValidMove is false at this point, if serves that purpose.
            std::cout<<"Invalid move for piece!"<<std::endl;
            isValidMove = false;
            
        }
        if(isValidMove && !endMove(row, col, t_row, t_col, turn)){
            std::cout<<"Its check you have to protect king"<<std::endl;
            isValidMove = false;
        }
        

    }while(!isValidMove);

    board[row][col].move(board, t_row, t_col);
    
    turnSwitch();
    //checkmate checks
    if(checkMate()){
        std::cout<<(otherColor(turn) == Color::WHITE ?  "White" : "Black")<<" won."<<std::endl;
        return false;//to end loop
    }
    return true;
}


void ChessBoard::turnSwitch() {
    turn = (turn == Color::WHITE) ? Color::BLACK :  Color::WHITE;
}



ChessPiece& ChessBoard::getKing(Color t){
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            if(board[i][j].getType()==ChessPiece::Type::KING && board[i][j].getColor() == t) 
                return board[i][j];
        }
    }
    return board[0][0];
}

//checks if our king is left unprotected after move or not
bool ChessBoard::endMove(int row, int col, int t_row, int t_col, Color c) const {
    ChessBoard dummyBoard(*this);
    dummyBoard.board[row][col].move(dummyBoard.board, t_row, t_col);
    if(dummyBoard.getKing(c).underAttack(dummyBoard.board)) return false;
    return true;
}

bool ChessBoard::checkMate(){
    //check every valid move and check if there is any move that doesnt result in king being underAttack
    for(int row = 0; row<8; row++){
        for(int col = 0; col<8; col++){
            if (board[row][col].getColor() == turn){
                for(int t_row = 0; t_row<8; t_row++){
                    for(int t_col = 0; t_col<8; t_col++){
                        if(!(row == t_row && col == t_col) && board[row][col].generic_moveValidity(board, t_row, t_col, turn) ){
                            if(board[row][col].checkPieceRule(board, t_row, t_col)){
                                if(endMove(row, col, t_row, t_col, otherColor(turn))){

                                    ChessBoard dummyBoard(*this);//Create a fake board out of this
                                    dummyBoard.board[row][col].move(dummyBoard.board, t_row, t_col);//do the move on the fake board
                                    //if even a single instance of dummyBoards in which king is not underAttack, return false
                                    if(dummyBoard.getKing(dummyBoard.turn).underAttack(dummyBoard.board)==false){
                                        //std::cout<<"s-move: "<<static_cast<char>(col + 'a')<<row+1<<static_cast<char>(t_col + 'a')<<t_row+1<<std::endl;
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}

//works in one-depth was going to increase depth but i am out of time for that
void ChessBoard::suggest(){
    //check every valid move and calculate their points, suggest the move with highest points
    double highestScore = -5000.0;
    int highestRow, highestCol, highestTargetRow, highestTargetCol;
    highestRow = highestCol = highestTargetRow = highestTargetCol = 0;
    double currentScore;
    for(int row = 0; row<8; row++){
        for(int col = 0; col<8; col++){
            if (board[row][col].getColor() == turn){
                for(int t_row = 0; t_row<8; t_row++){
                    for(int t_col = 0; t_col<8; t_col++){
                        if(!(row == t_row && col == t_col) && board[row][col].generic_moveValidity(board, t_row, t_col, turn) && board[row][col].checkPieceRule(board, t_row, t_col) && endMove(row, col, t_row, t_col, otherColor(turn))){
                            
                            //similar logic with checkMate
                            ChessBoard dummyBoard(*this);
                            dummyBoard.board[row][col].move(dummyBoard.board, t_row, t_col);
                            currentScore = dummyBoard.score();
                            //a better scoring board has been found
                            if(currentScore > highestScore) {
                                highestScore = currentScore;
                                highestRow = row;
                                highestCol = col;
                                highestTargetRow = t_row;
                                highestTargetCol = t_col;
                            }
                        }
                    }
                }
            }
        }
    }
    std::cout<<"suggested move: "<<static_cast<char>(highestCol + 'a')<<highestRow+1<<static_cast<char>(highestTargetCol + 'a')<<highestTargetRow+1<<std::endl;

}

//calculates scores
double ChessBoard::score(){
    double res = 0.0;
    for(int row = 0; row<8; row++){
        for(int col = 0; col<8; col++){
            if(board[row][col].getColor()== turn){
                res += board[row][col].getPoints(board);
            } else if(board[row][col].getColor()==otherColor(turn)) res -= board[row][col].getPoints(board);
        }
    }
    return res;
}   


void ChessBoard::save(){
    std::string filename;
    std::cout<<"Enter file-name to save: ";
    std::getline(std::cin, filename);
    std::ofstream outf;
    outf.open(filename);
    if(!outf) {
        std::cerr<<"Error opening file!"<<std::endl;
        return;
    }
    display(outf);
    outf << ((turn == Color::BLACK) ? "black" : "white");
    outf.close();
}


ChessBoard ChessBoard::load() {
    std::string filename;
    std::cout << "Enter file-name to load from: ";
    //std::cin.ignore();
    std::getline(std::cin, filename); 
    
    std::ifstream inf(filename);
    if (!inf) {
        std::cerr << "Error opening file!" << std::endl;
        exit(-1);
    }

    ChessBoard loadedBoard;
    for (int i = 7; i >= 0; --i) {
        std::string line;
        std::getline(inf, line);
        for (int j = 0; j < 8; ++j) {
            loadedBoard.board[i][j].setEmpty();
            char symbol = line[j * 2 + 1];
            Color pieceColor; 
            if(symbol=='.') pieceColor = Color::NOCOLOR;
            else pieceColor = (symbol >= 'a' && symbol <= 'z') ? Color::BLACK : Color::WHITE;
            ChessPiece::Type pieceType;
            switch (std::tolower(symbol)) {
                case 'p': pieceType = ChessPiece::Type::PAWN; break;
                case 'r': pieceType = ChessPiece::Type::ROOK; break;
                case 'n': pieceType = ChessPiece::Type::KNIGHT; break;
                case 'b': pieceType = ChessPiece::Type::BISHOP; break;
                case 'q': pieceType = ChessPiece::Type::QUEEN; break;
                case 'k': pieceType = ChessPiece::Type::KING; break;
                default: pieceType = ChessPiece::Type::EMPTY; break;
            }
            loadedBoard.board[i][j].setType(pieceType);
            loadedBoard.board[i][j].setColor(pieceColor);
            loadedBoard.board[i][j].setRow(i);
            loadedBoard.board[i][j].setCol(j);
        }
    }

    std::string turnLine;
    std::getline(inf, turnLine);
    inf.close();

    if (turnLine == "black") {
        loadedBoard.turn = Color::BLACK;
    } else if (turnLine == "white") {
        loadedBoard.turn = Color::WHITE;
    } else {
        std::cerr << "Error reading turn information from the file!" << std::endl;
        exit(-1);
    }
    
    return loadedBoard;
}