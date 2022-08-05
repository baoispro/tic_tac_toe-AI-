#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//Hàm chung
void clear()
{
   fflush(stdin); 
}
int random(int minN, int maxN){
    srand(time(NULL));
    return minN + rand() % (maxN + 1 - minN);
}
int convert_char_to_int(char a)
{
    return a-'0';
}
// Hàm riêng
void drawboard(char board[])
{
    printf("%c%s%c%s%c\n",board[7],"|",board[8],"|",board[9]);
    clear();
    printf("-+-+-\n");
    printf("%c%s%c%s%c\n",board[4],"|",board[5],"|",board[6]);
    clear();
    printf("-+-+-\n");
    printf("%c%s%c%s%c\n",board[1],"|",board[2],"|",board[3]);
    clear();
}

const char* inputPlayerLetter()
{
    char letter[3];
    while(letter[0]!='X'&& letter[0]!='O')
    {
        printf("Do you want to be X or O?\n");
        clear();
        fgets(letter,3,stdin);
        clear();
        strupr(letter);
    }
    if (letter[0]=='X')
    {
        return "XO";
    }
    else
    {
        return "OX";
    }
}


const char* Whogofirst ()
{
   if (random(0,1)==1)
        return "computer";
    return "player";
}

const char* Makemove (char board[],int move,char letter)
{
    board[move]=letter;
    return board;
}

bool isWinner (char bo[],char le)
{
    if(bo[7] == le && bo[8] == le && bo[9] == le||
    bo[4] == le && bo[5] == le && bo[6] == le||
    bo[1] == le && bo[2] == le && bo[3] == le||
    bo[7] == le && bo[4] == le && bo[1] == le||
    bo[8] == le && bo[5] == le && bo[2] == le||
    bo[9] == le && bo[6] == le && bo[3] == le||
    bo[7] == le && bo[5] == le && bo[3] == le||
    bo[9] == le && bo[5] == le && bo[1] == le)
    {
        return true;
    }
    return false;
}

char* copyBoard (char board[])
{
    char *copy_board;
    copy_board=(char*)malloc(sizeof(char)*10);
    for(int i=0;i<10;i++)
    {
        copy_board[i]=board[i];
    }
    return copy_board;

}

bool isspacefree (char board[],int move)
{
    if (move>10)
    {
        move = 0;
    }
    if (board[move]==' ')
        return true;
    return false;
}

int getplayermove (char board[])
{
    char move =' ';
    int move_int=convert_char_to_int(move);
    move_int=0;
    board[move_int]='1';
    while(move !='1'&&move !='2'&&move !='3'&&move !='4'&&move !='5'&&move !='6'&&move !='7'&&move !='8'&&move !='9' || isspacefree(board,move_int)==false)
    {
        printf("What is your next move?(1->9)?\n");
        clear();
        scanf("%c",&move);
        clear();
        move_int=convert_char_to_int(move);
    }
    return move_int;
}

int chooseRandom (char board[],int movelist[],int n)
{
    int *possibleMove;
    possibleMove=(int*)malloc(sizeof(int)*n);
    int choose;
    int count=0;
    int j=0;
    for(int i=0;i<n;i++)
    {
        if(isspacefree(board,movelist[i])==true)
        {
            possibleMove[j]=movelist[i];
            count++;
            j++;
        }
    }
    n=count;
    possibleMove=(int*)realloc(possibleMove,sizeof(int)*n);
    if(n!=0)
    {
        choose=possibleMove[random(0,n-1)];
        return choose;
    }
    return 11;
    
}

int getcomputermove(char board[], char computerleter,char playerletter)
{
    if (computerleter=='X')
    {
        playerletter='O';
    }
    else
        playerletter=='X';
    
    for(int i=0;i<10;i++)
    {
        char boarcopy[10];
        strcpy(boarcopy,copyBoard(board));
        if(isspacefree(boarcopy,i)==true)
        {
            boarcopy[i]=computerleter;
            if(isWinner(boarcopy,computerleter))
            {
                return i;
            }
        }
    }

     for(int i=0;i<10;i++)
    {
        char boarcopy[10];
        strcpy(boarcopy,copyBoard(board));
        if(isspacefree(boarcopy,i)==true)
        {
            boarcopy[i]=playerletter;
            if(isWinner(boarcopy,playerletter))
            {
                return i;
            }
        }
    }

    int list_odd[4] = {1,3,7,9};
    int list_even[4] = {2,4,6,8};

    int move= chooseRandom(board,list_odd,4);
    if(move!=11)
    {
        return move;
    }
    if(isspacefree(board,5)==true)
    {
        return 5;
    }
    return chooseRandom(board,list_even,4);
}

bool isboardfull (char board[])
{
    for(int i=0;i<10;i++)
    {
        if(isspacefree(board,i)==true)
            return false;
    }
    return true;
}
int main()
{
    printf("Welcome to Tic-Tac-Toe!\n");
    while(true)
    {
        char board[10];
        for(int i=0;i<10;i++)
        {
            board[i]=' ';
        }
        char le[3];
        strcpy(le,inputPlayerLetter());
        char playerletter, computerletter;
        playerletter = le[0];
        computerletter = le[1];
        char turn [20];
        strcpy(turn,Whogofirst());
        printf("The %s will go first\n",turn);
        bool gameisplaying = true;
        while (gameisplaying==true)
        {
            if(strcmp(turn,"player")==0)
            {
                drawboard(board);
                int move = getplayermove(board);
                board[move]=playerletter;
                if (isWinner(board,playerletter)==true)
                {
                    drawboard(board);
                    printf("Hooray! You have won the game!!!!\n");
                    gameisplaying = false;
                }
                else
                {
                    if (isboardfull(board)==true)
                    {
                        drawboard(board);
                        printf("Tie\n");
                        break;
                    }
                    else
                    {
                        strcpy(turn,"computer");
                    }
                }
            
            }
            else
            {
                int move = getcomputermove(board,computerletter,playerletter);
                board[move]=computerletter;
                if (isWinner(board,computerletter)==true)
                {
                    drawboard(board);
                    printf("You lose!!!\n");
                    gameisplaying = false;
                }
                else
                {
                    if (isboardfull(board)==true)
                    {
                        drawboard(board);
                        printf("Tie\n");
                        break;
                    }
                    else
                    {
                        strcpy(turn,"player");
                    }
                }
            }
        }
        printf("Do you want to play again?(y or n)");
        char answer;
        do 
        {
            scanf("%c",&answer);
        }
        while(answer!='y'&&answer!='n');
        if(answer=='n')
            {
                break;
            }
    }
    return 0;
}