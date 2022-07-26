#include <iostream>
#include <string.h>
#include<random>
#include<fstream>
using namespace std;

void Board();
void Input();
bool over();
void PlayAgain();
void SaveBoard(string);
void ReadBoard(string);

void InitializeBoard();
bool recursiveSolve(int,int);

bool isValidBox(int,int, int);
bool isBuiltinBox(int,int);
bool isPresentInRow(int,int);
bool isPresentInCol(int,int);
bool isPresentInBlock(int,int, int);

int rows = 9, cols = 9;
int board[9][9] = {0};
int solution[9][9] = {0};
int builtin[9][9] = {0};

bool quit = false;
char playAgain = 'Y'; //The Default PlayAgain Option
random_device Seed; //RandomValue Generator
uniform_int_distribution<int> randomNumber(1,9);

int main()
{
    cout << endl;
	cout << "Welcome to the Sudoku-Board-Game. A Logical-Puzzle Game. \n\n";
	
    do {
        InitializeBoard();
        Board();

        //Main Game
        while(true)
        {
            cout << "Select the Box (Row Col) on the Board: ";
            Input();
            Board();

            if(quit)
                break;

            if(over()) {
                cout << "\n\n Congratulations! You Won. The Whole Board is Completed. \n\n";
                break;
            }
        }
        
        PlayAgain();
    }
    while(playAgain == 'Y');
    
    cout << endl << endl;
    cout << "Thanks for Playing. Hope You Enjoyed the Game! \n";
    cout << "It would be very Kind of you, if you give us an Honest Feedback. \n\n";

    cout << "You can Find me in GitHub https://github.com/Haseebullah9012. \n";

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

    if(a==-9 && b==-9) {
        quit = true;
        cout << "\n\n You are Quiting the Game. \n\n";
        return;
    }
    else if(a==-8 && b==-8) {
        SaveBoard("Game");
        cout << "\n\n Your Sudoku Game is Saved. \n\n";
        return;
    }
    
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
}

bool over()
{
    for(int r=0; r<rows; r++)
        for(int c=0; c<cols; c++)
            if(board[r][c] == 0)
                return false;
    
    return true;
}


void InitializeBoard()
{
    char importBoard;
    cout << "Do You Want to Import Saved Sudoku Board (Y/N): ";
	cin >> importBoard;
	importBoard = toupper(importBoard);
	cin.ignore(255, '\n');

    if(importBoard == 'Y')
        ReadBoard
        ("Solution");
    else
        recursiveSolve(0,0); //Generate New Board

    //Copy the Filled Board as Solution
    for(int r=0; r<rows; r++)
        for(int c=0; c<cols; c++)
            solution[r][c] = board[r][c];
    SaveBoard("Solution");


    if(importBoard == 'Y')
        ReadBoard("Puzzle");
    else {
        for(int i=0, r,c; i<80; i++) {
            r = randomNumber(Seed) -1;
            c = randomNumber(Seed) -1;
            board[r][c] = 0; //Remove Values from Random Boxes (Max60-Avg42, Max80-Avg52)
        }
    }
    
    //Make The Builtin the Same as Board
    for(int r=0; r<rows; r++)
        for(int c=0; c<cols; c++)
            builtin[r][c] = board[r][c];
    SaveBoard("Puzzle");

    if(importBoard == 'Y')
        ReadBoard("Game");
}

bool recursiveSolve(int row,int col)
{
    //Next Row
    if(col>=cols) {
        col=0;
        row++;
        if(row>=rows)
            return true; //All Rows Filled
    }
    
    if(board[row][col] != 0)
        return recursiveSolve(row,col+1); //Skip Default Numbers

    int num = randomNumber(Seed);
    for(int i=0; i<10; i++,num++)
    {
        if(isValidBox(row,col, num)) {
            board[row][col] = num;
            if(recursiveSolve(row,col+1))
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
    if(!isPresentInRow(row, x) && !isPresentInCol(col, x) && !isPresentInBlock(row,col, x))
        return true;
    return false;
}

bool isBuiltinBox(int row, int col)
{
    if(board[row][col]!=0 && board[row][col]==builtin[row][col])
        return true;
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
    
    for(int r=i; r<i+3; r++)
        for(int c=j; c<j+3; c++)
            if(board[r][c] == x)
                return true;
    
    return false;
}


void PlayAgain()
{
	cout << "Do You Want to Play Again (Y/N): ";
	cin >> playAgain;
	playAgain = toupper(playAgain);
	cin.ignore(255, '\n');

    if(playAgain != 'Y' && playAgain != 'N') {
		cout << "   Oops! Its not a legal Response. \n\n";
		cout << "Again, ";
		PlayAgain();
	}
}


void SaveBoard(string name)
{
    ofstream file("Sudoku.txt", ios::out | ios::app);
    
    if(name=="Solution")
        file << "\n\n" << "\t -------- Solution ------- \n";
    else if(name=="Puzzle")
        file << "\t --------- Puzzle -------- \n";
    else if(name=="Game")
        file << "\t ---------- Game --------- \n";
    
    for(int r=0; r<rows; r++)
    {	
        if(r%3 == 0)
            file << "\t ------------------------- \n";
        
        file << "\t ";
		for(int c=0; c<cols; c++)
        {
            if(c%3 == 0)
                file << "| ";
            
            file << board[r][c] << " ";
        }
		file << "| \n";
	}
    file << "\t ------------------------- \n";
	
    file.close();
}

void ReadBoard(string name)
{
    ifstream file("Sudoku.txt");
    if(!file.is_open())
        return;
    
    string line;
    int skip = 1;
    if(name=="Puzzle")
        skip += 14;
    else if(name=="Game")
        skip += 2*14;

    for(int i=0; i<skip; i++)
        getline(file, line); //Skip to the Desired Board
    
    int r=0, c=0, num;
    while(!file.eof())
    {
        getline(file, line);
        for(int i=4; i<line.length(); i++)
        {
            num = line[i]-'0';
            if(num>=0 && num<=9)
            {
                board[r][c] = num;
                c++;

                if(c==cols) {
                    c=0;
                    r++;
                }
            }
        }
        
        if(r>=rows)
            break;
    }
    
    file.close();
}
