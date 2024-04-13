#include <iostream>
using namespace std;

int** initBoard(int size);
void placeMines(int** board,int size);
void drawBoard(int** board,int size);
void play(int** board,int size);
int countMines(int** board,int size,int y,int x);
bool checkWin(int** board,int size);
void endGame(int** board,int size);

int main(){
    int size=8;
    int** board= initBoard(size);
    drawBoard(board,size);

    bool end= false;
    int x,y;
    while (!end){
        do{
        cout << "enter y:";
        cin >> y;
        cout << "enter x:";
        cin >> x;
        }while(!(x>=0&&x<size && y>=0&&y<size));
        if (board[y][x]==-2)
            board[y][x]= countMines(board,size,y,x);
        else if (board[y][x]==-1){ //mine, lost
            end= true;
            cout << "oops! there was a mine there!\n";
        }
        else    
            cout << "already uncovered\n";
        if (!end){
            end= checkWin(board,size);
            if (end)
                cout << "you won!";
            drawBoard(board,size);
        }
    }
    
    endGame(board,size);
    return 0;
}

int** initBoard(int size){
    //create 2D DMA array
    int** board= new int*[size];
    for (int i=0; i<size; i++){
        board[i]= new int[size];
        for (int j=0; j<size; j++)
            board[i][j]= -2; //not set yet
    }
    //setup
    placeMines(board,size);
    return board;
}

void placeMines(int** board,int size){
    //10 mines, represented by -1
    int randX,randY;
    int mines=0;
    do{
        randX= rand()%size;
        randY= rand()%size;
        if (board[randY][randX]!=-1){
            board[randX][randY]=-1; //place mine
            mines++;
        }
    }while(mines<10);
}

void drawBoard(int** board,int size){
    for (int i=0; i<size; i++){
        for (int j=0; j<size; j++){
            if (board[i][j]>=0)
                cout << '[' << board[i][j] << ']';
            else
                cout << '[' << ' ' << ']';
        }
        cout << "\n";
    }

}

int countMines(int** board,int size,int y,int x){
    int mines=0;
    if (y>0){
        if (board[y-1][x]==-1)
            mines++;
        if (x>0){
            if (board[y-1][x-1]==-1)
                mines++;
        }
        if (x<size-1){
            if (board[y-1][x+1]==-1)
                mines++;
        }
    }
    if (y<size-1){
        if (board[y+1][x]==-1)
            mines++;
        if (x>0){
            if (board[y+1][x-1]==-1)
                mines++;
        }
        if (x<size-1){
            if (board[y+1][x+1]==-1)
                mines++;
        }
    }
    if (x>0){
        if (board[y][x-1]==-1)
            mines++;
    }
    if (x<size-1){
        if (board[y][x+1]==-1)
            mines++;
    }
    return mines;
}

bool checkWin(int** board,int size){
    bool won= true;
    int i=0; 
    while(i<size){
        int j=0; 
        while(j<size){
            if (board[i][j]==-2)  //all uncovered so no -2's
                won=false;
            j++;
        }
        i++;
    }
    return won;
}

void endGame(int** board,int size){
    for (int i=0; i<size; i++){
        for (int j=0; j<size; j++){
            if (board[i][j]==-2)
                board[i][j]= countMines(board,size,i,j);
            if (board[i][j]!=-1)
                cout << "[ " << board[i][j] << ']';
            else
                cout << '[' << board[i][j] << ']';

        }
        cout << "\n";
    }
    for (int i=0; i<size; i++)
        delete[] board[i];
    delete[] board;
}


//8x8 array, dynamic memory and pointers
//functions:
//placeMines(), 10 mines
//initBoard() calls placeMines(), set numbers
//play()
// quit when hit mine or all non-mines uncovered
// if numbered only uncover it
// if 0 then floodfill: 4 3box side expansions, for each side expand until all 3 are numbers or boundary reached
// drawBoard() just shows board
