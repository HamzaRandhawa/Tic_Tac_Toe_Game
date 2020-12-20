#include <iostream>
#include <windows.h>
#include <fstream>
#include <stdlib.h>

using namespace std;
bool IsWin (char Board[], int dim, char S,int ri, int ci);
void Write_on_Board(char Board[],int dim, int  ri, int ci, char S);
void TurnChange ( int & Turn);

void Initialize (char Board [] ,int dim)
{
    for(int i=0;i<dim*dim;i++)
    {
        Board[i]='-';
    }
}
int TwoD_to_OneD (int ri, int ci, int dim)
{
    return ((ri-1)*dim)+(ci-1);

}
void Print_Board(char Board[],int dim)
{
    cout<<"\n";
    int index;
 for(int ri=1;ri<=dim;ri++)
 {
    for(int ci=1;ci<=dim;ci++)
    {
        index=TwoD_to_OneD(ri,ci,dim);
        cout<<"\t"<<Board[index];
    }
    cout<<"\n\n\n";
 }
}
bool IsLegalMove (char Board[],int ri,int ci, int dim)
{
    if (ri<1 || ri>dim || ci<1 || ci>dim)
        return false;
    int index = TwoD_to_OneD(ri,ci,dim);
    if (Board[index] != '-')
        return false;
    else
        return true;
}
bool Is_CompWin (char B[],char CBoard[], int & ri, int & ci, int Turn, int dim,char S)
{
    int r;
    for (r=1; r<=dim; r++)
    {
        int c;
        for (c=1; c<=dim; c++)
        {
            if (IsLegalMove(B,r,c,dim) )
            {
                Write_on_Board(CBoard,dim,r,c,S);


                if (IsWin(CBoard,dim,S,r,c) )
                {
                    ri=r;
                    ci=c;
                    break;
                }
                else
                    Write_on_Board(CBoard,dim,r,c,'-');
            }
        }
        if (IsWin(CBoard,dim,S,r,c) )
                {
                    ri=r;
                    ci=c;
                    return 1;
                }
    }
    return false;
}
void Stop_Win (char B[],char CBoard[],char PSymbol[], int & ri, int & ci, int Turn, int dim,char S)
{
    TurnChange(Turn);
    int r;
    for (r=1; r<=dim; r++)
    {
        int c;
        for (c=1; c<=dim; c++)
        {
            if (IsLegalMove(B,r,c,dim) )
            {
                Write_on_Board(CBoard,dim,r,c,PSymbol[Turn]);


                if (IsWin(CBoard,dim,PSymbol[Turn],r,c) )
                {
                    ri=r;
                    ci=c;
                    break;
                }
                else
                    Write_on_Board(CBoard,dim,r,c,'-');
            }
        }
        if (IsWin(CBoard,dim,PSymbol[Turn],r,c) )
                {
                    ri=r;
                    ci=c;
                    TurnChange(Turn);
                    break;
                }
    }
}
void CompMove (char B[],char CBoard[],char PSymbol[], int & ri, int & ci, int Turn, int dim,char S )
{
    do
    {
        ri=rand()%dim+1;
        ci=rand()%dim+1;
    }
    while ((IsLegalMove(B,ri,ci,dim))==false );
    if (Is_CompWin(B,CBoard,ri,ci,Turn,dim,S))
    {

    }
    else
        Stop_Win(B,CBoard,PSymbol,ri,ci,Turn,dim,S);
}

void Ask_for_Move(char B[],char CBoard[],char PSymbol[],int & ri, int & ci, int Turn, int dim,char S)
{
    if (Turn==1)
        {
            CompMove(B,CBoard,PSymbol, ri, ci, Turn,dim,S);
        }
    else if (Turn==0)
    {
        cout<<"\nP"<<Turn+1<<"'s Move :";
        cin>>ri>>ci;
    }
}
void Write_on_Board(char Board[],int dim, int  ri, int ci, char S)
{
    int index=TwoD_to_OneD(ri,ci,dim);
    Board[index]=S;
}
void TurnChange ( int & Turn)
{
    Turn=(Turn+1)%2;
}

bool Is_Draw (char Board[], int dim)
{
    int index;
    for (int ri=1;ri<=dim;ri++)
    {
        for (int ci=1;ci<= dim;ci++)
        {
            index=TwoD_to_OneD(ri,ci,dim);
            if ((Board[index]=='-') )
            {
                return false;
            }
        }
    }
    return true;
}
bool Is_D1_Win (char Board[], int dim, char S)
{
    for (int ci=1, ri=1; ci<=dim; ri++, ci++)
    {
        int index=TwoD_to_OneD(ri,ci,dim);
        if (Board[index]!=S || Board[index]=='-' )
            return false;
    }
    return true;
}
bool Is_D2_Win (char Board[], int dim, char S)
{
    for (int ci=dim, ri=1; ri<=dim; ri++, ci--)
    {
        int index=TwoD_to_OneD(ri,ci,dim);
        if (Board[index]!=S || Board[index]=='-' )
            return false;
    }
    return true;
}
bool IsV_Win (char Board[], int dim, char S,int ri, int ci)
{
    for (int ri=1;ri<=dim; ri++)
    {
     int index=TwoD_to_OneD(ri,ci,dim);
        if (Board[index]!=S || Board[index]=='-' )
            return false;
    }
    return true;
}
bool IsH_Win (char Board[], int dim, char S,int ri, int ci)
{
    for (int ci=1;ci<=dim; ci++)
    {
     int index=TwoD_to_OneD(ri,ci,dim);
        if (Board[index]!=S || Board[index]=='-' )
            return false;
    }
    return true;
}
bool IsWin (char Board[], int dim, char S,int ri, int ci)
{
    if (Is_D1_Win(Board,dim,S)||Is_D2_Win(Board,dim,S)
    || IsV_Win(Board,dim,S,ri,ci) || IsH_Win(Board,dim,S,ri,ci))
        return true;
    else
        return false;
}
void Writer (char B[], int dim, int Turn)
{
    ofstream givingTo ("Game.txt");
    givingTo<<Turn<<" ";
    for (int i=0; i<dim*dim; i++)
    {
        givingTo<<B[i]<<" ";
    }
}
void Reader (char B[], int dim, int Turn)
{
    ifstream takingFrom ("Game.txt");
    takingFrom>>Turn;
    for (int i=0; i<dim*dim; i++)
    {
        takingFrom>>B[i];
    }
}

int main()
{
    char PSymbol [2]={'X','O'};
    int dim;

    cout<<"Enter Dimension : ";
    cin>>dim;

    char Board [dim*dim],choice ;
    char CBoard [dim*dim] ;
    int ri, ci;
    int v=0, Turn=0;



    cout<<"Do You want To Start New Game or Load Game (N/L) : ";
    cin>>choice;

    if(choice =='N' || choice == 'n')
    Initialize(Board,dim);

    else if (choice == 'L' || choice == 'l')
    {
        Reader(Board,dim,Turn);
    }

        for (int i=0; i<dim*dim; i++)
    {
        CBoard[i]=Board[i];
    }

    do
    {
        system ("cls");
        Print_Board(Board,dim);
        do
        {
            cout<<"\nEnter [Row , Column] [0,0 To Save] : ";
            Ask_for_Move(Board,CBoard,PSymbol,ri,ci,Turn,dim,PSymbol[Turn]);
            if (ri==0 && ci==0)
            {
                Writer(Board,dim,Turn);
                exit(1);
            }

        }
        while ((IsLegalMove(Board,ri,ci,dim))==false );

        Write_on_Board(Board,dim,ri,ci,PSymbol[Turn]);
        Write_on_Board(CBoard,dim,ri,ci,PSymbol[Turn]);
        if (IsWin(Board,dim,PSymbol[Turn],ri,ci)==true)
        {
            v=1;
            break;
        }
        TurnChange(Turn);
    }
    while (Is_Draw(Board,dim)==false);
    system ("cls");
    Print_Board(Board,dim);
    if (v==1)
    {
        cout<<"\n\nPlayer "<<Turn+1<<" Wins!";
    }
    else
        cout<<"\n Draw!";
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    return 0;
}
