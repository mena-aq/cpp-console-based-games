#include <iostream>
using namespace std;

void newSequence(int* arr,int size);
bool guess(int* arr,int size,int& tries);
void changeSize(int* &arr,int& size);

int main()
{
    srand(time(0));
    int size=2;
    int* sequence= new int[size];
    int tries=0;
    newSequence(sequence,size);
    while (size<=10 && tries<3)
    {
        if (guess(sequence,size,tries))
            changeSize(sequence,size);
        newSequence(sequence,size);
    }
    if (size>10)
        cout << "you won!\n";
    else
        cout << "you lost! :( \n";
    return 0;
}

void newSequence(int* arr,int size)
{
    for (int i=0; i<size; i++)
        arr[i]= rand()%100 +1;
}

bool guess(int* arr,int size,int& tries)
{  
    bool levelUp=false;
    for (int i=0; i<size; i++)
    {
        cout << arr[i] <<  ' ';
    }
    cout << "\nready? press any key to proceed\n";
    cin.get();
    system("clear");
    cout << "enter the sequence, one by one: \n";
    int i=0;
    bool mismatch=false;
    int guessNum=-1; 
    while (i<size && !mismatch)
    {
        cout << "enter: ";
        cin >> guessNum;
        if (guessNum!=arr[i])
            mismatch=true;
        i++;
    }
    if (mismatch)
    {
        tries++;
        cout << "try again!\n";
    }
    else
    {
        levelUp=true;
        tries=0;
        cout << "you guessed correctly!\n";
    }
    cin.ignore();    
    return levelUp;
}

void changeSize(int* &arr,int& size)
{
    size++;
    int* temp= new int[size];
    delete[] arr;
    arr=NULL;
    arr=temp;
    temp=NULL;
}