#include <iostream>
#include <string.h>
using namespace std;

void Board();

int rows = 9, cols = 9;
int board[9][9] = {0};

int main()
{
    cout << endl;
    Board();

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
