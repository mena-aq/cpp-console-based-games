#include <iostream>
using namespace std;

void displayStartMenu();
void displayGrid(int grid[][7]);
int playerTurn(int player,int grid[][7]);
bool checkWin(int player,int grid[][7]);
bool checkCell(int grid[][7],int x,int y,int dX,int dY);

int main(){
    //create game grid
    int grid[6][7]= {{0}};
    //game loop
    int winner= 0;   //no winning player
    displayStartMenu();
    displayGrid(grid);
    while (!winner){
        int p=1;
        while (!winner and p<=2){
            winner= playerTurn(p,grid);
            system("clear");
            displayGrid(grid);
            p++;
        }
    }
    cout << "congrats! player " << winner << " won!\n";

}

void displayStartMenu(){
    cout << "welcome to connect-4!\nplayer 1 tokens are represented by \'1\' and player 2 tokens by \'2\'\n";
}

void displayGrid(int grid[][7]){
    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            cout << grid[i][j] << ' ';
        }
        cout << endl;
    }
}

int playerTurn(int player,int grid[][7]){
    int col;
    bool validCol;
    do{
        validCol= true;
        cout << "player " << player << ",which col to place token? 1-7: ";
        cin >> col;
        if (grid[0][col-1]!=0||!(col>=1&&col<=7)){ //space taken or out of range
            validCol= false;
            cout << "invalid column, try again!\n";
        }
    }while(!validCol);
    col--; 
    //place token
    for (int i=5; i>=0; i--){ //from bottom check for bottommost empty space
        if (grid[i][col]==0){
            grid[i][col]= player;
            break;
        }
    }
    if (checkWin(player,grid))
        return player;
    return 0;
}

bool checkWin(int player,int grid[][7]){
    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            if (grid[i][j]==player){
                //check horizontal-right
                if (j<4)
                    if (checkCell(grid,j,i,1,0))
                        return true;
                //check vertical down
                if (i<3)
                    if (checkCell(grid,j,i,0,1))
                        return true;
                //check diagonal right
                if (i<3 && j<4)
                    if (checkCell(grid,j,i,1,1))
                        return true;
                //check diagonal left
                if (i<3 && j>2)
                    if (checkCell(grid,j,i,-1,1))
                        return true;
            }    
        }
    }
    return false;
}

bool checkCell(int grid[][7],int x,int y,int dX,int dY){
    int newX,newY;
    for (int i=1; i<4; i++){
        newX= x+ i*dX;
        newY= y+ i*dY;

        if (grid[y][x]!=grid[newY][newX])
            return false;
    }
    return true;
}

