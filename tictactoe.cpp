#include <iostream>
using namespace std;

void setUp(char players[][2],string &p1_name,string &p2_name);
void drawBoard(char board[][3]);
int gamePlay(char players[][2],char board[][3],bool &draw,bool &win);

int main()
{
    char players[2][2]={' '};
    char board[3][3];
    //initialise board
    for (int i=0;i<3;i++)
    {
        for (int j=0;j<3;j++)
            board[i][j]=' ';
    }
    string p1_name,p2_name;
    setUp(players,p1_name,p2_name);
    drawBoard(board);
    bool draw=false;
    bool win=false;
    int winner=gamePlay(players,board,draw,win);
    if (win)
        cout << "player " << players[winner][1] <<" wins\n";
    else
        cout << "draw\n";
    return 0;

}

void setUp(char players[][2],string &p1_name,string &p2_name)
{
    srand(time(0));
    cout << "enter your name, player 1: ";
    cin >> p1_name;
    cout << "enter your name, player 2: ";
    cin >> p2_name;
    //who goes first
    int die_p1,die_p2;
    do
    {
        die_p1= rand()%6 +1;
        die_p2= rand()%6 +1;
        cout << "player 1 rolled " << die_p1 << " and player 2 rolled " << die_p2 << endl;
    } while (die_p1==die_p2);
    if (die_p1>die_p2)//player 1 first
    {
        cout << "player 1 goes first!\n";
        players[0][1]=49;
        players[1][1]=50;   //ascii
    }
    else
    {
        cout << "player 2 goes first!\n";
        players[0][1]=50;
        players[1][1]=49;
    }
    //choose X or O
    do
    {
        cout << "player " << players[0][1] << " choose your character, X or 0?: ";
        cin.ignore();
        cin >> players[0][0];
        if (players[0][0]=='X')
            players[1][0]='O';
        else
            players[1][0]='X';
    } while (!(players[0][0]=='X'||players[0][0]=='O'));   
}

void drawBoard(char board[][3])
{
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            cout << '[' << board[i][j] << ']';
        }
        cout << "\n";
    }
}

int gamePlay(char players[][2],char board[][3],bool &draw,bool &win)
{
    int turn=0;
    int row,col;
    while (!(draw||win))
    {
        turn%=2;  //0,1,0,1,..
        while (!(draw||win)&&turn<2)
        {
            cout << "player " << players[turn][1] << "'s turn\n";
            row=-1;
            col=-1;
            do
            {
                cout << "which row?: ";
                cin >> row;
                cout << "which column?: ";
                cin >> col;
            }while(board[row][col]!=' ' || row>2 || col>2);
            board[row][col]=players[turn][0];
            drawBoard(board);
            //check for win, whoever just had their turn will be winner
                // check horizontal
                for (int i=0; i<3; i++)
                {
                    if (board[i][0]==board[i][1] && board[i][0]==board[i][2] && board[i][0]!=' ')
                    {
                        win=true;
                        break;
                    }                       
                }
                //check vertical
                 for (int j=0; j<3; j++)
                {
                    if (board[0][j]==board[1][j] && board[0][j]==board[2][j] && board[0][j]!=' ')
                    {
                        win=true;
                        break;
                    }
                       
                }
                //check diagonal 1
                if (board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[0][0]!=' ')
                    win=true;
                //check diagonal 2
                if (board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[0][2]!=' ')
                    win=true;

            //check for draw
            if (!win)
            {
                draw=true;
                for (int i=0; i<3; i++)
                {
                    for (int j=0; j<3; j++)
                    {
                        if (board[i][j]==' ')
                            draw=false;
                    }
                }
                turn++;
            }
            
        }
    }
    return turn;
}