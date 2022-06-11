#include <iostream>
#include <string.h>
using namespace std;

void Board();
void Input();
bool isValidBox(int,int, int);

bool isPresentInRow(int,int);
bool isPresentInCol(int,int);
bool isPresentInBox(int,int, int);

int rows = 9, cols = 9;
int board[9][9] = {0};

int main()
{
    cout << endl;
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
            cout << board[r][c] << " ";
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
        if(isPresentInBox(a-1,b-1, value))
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
    else if(isPresentInBox(row,col, x))
        return false;
    else
        return true;
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

bool isPresentInBox(int row, int col, int x)
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
