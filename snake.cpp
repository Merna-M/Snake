#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <deque>
#include <unordered_set>
#include <functional>
#include "snake.h"

using namespace std;

position fruit;
deque<position> snake;
unordered_set<position,pHash> snakeMap;

extern bool isLoss;
int current_press = 0;
extern unsigned int snake_size;

/***********************************************************************************************/
/*
Setup some configurations at the beginning of the play
*/
/***********************************************************************************************/
void Setup(void){
    // clear all lists and maps for a new game
    snake.clear();
    snakeMap.clear();
    isLoss = false; // no loss at the start of play
    current_press = 0;
    snake_size = 1;

    //seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    // make the cursor invisible
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Set the cursor visibility to false
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    // set the start location at the middle of the board
    snake.push_back(position((WIDTH-1)/2,(HEIGHT-1)/2));
    snakeMap.insert({(WIDTH-1)/2,(HEIGHT-1)/2});

    // Get a random location for fruit
    SetFruit();
    // Draw the Game
    GameDraw();
}

/***********************************************************************************************/
/*
Set some random location for the fruit
*/
/***********************************************************************************************/
void SetFruit(void){
    fruit.X = rand()%(WIDTH-2) + 1;
    fruit.Y = rand()%(HEIGHT-2) + 1;
}

/***********************************************************************************************/
/*
if the snake reached any of the edges, isLoss is set to true to indicate the loss
also checks if the snake ate the fruit to increase the size of the snake
*/
/***********************************************************************************************/
void checkWinLoss(void){
    if(snake[0].X==0 || snake[0].X==WIDTH-1){
        isLoss = true;
    }
    if(snake[0].Y==0 || snake[0].Y==HEIGHT-1){
        isLoss = true;
    }

    if(snake[0].X==fruit.X && snake[0].Y==fruit.Y){
        SetFruit();
        snake_size++;
    }
}

/***********************************************************************************************/
/*
configure the new position of the head of the snake and draw the play
*/
/***********************************************************************************************/
void GameDraw(void){
    // clear console
    system("cls");
    //check if the snake reached any edge or ate the fruit
    checkWinLoss();

    int Leng = snake.size();
    //snake ate a new fruit
    if(snake_size > Leng){
        snake.push_back(snake[Leng-1]);
    }

    // update the head of the snake according to its direction
    position p = snake[0];
    if(current_press==PRESS_UP){
        p.Y = snake[0].Y+1;
    }else if(current_press == PRESS_DOWN){
        p.Y = snake[0].Y-1;
    }else if(current_press == PRESS_LEFT){
        p.X = snake[0].X-1;
    }else if(current_press == PRESS_RIGHT){
        p.X = snake[0].X+1;
    }

    // check if the head of the snake pumped into any part of its body
    auto it = snakeMap.find(p);
    if(it != snakeMap.end() && snake_size!=1){
        isLoss = true;
    }

    // erase the end position of snake as an update if the length is the same as previous
    if(snake_size <= snakeMap.size()){
        it = snakeMap.find(snake[Leng-1]);
        snakeMap.erase(it);
    }

    // add the new updates
    snake.push_front(p);
    snakeMap.insert(p);
    snake.pop_back();

    // draw the game
    for(int i=0 ; i<WIDTH ; i++){
        cout << '#';
    }
    cout << endl;
    for(int i=1 ; i<HEIGHT-1 ; i++){
        cout << '#';
        for(int j=1 ; j<WIDTH-1 ; j++){
            position p = {j,i};
            // check if the position is part of the snake
            auto it = snakeMap.find(p);
            // draw F for the fruit
            if(fruit.X==j && fruit.Y==i)
                cout << 'F';
            // draw O for snake body
            else if(it != snakeMap.end())
                cout << 'O';
            else
                cout << ' ';
        }
        cout << '#' << endl;
    }
    for(int i=0 ; i<WIDTH ; i++){
        cout << '#';
    }
}

/***********************************************************************************************/
/*
Get input from keyboard
*/
/***********************************************************************************************/
void GameGetInput(void){
    // check if keyboard is hit
    if(_kbhit()){
        int key = _getch();
        // special key
        if(key == 0xE0){
            key = _getch();
            switch(key){
            case 72: // down
                current_press = PRESS_DOWN;
                break;
            case 80: // up
                current_press = PRESS_UP;
                break;
            case 75: // left
                current_press = PRESS_LEFT;
                break;
            case 77: // right
                current_press = PRESS_RIGHT;
                break;
            default:
                break;
            }
        }
    }
}

/***********************************************************************************************/
