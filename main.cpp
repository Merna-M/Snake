#include <iostream>
#include "snake.h"

using namespace std;

// boolean variable to check the game loss
bool isLoss = false;

// snake length
unsigned int snake_size = 1;


int main()
{
    Setup();
    while(true){
        while(!isLoss){
            for(int i=0 ; i<1000000 ; i++); // delay
            GameGetInput();
            GameDraw();
        }
        cout << endl <<endl << "Game Over" << endl;
        cout << "Would you like to play Again? <y/n>: " << endl;
        cout << "Your Option: ";
        char option;
        do{
            cin >> option;
            if(option != 'y' && option != 'Y' && option != 'n' && option != 'N'){
                cout << "Wrong Option, press <y/n>" << endl;
                cout << "Your Option: ";
            }
        }while(option != 'y' && option != 'Y' && option != 'n' && option != 'N');
        if(option == 'n' || option == 'N'){
            break;
        }else{
            Setup();
        }
    }
    return 0;
}
