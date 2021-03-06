#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

struct player
{
    char name[20];
    int age;
    int time;
}p;

//global variables
int size=10;
char board[10][10];
char uboard[10][10];

//function declarations
void setupMines();
void buildUserBoard();
void printBoard();
void printUserBoard();
void getInfo();
int findMines(int,int);
int mineSweep(int,int);
void setupGame();
int winCheck();
void win();
void loss();

//main function
int main()
{
    setupGame();
    return 0;
}

void setupGame()
{
    int x,y;
    getInfo();
    system("pause");
    setupMines();
    buildUserBoard();
    printUserBoard();

    for(;;)
    {
        do
        {
            printf("\nEnter row: ");
            scanf("%d",&x);
            printf("Enter column: ");
            scanf("%d",&y);
            printf("\n");
        }while(x<0||x>size-1||y<0||size-1 );

        if (board[x][y] == 'M')
        {
            printf("You have hit a mine!\n\n");
            printBoard();
            loss();
        }
        else
        mineSweep(x,y);
        printUserBoard();
    }
}

void getInfo()
{
    printf("------------------------------------\n");
    printf("WELCOME TO MINESWEEPER\nA project by:\nAtishay Jain(RA1711003010553)\nReet Tuteja(RA1711003010561)\nShubhi Gupta(RA171100300567)\n");
    printf("------------------------------------\n");
    printf("Please enter name:");
    scanf("%s",p.name);
    printf("\nHi %s, Remember if you step on a mine you lose! Use your brains to try and not blow up! Best of luck!\n\n",p.name);
}

void setupMines()
{
    int col,row;
    for(col=0;col<size;col++)
    {
        for(row = 0;row<size;row++)
            board[col][row]='-';
    }
    srand(time(0));
    for(row = 0;row<size;row++)
    {
        int random = (rand()%(size));
        board[random][row]='M';
    }
}

void buildUserBoard()
{
    int col,row;
    for(col=0;col<size;col++)
    {
        for(row=0;row<size;row++)
            uboard[col][row] = '-';
    }
}

void printUserBoard()
{
    int col,row;
    system("cls");
    for(col=0;col<size ; col++)
        printf(" %d ", col);
    printf("\n\n");
    for(col = 0; col<size ; col++)
    {
        for(row = 0;row<size; row++)
        {
            printf(" %c ",uboard[col][row]);
        }
        if(col >= 0 && col<=size )
            printf("   %d", col);
        printf("\n");
    }
}

void printBoard()
{
    int col, row;
    for(col=0;col<size;col++)
        printf(" %d ",col);
    printf("\n");
    for(row = 0;row<size;row++)
    {
        for(col=0;col<size;col++)
            printf(" %c ",board[row][col]);
        if(row>=0 && row<=size-1)
            printf("%d", row);
        printf("\n");
    }
}

void loss()
{
    char ch;
    scanf("%c",&ch);
    printf("You have lost the game!\n\nWould you like to try again?(Y/N):");
    scanf("%c",&ch);
    if(toupper(ch)=='Y')
    {
        system("cls");
        setupGame();
    }
    else
    printf("\nThanks for playing, Goodbye!\n\n");
    exit(0);
}

int mineSweep(int col,int row)
{
    int mines=0;
    if( row < 0 || row >=size || col < 0 || col>=size || uboard[col][row]!= '-')
    {
        return 0;
    }
    mines = findMines(col,row);
    uboard[col][row]=(char)(((int)'0')+mines);
    if(mines<1)
    {
        mineSweep(col,row-1);
        mineSweep(col+1,row-1);
        mineSweep(col+1,row);
        mineSweep(col+1,row+1);
        mineSweep(col,row+1);
        mineSweep(col-1,row+1);
        mineSweep(col-1,row);
        mineSweep(col-1,row-1);
    }
    return 1;
}

int findMines(int row, int col)
{
    int ct=0;

    if(board[row-1][col] == 'M')
        ct++;
    if(board[row+1][col] == 'M')
        ct++;
    if(board[row][col-1] == 'M')
        ct++;
    if(board[row][col+1] == 'M')
        ct++;
    if(board[row-1][col+1] == 'M')
        ct++;
    if(board[row-1][col-1] == 'M')
        ct++;
    if(board[row+1][col+1] == 'M')
        ct++;
    if(board[row+1][col-1] == 'M')
        ct++;
    return ct;
}

int winCheck()
{
    int col,row;
    for(col=1;col<size-1;col++)
        for(row=1;row<size-1;row++)
        {
            if(uboard[col][row]=='-' && board[col][row]!='M')
                return 0;
        }
    return 1;
}

void win()
{
    char ch;
    printf("Congratulations, You have won this game!\nWould you like to play again?(Y/N):");
    scanf("%c",&ch);
    if(toupper(ch)=='Y')
    {
        system("cls");
    }
    else
    exit(0);
}
