#include <iostream>
using namespace std;

int x=0; 
int y=1;
//20x20 board

//prototypes
int** gameSetup(int apple[],int &size);
void drawBoard(int** snake,int apple[],int size);
bool moveSnake(int** snake,int size);
bool eatApple(int** snake,int size,int apple[]);
int** sizeUp(int** snake,int &size,int &score);

int main()
{
    srand(time(0));
    int apple[2]={0};
    int size=0;
    int score=0;
    int** snake=gameSetup(apple,size);
    drawBoard(snake,apple,size);
    bool play= moveSnake(snake,size);
    while (play)
    {
        system("clear");
        drawBoard(snake,apple,size);
        play= moveSnake(snake,size);
        if (eatApple(snake,size,apple))
            snake= sizeUp(snake,size,score);
    }
    cout << "game over!\n";
    cout << "score: " << score << endl;

    return 0;
}

int** gameSetup(int apple[],int &size)
{
    //create snake array
    size=1;
    int** snake= new int*[size];
    snake[0]= new int[2];
    //set initial coordinate of snake
    snake[0][x]= rand()%7 +1; //1 to 28
    snake[0][y]= rand()%7 +1;
    //set initial coordinate of apple
    do
    {
        apple[x]= rand()%7 +1;
        apple[y]= rand()%7 +1;
    }while(apple[x]==snake[0][x] && apple[y]==snake[0][y]);

    return snake;
}

void drawBoard(int** snake,int apple[],int size)
{
    for (int i=0; i<10; i++)
    {
        for (int j=0; j<10; j++)
        {
            bool snakeThere=false;
            //check if snake there
            for (int k=0; k<size; k++)
            {
                if (snake[k][y]==i && snake[k][x]==j)
                    snakeThere=true;
            }
            if (i==0||i==9||j==0||j==9)
                cout << '#';
            else if (apple[y]==i && apple[x]==j)
                cout << '@';
            else if(snakeThere)
                cout << 'o';
            else
                cout << ' ';
        }
        cout << "\n";
    }
}

bool moveSnake(int** snake,int size)
{
    char move;
    //move segments 
    for (int i=size-1; i>0; i--)
    {
        snake[i][x]=snake[i-1][x];
        snake[i][y]=snake[i-1][y];
    }
    bool alive;
    do
    {
        cout << "enter your move, A/W/S/D: ";
        cin >> move;
    }while(!(move=='A'||move=='W'||move=='S'||move=='D'));
    alive=true;
    switch(move)
    {
        case 'A':
            if (snake[0][x]>1)
                snake[0][x]--;
            else
                alive=false;
            break;
        case 'W':
            if (snake[0][y]>1)
                snake[0][y]--;
            else
                alive=false;
            break; 
        case 'S':
            if (snake[0][y]<8)
                snake[0][y]++;
            else
                alive=false;
            break;    
        case 'D':
            if (snake[0][x]<8)
                snake[0][x]++;
            else
                alive=false;
            break;  
    }
    return alive;
}

bool eatApple(int** snake,int size,int apple[])
{
    if (snake[0][x]==apple[x]&&snake[0][y]==apple[y])
    {
        apple[x]= rand()%7 +1;
        apple[y]= rand()%7 +1;        
        return true;
    }
    else
        return false;
}

int** sizeUp(int** snake,int &size,int &score)
{
    //create tmp array
    int** tmp= new int*[size];
    for (int i=0; i<size; i++)
        tmp[i]= new int[2];
    //copy from snake to tmp
    for (int i=0; i<size; i++)
    {
        for (int j=0; j<2; j++)
            tmp[i][j]=snake[i][j];
    }
    //copy back
    snake= nullptr;
    snake= new int*[size+1];
    for (int i=0; i<size+1; i++)
        snake[i]= new int[2];
    for (int i=0; i<size; i++)
    {
        for (int j=0; j<2; j++)
            snake[i][j]=tmp[i][j];
    }
    //delete tmp
    for (int i=0; i<size; i++)
        delete[] tmp[i];
    delete[] tmp;

    size++;
    score+=5;

    return snake;
}