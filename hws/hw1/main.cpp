#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "board.h"

using namespace std;

/*

Hakan Keser - 220104004073

*/


void menu();

int main(){
    
    menu();
}


void menu(){
    ChessBoard game;
    int userInput;
    string line;
    do{
        cout<<"1- Play a new chess game"<<endl;
        cout<<"2- Load from a previous chess game"<<endl;
        cout<<"3- Exit"<<endl;
        cout<<"Enter your choice: ";
        //cin>>userInput;
        
        getline(cin, line);
        userInput = line[0]-'0';
        switch(userInput){
            case 2:
                game = game.load();
            case 1:
            while(game.playTurn());
                cout<<"GAME ENDED!"<<endl<<endl;
                break;
            case 3:
            break;
            default:
            cout<<"Invalid input!"<<endl;
        }
    }while(userInput!=3);

}