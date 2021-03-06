#include<iostream>
#include<vector>
using namespace std;

void getNextEmpty(vector<vector<char>>& board, int &row, int &column)
{
    do
    {
        if(board[row][column] == '.')
            return;
        row = (column == 8) ? row + 1 : row;
        column = (column + 1) % 9;
    }while(row < 9);
}
void getAvailable(vector<vector<char>>& board, vector<bool> &avail, int row, int column)
{
    for(int i = 0; i < 9; i++)
    {
        if(board[row][i] != '.')
            avail[board[row][i] - '1'] = false;
        if(board[i][column] != '.')
            avail[board[i][column] - '1'] = false;
        int box_i = row / 3 * 3 + i / 3, box_j = column / 3 * 3 + i % 3;
        if(board[box_i][box_j] != '.')
            avail[board[box_i][box_j] - '1'] = false;
    }
}
bool solveSudokuRe(vector<vector<char>>& board, int row, int column)
{
    getNextEmpty(board, row, column);

    if(row == 9)
        return true;
    vector<bool> avail(9, true);
    getAvailable(board, avail, row, column);
    for(int i = 0; i < 9; i++)
    {
        if(!avail[i])
            continue;
        board[row][column] = i + '1';
        if(solveSudokuRe(board, row, column))
            return true;
    }
    board[row][column] = '.';
    return false;
}
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        solveSudokuRe(board, 0, 0);
    }
};

int main()
{
	vector<vector<char>> board{{'7', '3', '.', '2', '1', '8', '5', '.', '4'},
	{'2', '1', '.', '.', '.', '9', '.', '.', '3'},
	{'5', '9', '.', '.', '7', '.', '2', '8', '1'},
	{'3', '4', '1', '8', '6', '.', '9', '2', '7'},
	{'.', '6', '.', '.', '9', '.', '.', '1', '.'},
	{'9', '5', '2', '.', '4', '1', '8', '3', '6'},
	{'4', '7', '3', '.', '8', '.', '.', '5', '2'},
	{'6', '.', '.', '1', '.', '.', '.', '4', '9'},
	{'1', '.', '9', '5', '3', '4', '.', '6', '8'}};
	vector<vector<char>> board1{{'.', '.', '.', '.', '.', '.', '8', '.', '3'},
	{'7', '6', '4', '.', '5', '3', '9', '.', '.'},
	{'.', '5', '3', '9', '2', '.', '7', '6', '4'},
	{'5', '.', '.', '2', '3', '9', '.', '.', '7'},
	{'.', '.', '9', '.', '1', '.', '6', '.', '.'},
	{'4', '.', '.', '6', '8', '5', '.', '.', '2'},
	{'6', '9', '5', '.', '7', '2', '1', '4', '.'},
	{'.', '.', '2', '1', '9', '.', '5', '7', '6'},
	{'1', '.', '8', '.', '.', '.', '.', '.', '.'}};
	vector<vector<char>> board2{{'7', '3', '.', '2', '1', '8', '5', '.', '4'},
	{'2', '1', '.', '.', '.', '9', '.', '.', '3'},
	{'5', '9', '.', '.', '7', '.', '2', '8', '1'},
	{'3', '4', '1', '8', '6', '.', '9', '2', '7'},
	{'.', '6', '.', '.', '9', '.', '.', '1', '.'},
	{'9', '5', '2', '.', '4', '1', '8', '3', '6'},
	{'4', '7', '3', '.', '8', '.', '.', '5', '2'},
	{'6', '.', '.', '1', '.', '.', '.', '4', '9'},
	{'1', '.', '9', '5', '3', '4', '.', '6', '8'}};
	vector<vector<char>> board3{{'7', '3', '.', '2', '1', '8', '5', '.', '4'},
	{'2', '1', '.', '.', '.', '9', '.', '.', '3'},
	{'5', '9', '.', '.', '7', '.', '2', '8', '1'},
	{'3', '4', '1', '8', '6', '.', '9', '2', '7'},
	{'.', '6', '.', '.', '9', '.', '.', '1', '.'},
	{'9', '5', '2', '.', '4', '1', '8', '3', '6'},
	{'4', '7', '3', '.', '8', '.', '.', '5', '2'},
	{'6', '.', '.', '1', '.', '.', '.', '4', '9'},
	{'1', '.', '9', '5', '3', '4', '.', '6', '8'}};
	vector<vector<char>> board4{{'7', '3', '.', '2', '1', '8', '5', '.', '4'},
	{'2', '1', '.', '.', '.', '9', '.', '.', '3'},
	{'5', '9', '.', '.', '7', '.', '2', '8', '1'},
	{'3', '4', '1', '8', '6', '.', '9', '2', '7'},
	{'.', '6', '.', '.', '9', '.', '.', '1', '.'},
	{'9', '5', '2', '.', '4', '1', '8', '3', '6'},
	{'4', '7', '3', '.', '8', '.', '.', '5', '2'},
	{'6', '.', '.', '1', '.', '.', '.', '4', '9'},
	{'1', '.', '9', '5', '3', '4', '.', '6', '8'}};
	Solution().solveSudoku(board1);
	for(int i = 0; i < board.size(); i++)
	{
		for(int j = 0; j < board[0].size(); j++)
		{
			cout<<board[i][j]<<"    ";
		}
		cout<<endl;
	}
	return 0;
}
