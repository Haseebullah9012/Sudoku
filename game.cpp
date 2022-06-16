#include <iostream>
#include <string.h>
using namespace std;

void Board();
void InitializeBoard();

void Input();
bool isBuiltinBox(int,int);
bool isValidBox(int,int, int);

bool isPresentInRow(int,int);
bool isPresentInCol(int,int);
bool isPresentInBlock(int,int, int);

void SwapNums(int,int);
void SwapRows(int,int);
void SwapRowBlocks(int,int);
void SwapCols(int,int);
void SwapColBlocks(int,int);
void SwapValues(int &, int &);

int rows = 9, cols = 9;
int board[9][9] = {0};
//int builtin[9][9] = {0};
int builtin[9][9] =
                {
                    {1,2,3,  4,5,6,  7,8,9},
                    {4,5,6,  7,8,9,  1,2,3},
                    {7,8,9,  1,2,3,  4,5,6},

                    {2,3,1,  5,6,4,  8,9,7},
                    {5,6,4,  8,9,7,  2,3,1},
                    {8,9,7,  2,3,1,  5,6,4},

                    {3,1,2,  6,4,5,  9,7,8},
                    {6,4,5,  9,7,8,  3,1,2},
                    {9,7,8,  3,1,2,  6,4,5}
                };

int main()
{
    cout << endl;
    InitializeBoard();
    Board();

    while(true)
    {
        cout << "Select the Box (Row Col) on the Board: ";
        Input();
    }

    getchar();
    return 0;
}

void Board()
{
    cout << endl;
	for(int r=0; r<rows; r++)
    {	
        if(r%3 == 0)
            cout << "\t ------------------------- \n";
        
        cout << "\t ";
		for(int c=0; c<cols; c++) {
            if(c%3 == 0)
                cout << "| ";
            
            if(board[r][c] == 0)
                cout << board[r][c] << " ";
            else if(board[r][c] == builtin[r][c])
                cout << "\033[4;1;32m" << board[r][c] << "\033[0m ";
            else
                cout << "\033[36m" << board[r][c] << "\033[0m ";
        }
		cout << "| \n";
	}
    cout << "\t ------------------------- \n";
	cout << endl;
}

void InitializeBoard()
{
    for(int r=0; r<rows; r++)
        for(int c=0; c<cols; c++)
            if(random()%2==0)
                board[r][c] = builtin[r][c]; //Place the Number with 1/2 Probability (50% Chance)
    
    //Swap Numbers
    for(int n=1,x=1; n<=9; n++) {
        while(n == x)
            x = random()%9 +1;
        
        SwapNums(n,x);
    }
    
    int box;
    //Swap Rows
    for(int r=1,x=1; r<=9; r++)
    {    
        box = (r-1)/3;
        while(box*3 +x == r)
            x = random()%3 +1;
        
        SwapRows(r, box*3 +x);
    }

    //Swap Columns
    for(int c=1,x=1; c<=9; c++)
    {    
        box = (c-1)/3;
        while(box*3 +x == c)
            x = random()%3 +1;
        
        SwapCols(c, box*3 +x);
    }

    //Swap RowBlocks
    for(int r=1,x=1; r<=3; r++)
    {    
        while(x == r)
            x = random()%3 +1;
        
        SwapRowBlocks(r, x);
    }

    //Swap ColumnBlocks
    for(int c=1,x=1; c<=3; c++)
    {    
        while(x == c)
            x = random()%3 +1;
        
        SwapColBlocks(c, x);
    }

    //Make The Builtin the Same as Board
    for(int r=0; r<rows; r++)
        for(int c=0; c<cols; c++)
                builtin[r][c] = board[r][c];
}


void Input()
{
    int a,b;
    cin >> a >> b;    
    if(a<1 || a>rows || b<1 || b>cols) {
        cout << "Oops! Its Outside the Box. There are only 9 Rows and Columns. \n\n";
        return;
    }
    
    if(isBuiltinBox(a-1,b-1)) {
        cout << "Oops! Its a Builtin Box, with Predefined Value. \n\n";
        return;    
    }
    
    int value;
    cout << "Enter the Number: ";
    cin >> value;
    if(value<0 || value>9) {
        cout << "Oops! Its not Legal. Number should be only 1 to 9. 0 for Empty. \n\n";
        return;
    }

    if(value == board[a-1][b-1]) {
        cout << value << " is already Present Here. \n\n";
        return;
    }

    if(value!=0 && !isValidBox(a-1,b-1, value))
    {
        cout << "Oops! " << value << " is already Present in the ";
        if(isPresentInRow(a-1, value))
            cout << "Row ";
        if(isPresentInCol(b-1, value))
            cout << "Column ";
        if(isPresentInBlock(a-1,b-1, value))
            cout << "Box ";
        
        cout << endl << endl;
        return;
    }            
    
    board[a-1][b-1] = value;
    Board();
}

bool isValidBox(int row, int col, int x)
{
    if(isPresentInRow(row, x))
        return false;
    else if(isPresentInCol(col, x))
        return false;
    else if(isPresentInBlock(row,col, x))
        return false;
    else
        return true;
}

bool isBuiltinBox(int row, int col)
{
    for(int r=0; r<rows; r++) {
        for(int c=0; c<cols; c++) {
            if(board[row][col] == 0)
                continue;
            else if(board[row][col] == builtin[r][c])
                return true;
        }
    }
    return false;
}


bool isPresentInRow(int row, int x)
{
    for(int c=0; c<cols; c++)
        if(board[row][c] == x)
            return true;
    
    return false;
}

bool isPresentInCol(int col, int x)
{
    for(int r=0; r<rows; r++)
        if(board[r][col] == x)
            return true;
    
    return false;
}

bool isPresentInBlock(int row, int col, int x)
{
    int i = row - row%3;
    int j = col - col%3;
    
    for(int r=i; r<i+3; r++) {
        for(int c=j; c<j+3; c++) {
            if(board[r][c] == x)
                return true;
        }
    }
    
    return false;
}


void SwapNums(int n1, int n2)
{
    for(int r=0; r<rows; r++) {
        for(int c=0; c<cols; c++) {
            if(board[r][c] == n1)
                board[r][c] = n2;
            else if(board[r][c] == n2)
                board[r][c] = n1;
        }
    }
}

void SwapRows(int r1, int r2)
{
    r1--, r2--;
    for(int c=0; c<cols; c++)
        SwapValues( board[r1][c],board[r2][c] );
}

void SwapRowBlocks(int r1, int r2)
{
    r1 = (r1-1)*3;
    r2 = (r2-1)*3;
    for(int r=1; r<=3; r++)
        SwapRows( r1+r, r2+r );
}

void SwapCols(int c1, int c2)
{
    c1--, c2--;
    for(int r=0; r<rows; r++)
        SwapValues( board[r][c1],board[r][c2] );
}

void SwapColBlocks(int c1, int c2)
{
    c1 = (c1-1)*3;
    c2 = (c2-1)*3;
    for(int c=1; c<=3; c++)
        SwapCols( c1+c, c2+c );
}

void SwapValues(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}
