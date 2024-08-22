#ifndef _SNAKE_H
#define _SNAKE_H

#define WIDTH             30
#define HEIGHT            20

#define PRESS_UP          1
#define PRESS_DOWN        2
#define PRESS_RIGHT       3
#define PRESS_LEFT        4


typedef struct position{
    int X;
    int Y;

    position(int x,int y):X(x),Y(y) {}
    position(){}

    bool operator==(const position& p)const{
        return X==p.X && Y==p.Y;
    }
}position;


struct pHash{
    std::size_t operator()(const position& obj)const{
        //combine hash of X and Y
        return std::hash<int>()(obj.X) ^ std::hash<int>()(obj.Y);
    }
};


void Setup(void);
void SetFruit(void);
void checkWinLoss(void);
void GameDraw(void);
void GameGetInput(void);



#endif // _SNAKE_H
