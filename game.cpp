#include <iostream>
#include <string.h>
using namespace std;

void Board();
void Input();

void InitializeBoard();
bool RecursiveFillBox(int,int);

bool isValidBox(int,int, int);
bool isBuiltinBox(int,int);
bool isPresentInRow(int,int);
bool isPresentInCol(int,int);
bool isPresentInBlock(int,int, int);

int rows = 9, cols = 9;
int board[9][9] = {0};
int solution[9][9] = {0};
int builtin[9][9] = {0};

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


void InitializeBoard()
{
    RecursiveFillBox(0,0);

    //Copy the Filled Board as Solution
    for(int r=0; r<rows; r++)
        for(int c=0; c<cols; c++)
                solution[r][c] = board[r][c];
    
    //Remove Values from Random Boxes
    for(int r=0; r<rows; r++)
        for(int c=0; c<cols; c++)
            if(random()%20==0)
                board[r][c] = 0; //Remove with 1/2 Probability (50% Chance)
    
    //Make The Builtin the Same as Board
    for(int r=0; r<rows; r++)
        for(int c=0; c<cols; c++)
                builtin[r][c] = board[r][c];
}

bool RecursiveFillBox(int row,int col)
{
    //Next Row
    if(col>=cols) {
        col=0;
        row++;
        if(row>=rows)
            return true; //All Rows Filled
    }
    
    int num = random()%9 +1;
    for(int i=0; i<10; i++,num++)
    {
        if(isValidBox(row,col, num)) {
            board[row][col] = num;
            if(RecursiveFillBox(row,col+1))
                return true;
            else
                board[row][col] = 0;
        }
        
        if(num>=9)
            num=0;
    }

    return false;
}


bool isValidBox(int row, int col, int x)
{
    if(isPresentInRow(row, x) || isPresentInCol(col, x) || isPresentInBlock(row,col, x))
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
