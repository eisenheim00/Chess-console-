
#include "pch.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <windows.h>
using namespace std;
bool ischeckmate = false, isstalemate = false;

int w_kills = 0, b_kills = 0;
int wpieces = 0, bpieces = 0;
bool w_check = false, b_check = false;

void Pawn_promotion(char board[][8], int prow, int pcol, int nrow, int ncol)
{
	char pro;
	if (board[prow][pcol] == 'p')
	{
		if (prow == 1 && nrow == 0)
		{
			cout << "\n'PAWN PROMOTION'\nType 'q' for QUEEN\nType 'b' for BISHOP\nType 'r' for ROOK\nType 'n' for KNIGHT\n";
			cin >> pro;
			switch (pro)
			{
			case 'q':
				board[prow][pcol] = 'q';
				break;
			case 'b':
				board[prow][pcol] = 'b';
				break;
			case 'r':
				board[prow][pcol] = 'r';
				break;
			case 'n':
				board[prow][pcol] = 'n';
				break;
			}
		}
	}
	else if (board[prow][pcol] == 'P')
	{
		if (prow == 6 && nrow == 7)
		{
			cout << "\n'PAWN PROMOTION'\nType 'q' for QUEEN\nType 'b' for BISHOP\nType 'r' for ROOK\nType 'n' for KNIGHT\n";
			cin >> pro;
			switch (pro)
			{
			case 'q':
				board[prow][pcol] = 'Q';
				break;
			case 'b':
				board[prow][pcol] = 'B';
				break;
			case 'r':
				board[prow][pcol] = 'R';
				break;
			case 'n':
				board[prow][pcol] = 'N';
				break;
			}
		}
	}
}

bool em_passant(char board[][8], int prow, int pcol, int nrow, int ncol)
{
	if (board[prow][pcol] == 'p')
	{
		if (prow - 1 == nrow && pcol - 1 == ncol)
		{
			if (board[nrow][ncol] == ' ')
			{
				if (board[prow][ncol] > 'A' && board[prow][ncol] < 'Z')
				{
					b_kills++;
					return true;
				}
			}
		}
		else if (prow - 1 == nrow && pcol + 1 == ncol)
		{
			if (board[nrow][ncol] == ' ')
			{
				if (board[prow][ncol] > 'A' && board[prow][ncol] < 'Z')
				{
					b_kills++;
					return true;
				}
			}
		}
	}
	else if (board[prow][pcol] == 'P')
	{
		if (prow + 1 == nrow && pcol - 1 == ncol)
		{
			if (board[nrow][ncol] == ' ')
			{
				if (board[prow][ncol] > 'a' && board[prow][ncol] < 'z')
				{
					w_kills++;
					return true;
				}
			}
		}
		else if (prow + 1 == nrow && pcol + 1 == ncol)
		{
			if (board[nrow][ncol] == ' ')
			{
				if (board[prow][ncol] > 'a' && board[prow][ncol] < 'z')
				{
					w_kills++;
					return true;
				}
			}
		}
	}
	return false;
}

bool castling(char board[][8], int prow, int pcol, int nrow, int ncol)
{
	if (prow - nrow == 0)
	{
		if (prow == 0 && pcol == 0)
		{
			if (ncol == 3 && board[prow][4]=='K')
				return true;
		}
		else if (prow == 0 && pcol == 7)
		{
			if (ncol == 5 && board[prow][4]=='K')
				return true;
		}
		else if (prow == 7 && pcol == 0)
		{
			if (ncol == 3 && board[prow][4]=='k')
				return true;
		}
		else if (prow == 7 && pcol == 7)
		{
			if (ncol == 5 && board[prow][4] == 'k')
				return true;
		}
	}
	return false;
}

void initboard(char newB[8][8], char Board[8][8])
{
	char gameType;
	cout << "Press N for new game.\nPress L to load saved game\n";
	cin >> gameType;
	while (gameType != 'n' && gameType != 'N' && gameType != 'l' && gameType != 'L')
	{
		cout << "Wrong Input.\n";
		cin >> gameType;
	}
	if (gameType == 'n' || gameType == 'N')
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				Board[i][j] = newB[i][j];
			}
		}
	}
	else
	{
		ifstream fin("C:\\Users\\TOSHIBA\\Documents\\chesssaved.txt");
		char buff[500];
		int i = 0, k = 0;
		while (fin.getline(buff, 500) && i < 8)
		{
			k = 0;
			for (int j = 0; j < 8; j++)
			{
				Board[i][j] = buff[k++];
			}
			i++;
		}
	}
}

bool validPlayer(bool turn, int prow, int pcol, char board[][8])
{
	if (turn == 1)
	{
		if (board[prow][pcol] > 'a' && board[prow][pcol] < 'z')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (board[prow][pcol] > 'A' && board[prow][pcol] < 'Z')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool validPawnMove(char board[][8], int prow, int pcol, int nrow, int ncol)
{
	if (!em_passant(board, prow, pcol, nrow, ncol))
	{
		if (board[prow][pcol] == 'p')
		{
			if (prow == 6)
			{
				if ((prow - nrow) == 1 || (prow - nrow) == 2)
				{
					if ((pcol - ncol) == 0)
					{
						return true;
					}
					else if ((pcol - ncol) == 1 || (pcol - ncol) == -1)
					{
						if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
						{
							w_kills++;
							return true;
						}
						else if (board[nrow][ncol] == ' ')
						{
							return false;
						}
					}
					
				}
				else
				{
					return false;
				}
			}
			else
			{
				if ((prow - nrow) == 1)
				{
					if ((pcol - ncol) == 0)
					{
						return true;
					}
					else if ((pcol - ncol) == 1 || (pcol - ncol) == -1)
					{
						if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
						{
							w_kills++;
							return true;
						}
						else if (board[nrow][ncol] == ' ')
						{
							return false;
						}
					}
				}
				else
				{
					return false;
				}

			}
		}
		else if (board[prow][pcol] == 'P')
		{
			if (prow == 1)
			{
				if ((prow - nrow) == -1 || (prow - nrow) == -2)
				{
					if ((pcol - ncol) == 0)
					{
						return true;
					}
					else if ((pcol - ncol) == 1 || (pcol - ncol) == -1)
					{
						if (board[nrow][ncol] > 'a' && board[nrow][ncol] < 'z')
						{
							b_kills++;
							return true;
						}
						else if (board[nrow][ncol] == ' ')
						{
							return false;
						}
					}
					else return false;
				}
				else
				{
					return false;
				}
			}
			else
			{
				if ((prow - nrow) == -1)
				{
					if ((pcol - ncol) == 0)
					{
						return true;
					}
					else if ((pcol - ncol) == 1 || (pcol - ncol) == -1)
					{
						if (board[nrow][ncol] > 'a' && board[nrow][ncol] < 'z')
						{
							b_kills++;

							return true;
						}
						else  if (board[nrow][ncol] == ' ')
						{
							return false;
						}
					}
					else return false;
				}
				else
				{
					return false;
				}
			}
		}

	}
}

bool validKnightMove(char board[][8], int prow, int pcol, int nrow, int ncol, bool turn)
{
	if (turn)
	{
		if ((prow - nrow) == 2 || (prow - nrow) == -2)
		{
			if ((pcol - ncol) == 1 || (pcol - ncol) == -1)
			{
				if (board[nrow][ncol] == ' ')
				{
					return true;
				}
				else if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
				{
					w_kills++;
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		else if ((prow - nrow) == 1 || (prow - nrow) == -1)
		{
			if ((pcol - ncol) == -2 || (pcol - ncol) == 2)
			{
				if (board[nrow][ncol] == ' ')
				{
					return true;
				}
				else if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
				{
					w_kills++;
					return true;
				}
				else
				{
					return false;
				}
			}
			else
				return false;
		}
		else return false;
	}
	else if (!turn)
	{
		if ((prow - nrow) == 2 || (prow - nrow) == -2)
		{
			if ((pcol - ncol) == 1 || (pcol - ncol) == -1)
			{
				if (board[nrow][ncol] == ' ')
				{
					return true;
				}
				else if (board[nrow][ncol] >= 'a' && board[nrow][ncol] <= 'z')
				{
					b_kills++;
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		else if ((prow - nrow) == 1 || (prow - nrow) == -1)
		{
			if ((pcol - ncol) == 2 || (pcol - ncol) == -2)
			{
				if (board[nrow][ncol] == ' ')
				{
					return true;
				}
				else if (board[nrow][ncol] >= 'a' && board[nrow][ncol] <= 'z')
				{
					b_kills++;
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		else return false;
	}
}

bool validRookMove(char board[][8], int prow, int pcol, int nrow, int ncol, bool turn)
{
	if (turn)
	{
		if ((ncol - pcol) == 0)
		{
			if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
			{
				w_kills++;
			}
			else if (board[nrow][ncol] > 'a' && board[nrow][ncol] < 'z')
			{
				return false;
			}
			return true;
		}
		else if ((nrow - prow) == 0)
		{
			if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
			{
				w_kills++;
			}
			else if (board[nrow][ncol] > 'a' && board[nrow][ncol] < 'z')
			{
				return false;
			}
			return true;
		}
		else return false;
	}
	else if (!turn)
	{
		if ((ncol - pcol) == 0)
		{
			if (board[nrow][ncol] > 'a' && board[nrow][ncol] < 'z')
			{
				w_kills++;
			}
			else if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
			{
				return false;
			}
			return true;
		}
		else if ((nrow - prow) == 0)
		{
			if (board[nrow][ncol] > 'a' && board[nrow][ncol] < 'z')
			{
				w_kills++;
			}
			else if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
			{
				return false;
			}
			return true;
		}
		else return false;
	}
}

bool validBishopMove(char board[][8], int prow, int pcol, int nrow, int ncol, bool turn)
{
	bool flag = false;
	if (turn)
	{

		if (nrow > prow && ncol > pcol)
		{
			if ((nrow - prow) == (ncol - pcol))
			{
				flag = true;
			}
		}
		else if (nrow < prow && ncol < pcol)
		{
			if ((ncol - pcol) == (nrow - prow))
			{
				flag = true;
			}
		}
		else if (prow > nrow && ncol > pcol)
		{
			if ((prow - nrow) == (ncol - pcol))
			{
				flag = true;
			}
		}
		else if (prow < nrow && ncol < pcol)
		{
			if ((prow - nrow) == (ncol - pcol))
			{
				flag = true;
			}
		}
	}
	else if (!turn)
	{
		if (nrow > prow && ncol > pcol)
		{
			if ((nrow - prow) == (ncol - pcol))
			{
				flag = true;
			}
		}
		else if (nrow < prow && ncol < pcol)
		{
			if ((ncol - pcol) == (nrow - prow))
			{
				flag = true;
			}
		}
		else if (prow > nrow && ncol > pcol)
		{
			if ((prow - nrow) == (ncol - pcol))
			{
				flag = true;
			}
		}
		else if (prow < nrow && ncol < pcol)
		{
			if ((prow - nrow) == (ncol - pcol))
			{
				flag = true;
			}
		}
	}
	if (flag == true)
	{
		if (turn)
		{
			if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
			{
				w_kills++;
			}
			else if (board[nrow][ncol] > 'a' && board[nrow][ncol] < 'z')
			{
				flag = false;
			}
		}
		else
		{
			if (board[nrow][ncol] > 'a' && board[nrow][ncol] < 'z')
			{
				b_kills++;
			}
			else if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
			{
				flag = false;
			}
		}
	}
	return flag;
}

bool validKingMove(char board[][8], int prow, int pcol, int nrow, int ncol, bool turn)
{
	int m = nrow - prow;
	int n = ncol - pcol;
	bool flag = false;
	if (m == 0 && n == 1)
	{
		flag = true;
	}
	else if (m == 1 && n == 0)
	{
		flag = true;
	}
	else if (m == 1 && n == 1)
	{
		flag = true;
	}
	else if (m == -1 && n == 0)
	{
		flag = true;
	}
	else if (m == 0 && n == -1)
	{
		flag = true;
	}
	else if (m == -1 && n == -1)
	{
		flag = true;
	}
	else if (m == 1 && n == -1)
	{
		flag = true;
	}
	else if (m == -1 && n == 1)
	{
		flag = true;
	}
	if (turn)
	{
		if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
			w_kills++;
		else if (board[nrow][ncol] > 'a' && board[nrow][ncol] < 'z')
			flag = false;
	}
	else if (!turn)
	{
		if (board[nrow][ncol] > 'z' && board[nrow][ncol] < 'z')
			b_kills++;
		else if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
			flag = false;
	}
	return flag;
}

bool validQueenMove(char board[][8], int prow, int pcol, int nrow, int ncol, bool turn)
{
	if (turn)
	{
		if ((ncol - pcol) == 0)
		{
			if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
			{
				w_kills++;
			}
			else if (board[nrow][ncol] > 'a' && board[nrow][ncol] < 'z')
			{
				return false;
			}
			return true;
		}
		else if ((nrow - prow) == 0)
		{
			if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
			{
				w_kills++;
			}
			else if (board[nrow][ncol] > 'a' && board[nrow][ncol] < 'z')
			{
				return false;
			}
			return true;
		}
		else if (nrow > prow && ncol > pcol)
		{
			if ((nrow - prow) == (ncol - pcol))
			{
				if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
				{
					w_kills++;
				}
				else if (board[nrow][ncol] > 'a' && board[nrow][ncol] < 'z')
				{
					return false;
				}
				return true;
			}
		}
		else if (nrow < prow && ncol < pcol)
		{
			if ((ncol - pcol) == (nrow - prow))
			{
				if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
				{
					w_kills++;
				}
				else if (board[nrow][ncol] > 'a' && board[nrow][ncol] < 'z')
				{
					return false;
				}
				return true;
			}
		}
		else if (prow > nrow && ncol > pcol)
		{
			if ((prow - nrow) == (ncol - pcol))
			{
				if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
				{
					w_kills++;
				}
				else if (board[nrow][ncol] > 'a' && board[nrow][ncol] < 'z')
				{
					return false;
				}
				return true;
			}
		}
		else if (prow < nrow && ncol < pcol)
		{
			if ((prow - nrow) == (ncol - pcol))
			{
				if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
				{
					w_kills++;
				}
				else if (board[nrow][ncol] > 'a' && board[nrow][ncol] < 'z')
				{
					return false;
				}
				return true;
			}
		}
		else return false;
	}
	else if (!turn)
	{
		if ((ncol - pcol) == 0)
		{
			if (board[nrow][ncol] > 'a' && board[nrow][ncol] < 'z')
			{
				b_kills++;
			}
			else if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
			{
				return false;
			}
			return true;
		}
		else if ((nrow - prow) == 0)
		{
			if (board[nrow][ncol] > 'a' && board[nrow][ncol] < 'z')
			{
				b_kills++;
			}
			else if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
			{
				return false;
			}
			return true;
		}
		else if (nrow > prow && ncol > pcol)
		{
			if ((nrow - prow) == (ncol - pcol))
			{
				if (board[nrow][ncol] > 'a' && board[nrow][ncol] < 'z')
				{
					b_kills++;
				}
				else if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
				{
					return false;
				}
				return true;
			}
		}
		else if (nrow < prow && ncol < pcol)
		{
			if ((ncol - pcol) == (nrow - prow))
			{
				if (board[nrow][ncol] > 'a' && board[nrow][ncol] < 'z')
				{
					b_kills++;
				}
				else if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
				{
					return false;
				}
				return true;
			}
		}
		else if (prow > nrow && ncol > pcol)
		{
			if ((prow - nrow) == (ncol - pcol))
			{
				if (board[nrow][ncol] > 'a' && board[nrow][ncol] < 'z')
				{
					b_kills++;
				}
				else if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
				{
					return false;
				}
				return true;
			}
		}
		else if (prow < nrow && ncol < pcol)
		{
			if ((prow - nrow) == (ncol - pcol))
			{
				if (board[nrow][ncol] > 'a' && board[nrow][ncol] < 'z')
				{
					b_kills++;
				}
				else if (board[nrow][ncol] > 'A' && board[nrow][ncol] < 'Z')
				{
					return false;
				}
				return true;
			}
		}
		else return false;
	}
}

bool isWayClear(char board[][8], int prow, int pcol, int nrow, int ncol)
{
	if (board[nrow][ncol] == 'n' || board[nrow][ncol] == 'N')
	{
		return true;
	}
	else
	{
		if (board[prow][pcol] == 'p' || board[prow][pcol] == 'P')
		{
			if (!em_passant(board, prow, pcol, nrow, ncol))
			{
				if (prow == 1 && pcol == ncol)
				{
					if (nrow == 2)
					{
						if (board[nrow][ncol] == ' ')
							return true;
					}
					else if (nrow == 3)
					{
						if (board[nrow][ncol] == ' ' && board[2][ncol] == ' ')
							return true;
					}
					else return false;
				}
				else if (prow == 6 && pcol == ncol)
				{
					if (nrow == 5)
					{
						if (board[nrow][ncol] == ' ')
							return true;
					}
					else if (nrow == 4)
					{
						if (board[nrow][ncol] == ' ' && board[5][ncol] == ' ')
							return true;
					}
					else return false;
				}
				else if ((prow + 1) == nrow && pcol == ncol)
				{
					if (board[nrow][ncol] == ' ')
						return true;
				}
				else if ((prow - 1) == nrow && pcol == ncol)
				{
					if (board[nrow][ncol] == ' ')
						return true;
				}
				else if (prow - 1 == nrow && pcol - 1 == ncol )
				{
					if ((board[nrow][ncol] > 'A' && board[prow][pcol] < 'Z') || (board[nrow][ncol] > 'a' && board[prow][pcol] < 'a'))
						return true;
				}
				else if (prow - 1 == nrow && pcol + 1 == nrow)
				{
					if ((board[nrow][ncol] > 'A' && board[prow][pcol] < 'Z') || (board[nrow][ncol] > 'a' && board[prow][pcol] < 'a'))
						return true;
				}
				else if ((prow + 1) == nrow && pcol - 1 == nrow )
				{
					if ((board[nrow][ncol] > 'A' && board[prow][pcol] < 'Z') || (board[nrow][ncol] > 'a' && board[prow][pcol] < 'a'))
						return true;
				}
				else if ((prow + 1) == nrow && pcol + 1 == nrow)
				{
					if ((board[nrow][ncol] > 'A' && board[prow][pcol] < 'Z') || (board[nrow][ncol] > 'a' && board[prow][pcol] < 'a'))
						return true;
				}
				else return false;
			}
		}
		else if (board[prow][pcol] == 'r' || board[prow][pcol] == 'R')
		{
			if ((ncol - pcol) == 0)
			{
				if (nrow > prow)
				{
					int temp_r = prow+1;
					while (temp_r < nrow)
					{
						
						if (board[temp_r][ncol] != ' ')
							return false;
						temp_r++;
					}
				}
				else if (prow > nrow)
				{
					int temp_r = prow-1;
					while (temp_r > nrow)
					{
						
						if (board[temp_r][ncol] != ' ')
							return false;
						temp_r--;
					}
				}
			}
			else if ((nrow - prow) == 0)
			{
				if (ncol > pcol)
				{
					int temp_c = pcol+1;
					while (temp_c < ncol)
					{
						
						if (board[nrow][temp_c] != ' ')
							return false;
						temp_c++;
					}
				}
				else if (pcol > ncol)
				{
					int temp_c = pcol-1;
					while (temp_c > ncol)
					{
						
						if (board[nrow][temp_c] != ' ')
							return false;
						temp_c--;
					}
				}
			}
		}
		else if (board[prow][pcol] == 'b' || board[prow][pcol] == 'B')
		{
			int m = nrow - prow;
			int n = ncol - pcol;
			if (m > 0 && n > 0)
			{
				int temp_r = prow+1;
				int temp_c = pcol+1;
				while (temp_c < ncol &&  temp_r < nrow)
				{
					
					if (board[temp_r][temp_c] != ' ')
						return false;
					temp_r++;
					temp_c++;
				}
			}
			else if (m < 0 && n < 0)
			{
				int temp_r = prow-1;
				int temp_c = pcol-1;
				while (temp_c >= ncol && temp_r >= nrow)
				{
					
					if (board[temp_r][temp_c] != ' ')
						return false;
					temp_r--;
					temp_c--;
				}
			}
			else if (m < 0 && n > 0)
			{
				int temp_r = prow-1;
				int temp_c = pcol+1;
				while (temp_r > nrow && temp_c < ncol)
				{
					
					if (board[temp_r][temp_c] != ' ')
						return false;
					temp_r--;
					temp_c++;
				}
			}
			else if (m > 0 && n < 0)
			{
				int temp_r = prow+1;
				int temp_c = pcol-1;
				while (temp_r<nrow && temp_c>ncol)
				{
					
					if (board[temp_r][temp_c] != ' ')
						return false;
					temp_r++;
					temp_c--;
				}
			}
		}
		else if (board[prow][pcol] == 'q' || board[prow][pcol] == 'Q')
		{
			int m = nrow - prow;
			int n = ncol - pcol;
			if ((ncol - pcol) == 0)
			{
				if (nrow > prow)
				{
					int temp_r = prow+1;
					while (temp_r <= nrow)
					{
						
						if (board[temp_r][ncol] != ' ')
							return false;
						temp_r++;
					}
				}
				else if (prow > nrow)
				{
					int temp_r = prow-1;
					while (temp_r > nrow)
					{
						
						if (board[temp_r][ncol] != ' ')
							return false;
						temp_r--;
					}
				}
			}
			else if ((nrow - prow) == 0)
			{
				if (ncol > pcol)
				{
					int temp_c = pcol+1;
					while (temp_c < ncol)
					{
						
						if (board[nrow][temp_c] != ' ')
							return false;
						temp_c++;
					}
				}
				else if (pcol > ncol)
				{
					int temp_c = pcol-1;
					while (temp_c > ncol)
					{
						
						if (board[nrow][temp_c] != ' ')
							return false;
						temp_c--;
					}
				}
			}
			else if (m > 0 && n > 0)
			{
				int temp_r = prow+1;
				int temp_c = pcol+1;
				while (temp_c < ncol && temp_r < nrow)
				{
					
					if (board[temp_r][temp_c] != ' ')
						return false;
					temp_r++;
					temp_c++;
				}
			}
			else if (m < 0 && n < 0)
			{
				int temp_r = prow-1;
				int temp_c = pcol-1;
				while (temp_c > ncol && temp_r > nrow)
				{
					
					if (board[temp_r][temp_c] != ' ')
						return false;
					temp_r--;
					temp_c--;
				}
			}
			else if (m < 0 && n > 0)
			{
				int temp_r = prow-1;
				int temp_c = pcol+1;
				while (temp_r > nrow && temp_c < ncol)
				{
					
					if (board[temp_r][temp_c] != ' ')
						return false;
					temp_r--;
					temp_c++;
				}
			}
			else if (m > 0 && n < 0)
			{
				int temp_r = prow+1;
				int temp_c = pcol-1;
				while (temp_r <nrow && temp_c>ncol)
				{
					
					if (board[temp_r][temp_c] != ' ')
						return false;
					temp_r++;
					temp_c--;
				}
			}
		}

	}
	return true;
}

bool isCheck(char board[][8], int nrow, int ncol,bool& w_check, bool& b_check, bool turn)
{
	w_check = false; b_check = false;
	
	if (board[nrow][ncol] == 'n')
	{
		if (board[nrow + 2][ncol + 1] == 'K')
		{
			b_check = true;
			return true;
		}
		else if (board[nrow + 1][ncol + 2] == 'K')
		{
			b_check = true;
			return true;
		}
		else if (board[nrow - 2][ncol - 1] == 'K')
		{
			b_check = true;
			return true;
		}
		else if (board[nrow - 1][ncol - 2] == 'K')
		{
			b_check = true;
			return true;
		}
		else if (board[nrow + 2][ncol - 1] == 'K')
		{
			b_check = true;
			return true;
		}
		else if (board[nrow - 2][ncol + 1] == 'K')
		{
			b_check = true;
			return true;
		}
		else if (board[nrow - 1][ncol + 2] == 'K')
		{
			b_check = true;
			return true;
		}
		else if (board[nrow + 1][ncol - 2] == 'K')
		{
			b_check = true;
			return true;
		}
		//else return false;
	}
	else if (board[nrow][ncol] == 'N')
	{
		if (board[nrow + 2][ncol + 1] == 'k')
		{
			w_check = true;
			return true;
		}
		else if (board[nrow + 1][ncol + 2] == 'k')
		{
			w_check = true;
			return true;
		}
		else if (board[nrow - 2][ncol - 1] == 'k')
		{
			w_check = true;
			return true;
		}
		else if (board[nrow - 1][ncol - 2] == 'k')
		{
			w_check = true;
			return true;
		}
		else if (board[nrow + 2][ncol - 1] == 'k')
		{
			w_check = true;
			return true;
		}
		else if (board[nrow - 2][ncol + 1] == 'k')
		{
			w_check = true;
			return true;
		}
		else if (board[nrow - 1][ncol + 2] == 'k')
		{
			w_check = true;
			return true;
		}
		else if (board[nrow + 1][ncol - 2] == 'k')
		{
			w_check = true;
			return true;
		}
		//else return false;
	}
	if (board[nrow][ncol] == 'p' || board[nrow][ncol] == 'P')
	{
		if (board[nrow][ncol] == 'p')
		{
			if (board[nrow - 1][ncol+1] == 'K'|| board[nrow - 1][ncol -1 ] == 'K')
			{
				b_check = true;
				return true;
			}
		}
		else if (board[nrow][ncol] == 'P')
		{
			if (board[nrow + 1][ncol+1] == 'k'|| board[nrow + 1][ncol -1 ] == 'k')
			{
				w_check = true;
				return true;
			}
		}

	}
	if (board[nrow][ncol] == 'r' || board[nrow][ncol] == 'R')
	{
		if (turn)
		{
			
				int k = nrow-1;
				while (k >= 0)
				{
					if (board[k][ncol] == ' ')
						k--;
					else if (board[k][ncol] == 'K')
					{
						b_check = true;
						return true;
					}
					else break;
				}k = nrow+1;
				while (k <= 8)
				{
					if (board[k][ncol] == ' ')
						k++;
					else if (board[k][ncol] == 'K')
					{
						b_check = true;
						return true;
					}
					else break;
				}
			
				 k = ncol-1;
				while (k >= 0)
				{
					if (board[nrow][k] == ' ')
						k--;
					else if (board[nrow][k] == 'K')
					{
						b_check = true;
						return true;
					}
					else break;
				}k = ncol+1;
				while (k <= 8)
				{
					if (board[nrow][k] == ' ')
						k++;
					else if (board[nrow][k] == 'K')
					{
						b_check = true;
						return true;
					}
					else break;
				}
			
		}
		else
		{
			
				int k = nrow-1;
				while (k >= 0)
				{
					if (board[k][ncol] == ' ')
						k--;
					else if (board[k][ncol] == 'k')
					{
						w_check = true;
						return true;
					}
					else break;
				}k = nrow+1;
				while (k <= 8)
				{
					if (board[k][ncol] == ' ')
						k++;
					else if (board[k][ncol] == 'k')
					{
						w_check = true;
						return true;
					}
					else break;
				}
			
				 k = ncol-1;
				while (k >= 0)
				{
					if (board[nrow][k] == ' ')
						k--;
					else if (board[nrow][k] == 'k')
					{
						w_check = true;
						return true;
					}
					else break;
				}k = ncol+1;
				while (k <= 8)
				{
					if (board[nrow][k] == ' ')
						k++;
					else if (board[nrow][k] == 'k')
					{
						w_check = true;
						return true;
					}
					else break;
				}
			
		}
	}
	if (board[nrow][ncol] == 'b' || board[nrow][ncol] == 'B')
	{
		if (turn)
		{
			
				for (int i = nrow+1, j = ncol+1; i <= 8 && j <= 8; i++, j++)
				{
					if (board[i][j] == 'K')
					{
						b_check = true;
						return true;
					}
				}
				for (int i = nrow-1, j = ncol-1; i >= 0 && j >= 0; i--, j--)
				{
					if (board[i][j] == 'K')
					{
						b_check = true;
						return true;
					}
				}
			
				for (int i = nrow-1, j = ncol+1; i >= 0 && j <= 8; i--, j++)
				{
					if (board[i][j] == 'K')
					{
						b_check = true;
						return true;
					}
				}
				for (int i = nrow+1, j = ncol-1; i <= 8 && j >= 0; i++, j--)
				{
					if (board[i][j] == 'K')
					{
						b_check = true;
						return true;
					}
				}
			
		}
		else
		{
			
				for (int i = nrow+1, j = ncol+1; i <= 8 && j <= 8; i++, j++)
				{
					if (board[i][j] == 'k')
					{
						w_check = true;
						return true;
					}
				}
				for (int i = nrow-1, j = ncol-1; i >= 0 && j >= 0; i--, j--)
				{
					if (board[i][j] == 'k')
					{
						w_check = true;
						return true;
					}
				}
			
				for (int i = nrow-1, j = ncol+1; i >= 0 && j <= 8; i--, j++)
				{
					if (board[i][j] == 'k')
					{
						w_check = true;
						return true;
					}
				}
				for (int i = nrow+1, j = ncol-1; i <= 8 && j >= 0; i++, j--)
				{
					if (board[i][j] == 'k')
					{
						w_check = true;
						return true;
					}
				}
			
		}
	}
	if (board[nrow][ncol] == 'Q' || board[nrow][ncol] == 'q')
	{
		
		if (turn)
		{
			
				for (int i = nrow+1, j = ncol+1; i <= 8 && j <= 8; i++, j++)
				{
					if (board[i][j] == 'K')
					{
						b_check = true;
						return true;
					}
					else if (board[i][j] != ' ')
						break;
				}
				for (int i = nrow-1, j = ncol-1; i >= 0 && j >= 0; i--, j--)
				{
					if (board[i][j] == 'K')
					{
						b_check = true;
						return true;
					}
					else if (board[i][j] != ' ')
						break;
				}
			
				for (int i = nrow-1, j = ncol+1; i >= 0 && j <= 8; i--, j++)
				{
					if (board[i][j] == 'K')
					{
						b_check = true;
						return true;
					}
					else if (board[i][j] != ' ')
						break;
				}
				for (int i = nrow+1, j = ncol-1; i <= 8 && j >= 0; i++, j--)
				{
					if (board[i][j] == 'K')
					{
						b_check = true;
						return true;
					}
					else if (board[i][j] != ' ')
						break;
				}
			
				int k = nrow-1;
				while (k >= 0)
				{
					if (board[k][ncol] == ' ')
						k--;
					else if (board[k][ncol] == 'K')
					{
						b_check = true;
						return true;
					}
					else break;
				}k = nrow+1;
				while (k <= 8)
				{
					if (board[k][ncol] == ' ')
						k++;
					else if (board[k][ncol] == 'K')
					{
						b_check = true;
						return true;
					}
					else break;
				}
			
				 k = ncol-1;
				while (k >= 0)
				{
					if (board[nrow][k] == ' ')
						k--;
					else if (board[nrow][k] == 'K')
					{
						b_check = true;
						return true;
					}
					else break;
				}k = ncol+1;
				while (k <= 8)
				{
					if (board[nrow][k] == ' ')
						k++;
					else if (board[nrow][k] == 'K')
					{
						b_check = true;
						return true;
					}
					else break;
				}
			
		}
		else
		{
			
				for (int i = nrow+1, j = ncol+1; i <= 8 && j <= 8; i++, j++)
				{
					if (board[i][j] == 'k')
					{
						w_check = true;
						return true;
					}
					else if (board[i][j] != ' ')
						break;
				}
				for (int i = nrow-1, j = ncol-1; i >= 0 && j >= 0; i--, j--)
				{
					if (board[i][j] == 'k')
					{
						w_check = true;
						return true;
					}
					else if (board[i][j] != ' ')
						break;
				}
			
				for (int i = nrow-1, j = ncol+1; i >= 0 && j <= 8; i--, j++)
				{
					if (board[i][j] == 'k')
					{
						w_check = true;
						return true;
					}
					else if (board[i][j] != ' ')
						break;
				}
				for (int i = nrow+1, j = ncol-1; i <= 8 && j >= 0; i++, j--)
				{
					if (board[i][j] == 'k')
					{
						w_check = true;
						return true;
					}
					else if (board[i][j] != ' ')
						break;
				}
			
				int k = nrow-1;
				while (k >= 0)
				{
					if (board[k][ncol] == ' ')
						k--;
					else if (board[k][ncol] == 'k')
					{
						w_check = true;
						return true;
					}
					else break;
				}k = nrow+1;
				while (k <= 8)
				{
					if (board[k][ncol] == ' ')
						k++;
					else if (board[k][ncol] == 'k')
					{
						w_check = true;
						return true;
					}
					else break;
				}
			
				k = ncol-1;
				while (k >= 0)
				{
					if (board[nrow][k] == ' ')
						k--;
					else if (board[nrow][k] == 'k')
					{
						w_check = true;
						return true;
					}
					else break;
				}k = ncol+1;
				while (k <= 8)
				{
					if (board[nrow][k] == ' ')
						k++;
					else if (board[nrow][k] == 'k')
					{
						w_check = true;
						return true;
					}
					else break;
				}return false;

		}
	
     }

	
	return false;
}

bool checkmate(char board[][8])
{
	int w_pos_x, w_pos_y , wcount=0,bcount=0;
	int b_pos_x, b_pos_y;
	bool twcheck = false , tbcheck = false;
	char tboard[8][8];
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			tboard[i][j] = board[i][j];
			if (board[i][j] == 'k')
			{
				w_pos_x = i;
				w_pos_y = j;
			}
			if (board[i][j] == 'K')
			{
				b_pos_x = i;
				b_pos_y = j;
			}
		}
	}
	if (w_check)
	{
		tboard[w_pos_x][w_pos_y] = ' ';
		if (tboard[w_pos_x+1][w_pos_y]==' ' )
		{
			tboard[w_pos_x + 1][w_pos_y] = 'k';
		}
		else if ( tboard[w_pos_x + 1][w_pos_y] > 'a' && tboard[w_pos_x + 1][w_pos_y] < 'z')
		{
			wcount++;
		}
		if (tboard[w_pos_x - 1][w_pos_y] == ' ')
		{
			tboard[w_pos_x - 1][w_pos_y] = 'k';
		}
		else if (tboard[w_pos_x - 1][w_pos_y] > 'a' && tboard[w_pos_x - 1][w_pos_y] < 'z')
		{
			wcount++;
		}
		if (tboard[w_pos_x][w_pos_y+1] == ' ')
		{
			tboard[w_pos_x][w_pos_y+1] = 'k';
		}
		else if (tboard[w_pos_x][w_pos_y+1] > 'a' && tboard[w_pos_x][w_pos_y+1] < 'z')
		{
			wcount++;
		}
		if (tboard[w_pos_x][w_pos_y - 1] == ' ')
		{
			tboard[w_pos_x][w_pos_y - 1] = 'k';
		}
		else if (tboard[w_pos_x][w_pos_y - 1] > 'a' && tboard[w_pos_x][w_pos_y - 1] < 'z')
		{
			wcount++;
		}
		if (tboard[w_pos_x + 1][w_pos_y+1] == ' ')
		{
			tboard[w_pos_x + 1][w_pos_y+1] = 'k';
		}
		else if (tboard[w_pos_x + 1][w_pos_y+1] > 'a' && tboard[w_pos_x + 1][w_pos_y+1] < 'z')
		{
			wcount++;
		}
		if (tboard[w_pos_x + 1][w_pos_y-1] == ' ')
		{
			tboard[w_pos_x + 1][w_pos_y-1] = 'k';
		}
		else if (tboard[w_pos_x + 1][w_pos_y-1] > 'a' && tboard[w_pos_x + 1][w_pos_y-1] < 'z')
		{
			wcount++;
		}
		if (tboard[w_pos_x - 1][w_pos_y - 1] == ' ')
		{
			tboard[w_pos_x - 1][w_pos_y - 1] = 'k';
		}
		else if (tboard[w_pos_x - 1][w_pos_y - 1] > 'a' && tboard[w_pos_x - 1][w_pos_y - 1] < 'z')
		{
			wcount++;
		}
		if (tboard[w_pos_x - 1][w_pos_y + 1] == ' ')
		{
			tboard[w_pos_x - 1][w_pos_y + 1] = 'k';
		}
		else if (tboard[w_pos_x - 1][w_pos_y + 1] > 'a' && tboard[w_pos_x - 1][w_pos_y + 1] < 'z')
		{
			wcount++;
		}
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				
				if (tboard[i][j] > 'A' && tboard[i][j] < 'Z')
				{
					if (isCheck(tboard, i, j, twcheck, tbcheck, 0))
						wcount++;
				}
			}
		}
	}
	else if (b_check)
	{
		tboard[b_pos_x][b_pos_y] = ' ';
		if (tboard[b_pos_x + 1][b_pos_y] == ' ')
		{
			tboard[b_pos_x + 1][b_pos_y] = 'K';
		}
		else if (tboard[w_pos_x + 1][w_pos_y] > 'A' && tboard[w_pos_x + 1][w_pos_y] < 'Z')
		{
			bcount++;
		}
		if (tboard[b_pos_x - 1][b_pos_y] == ' ')
		{
			tboard[b_pos_x - 1][b_pos_y] = 'K';
		}
		else if (tboard[b_pos_x - 1][b_pos_y] > 'A' && tboard[b_pos_x - 1][b_pos_y] < 'Z')
		{
			bcount++;
		}
		if (tboard[b_pos_x][b_pos_y + 1] == ' ')
		{
			tboard[b_pos_x][b_pos_y + 1] = 'K';
		}
		else if (tboard[w_pos_x][w_pos_y + 1] > 'A' && tboard[w_pos_x][w_pos_y + 1] < 'Z')
		{
			bcount++;
		}
		if (tboard[b_pos_x][b_pos_y - 1] == ' ')
		{
			tboard[b_pos_x][b_pos_y - 1] = 'K';
		}
		else if (tboard[b_pos_x][b_pos_y - 1] > 'A' && tboard[b_pos_x][b_pos_y - 1] < 'Z')
		{
			bcount++;
		}
		if (tboard[b_pos_x + 1][b_pos_y + 1] == ' ')
		{
			tboard[b_pos_x + 1][b_pos_y + 1] = 'K';
		}
		else if (tboard[b_pos_x + 1][b_pos_y + 1] > 'A' && tboard[b_pos_x + 1][b_pos_y + 1] < 'Z')
		{
			bcount++;
		}
		if (tboard[b_pos_x + 1][b_pos_y - 1] == ' ')
		{
			tboard[b_pos_x + 1][b_pos_y - 1] = 'K';
		}
		else if (tboard[b_pos_x + 1][b_pos_y - 1] > 'A' && tboard[b_pos_x + 1][b_pos_y - 1] < 'Z')
		{
			bcount++;
		}
		if (tboard[b_pos_x - 1][b_pos_y - 1] == ' ')
		{
			tboard[b_pos_x - 1][b_pos_y - 1] = 'K';
		}
		else if (tboard[b_pos_x - 1][b_pos_y - 1] > 'A' && tboard[b_pos_x - 1][b_pos_y - 1] < 'Z')
		{
			bcount++;
		}
		if (tboard[b_pos_x - 1][b_pos_y + 1] == ' ')
		{
			tboard[b_pos_x - 1][b_pos_y + 1] = 'K';
		}
		else if (tboard[b_pos_x - 1][b_pos_y + 1] > 'A' && tboard[b_pos_x - 1][b_pos_y + 1] < 'Z')
		{
			bcount++;
		}
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{

				if (tboard[i][j] > 'a' && tboard[i][j] < 'z')
				{
					if (isCheck(tboard, i, j, twcheck, tbcheck, 1))
						bcount++;
				}
			}
		}
	}

	if (wcount == 5 && (w_pos_x==0))
		return true;
	if (wcount == 5 && (w_pos_y == 0))
		return true;
	if (wcount == 5 && (w_pos_x == 7))
		return true;
	if (wcount == 5 && (w_pos_y == 7))
		return true;
	else if (w_pos_x == 0 && w_pos_y == 0)
	{
		if (wcount == 3)
			return true;
	}
	else if (w_pos_x == 0 && w_pos_y == 7)
	{
		if (wcount == 3)
			return true;
	}
	else if (w_pos_x == 7 && w_pos_y == 0)
	{
		if (wcount == 3)
			return true;
	}
	else if (w_pos_x == 7 && w_pos_y == 7)
	{
		if (wcount == 3)
			return true;
	}
	else if(wcount == 8)
		return true;
	if (bcount == 5 && (b_pos_x == 0))
		return true;
	if (bcount == 5 && (b_pos_y == 7))
		return true;
	if (bcount == 5 && (w_pos_x == 7))
		return true;
	if (bcount == 5 && (w_pos_y == 0))
		return true;
	else if (b_pos_x == 0 && b_pos_y == 0)
	{
		if (bcount == 3)
			return true;
	}
	else if (b_pos_x == 0 && b_pos_y == 7)
	{
		if (bcount == 3)
			return true;
	}
	else if (b_pos_x == 7 && b_pos_y == 0)
	{
		if (bcount == 3)
			return true;
	}
	else if (b_pos_x == 7 && b_pos_y == 7)
	{
		if (wcount == 3)
			return true;
	}
	else if (bcount == 8)
		return true;
	return false;
}

bool stalemate(char board[][8], int turn)
{
	int w_pos_x, w_pos_y, wcount = 0, bcount = 0;
	int b_pos_x, b_pos_y;
	char tboard[8][8];
	bool twcheck = false, tbcheck = false;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			tboard[i][j] = board[i][j];
			if (board[i][j] == 'k')
			{
				w_pos_x = i;
				w_pos_y = j;
			}
			if (board[i][j] == 'K')
			{
				b_pos_x = i;
				b_pos_y = j;
			}
		}
	}
	if (turn)
	{
		if (w_check)
			return false;
		else
		{
			tboard[w_pos_x][w_pos_y] = ' ';
			if (tboard[w_pos_x + 1][w_pos_y] == ' ')
			{
				tboard[w_pos_x + 1][w_pos_y] = 'k';
			}
			else if (tboard[w_pos_x + 1][w_pos_y] > 'a' && tboard[w_pos_x + 1][w_pos_y] < 'z')
			{
				wcount++;
			}
			if (tboard[w_pos_x - 1][w_pos_y] == ' ')
			{
				tboard[w_pos_x - 1][w_pos_y] = 'k';
			}
			else if (tboard[w_pos_x - 1][w_pos_y] > 'a' && tboard[w_pos_x - 1][w_pos_y] < 'z')
			{
				wcount++;
			}
			if (tboard[w_pos_x][w_pos_y + 1] == ' ')
			{
				tboard[w_pos_x][w_pos_y + 1] = 'k';
			}
			else if (tboard[w_pos_x][w_pos_y + 1] > 'a' && tboard[w_pos_x][w_pos_y + 1] < 'z')
			{
				wcount++;
			}
			if (tboard[w_pos_x][w_pos_y - 1] == ' ')
			{
				tboard[w_pos_x][w_pos_y - 1] = 'k';
			}
			else if (tboard[w_pos_x][w_pos_y - 1] > 'a' && tboard[w_pos_x][w_pos_y - 1] < 'z')
			{
				wcount++;
			}
			if (tboard[w_pos_x + 1][w_pos_y + 1] == ' ')
			{
				tboard[w_pos_x + 1][w_pos_y + 1] = 'k';
			}
			else if (tboard[w_pos_x + 1][w_pos_y + 1] > 'a' && tboard[w_pos_x + 1][w_pos_y + 1] < 'z')
			{
				wcount++;
			}
			if (tboard[w_pos_x + 1][w_pos_y - 1] == ' ')
			{
				tboard[w_pos_x + 1][w_pos_y - 1] = 'k';
			}
			else if (tboard[w_pos_x + 1][w_pos_y - 1] > 'a' && tboard[w_pos_x + 1][w_pos_y - 1] < 'z')
			{
				wcount++;
			}
			if (tboard[w_pos_x - 1][w_pos_y - 1] == ' ')
			{
				tboard[w_pos_x - 1][w_pos_y - 1] = 'k';
			}
			else if (tboard[w_pos_x - 1][w_pos_y - 1] > 'a' && tboard[w_pos_x - 1][w_pos_y - 1] < 'z')
			{
				wcount++;
			}
			if (tboard[w_pos_x - 1][w_pos_y + 1] == ' ')
			{
				tboard[w_pos_x - 1][w_pos_y + 1] = 'k';
			}
			else if (tboard[w_pos_x - 1][w_pos_y + 1] > 'a' && tboard[w_pos_x - 1][w_pos_y + 1] < 'z')
			{
				wcount++;
			}
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{

					if (tboard[i][j] > 'A' && tboard[i][j] < 'Z')
					{
						if (isCheck(tboard, i, j, twcheck, tbcheck, !turn))
							wcount++;
					}
				}
			}
			if (w_pos_x == 0 && wcount == 5)
				return true;
			else if (w_pos_x == 7 && wcount == 5)
				return true;
			else if (w_pos_x == 0 && w_pos_y == 0)
			{
				if (wcount == 3)
					return true;
			}
			else if (w_pos_x == 0 && w_pos_y == 7)
			{
				if (wcount == 3)
					return true;
			}
			else if (w_pos_x == 7 && w_pos_y == 0)
			{
				if (wcount == 3)
					return true;
			}
			else if (w_pos_x == 7 && w_pos_y == 7)
			{
				if (wcount == 3)
					return true;
			}
			else if (w_pos_y == 7 && wcount == 5)
				return true;
			else if (w_pos_y == 0 && wcount == 5)
				return true;
			else if (wcount == 8)
				return true;
		}
	}
	else
	{
		if (b_check)
			return false;
		else
		{
			tboard[b_pos_x][b_pos_y] = ' ';
			if (tboard[b_pos_x + 1][b_pos_y] == ' ')
			{
				tboard[b_pos_x + 1][b_pos_y] = 'K';
			}
			else if (tboard[w_pos_x + 1][w_pos_y] > 'A' && tboard[w_pos_x + 1][w_pos_y] < 'Z')
			{
				bcount++;
			}
			if (tboard[b_pos_x - 1][b_pos_y] == ' ')
			{
				tboard[b_pos_x - 1][b_pos_y] = 'K';
			}
			else if (tboard[b_pos_x - 1][b_pos_y] > 'A' && tboard[b_pos_x - 1][b_pos_y] < 'Z')
			{
				bcount++;
			}
			if (tboard[b_pos_x][b_pos_y + 1] == ' ')
			{
				tboard[b_pos_x][b_pos_y + 1] = 'K';
			}
			else if (tboard[w_pos_x][w_pos_y + 1] > 'A' && tboard[w_pos_x][w_pos_y + 1] < 'Z')
			{
				bcount++;
			}
			if (tboard[b_pos_x][b_pos_y - 1] == ' ')
			{
				tboard[b_pos_x][b_pos_y - 1] = 'K';
			}
			else if (tboard[b_pos_x][b_pos_y - 1] > 'A' && tboard[b_pos_x][b_pos_y - 1] < 'Z')
			{
				bcount++;
			}
			if (tboard[b_pos_x + 1][b_pos_y + 1] == ' ')
			{
				tboard[b_pos_x + 1][b_pos_y + 1] = 'K';
			}
			else if (tboard[b_pos_x + 1][b_pos_y + 1] > 'A' && tboard[b_pos_x + 1][b_pos_y + 1] < 'Z')
			{
				bcount++;
			}
			if (tboard[b_pos_x + 1][b_pos_y - 1] == ' ')
			{
				tboard[b_pos_x + 1][b_pos_y - 1] = 'K';
			}
			else if (tboard[b_pos_x + 1][b_pos_y - 1] > 'A' && tboard[b_pos_x + 1][b_pos_y - 1] < 'Z')
			{
				bcount++;
			}
			if (tboard[b_pos_x - 1][b_pos_y - 1] == ' ')
			{
				tboard[b_pos_x - 1][b_pos_y - 1] = 'K';
			}
			else if (tboard[b_pos_x - 1][b_pos_y - 1] > 'A' && tboard[b_pos_x - 1][b_pos_y - 1] < 'Z')
			{
				bcount++;
			}
			if (tboard[b_pos_x - 1][b_pos_y + 1] == ' ')
			{
				tboard[b_pos_x - 1][b_pos_y + 1] = 'K';
			}
			else if (tboard[b_pos_x - 1][b_pos_y + 1] > 'A' && tboard[b_pos_x - 1][b_pos_y + 1] < 'Z')
			{
				bcount++;
			}
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{

					if (tboard[i][j] > 'a' && tboard[i][j] < 'z')
					{
						if (isCheck(tboard, i, j, twcheck, tbcheck, !turn))
							bcount++;
					}
				}
			}
			if (b_pos_x == 0 && bcount == 5)
				return true;
			else if (b_pos_x == 7 && bcount == 5)
				return true;
			else if (b_pos_x == 0 && b_pos_y == 0)
			{
				if (bcount == 3)
					return true;
			}
			else if (b_pos_x == 0 && b_pos_y == 7)
			{
				if (bcount == 3)
					return true;
			}
			else if (b_pos_x == 7 && b_pos_y == 0)
			{
				if (bcount == 3)
					return true;
			}
			else if (b_pos_x == 7 && b_pos_y == 7)
			{
				if (wcount == 3)
					return true;
			}
			else if (b_pos_y == 7 && bcount == 5)
				return true;
			else if (b_pos_y == 0 && bcount == 5)
				return true;
			else if (bcount == 8)
				return true;
		}
	}
	return false;
}

void printBoard(char Board[][8], bool turn)
{
	system("CLS");
	for (int i = 0; i < 8; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		cout << "-----------------------------------------\n";
		for (int j = 0; j < 8; j++)
		{
			if (Board[i][j] > 'a' && Board[i][j] < 'z')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				cout << "| " << Board[i][j] << " |";
			}
			 else if (Board[i][j] > 'A' && Board[i][j] < 'Z')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
				cout << "| " << Board[i][j] << " |";
			}
			else 
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				cout << "| " << Board[i][j] <<  " |";
			}
		}
		cout << "|\n";
	}
	
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		
	cout << "-----------------------------------------\n";
	if (turn)
	{
		cout << "TURN: WHITE \n";
	}
	else
	{
		cout << "TURN: BLACK \n";
	}

	if (w_check)
		cout << "\nCHECK : WHITE\n";
	else if (b_check)
		cout << "\nCHECK : BLACK\n";
	else cout << "\nCHECK : NONE\n";
	if (checkmate(Board) && w_check) {
		cout << "\nBLACK WINS\nGame Over\n";
		ischeckmate = true;
	}
	else if (checkmate(Board) && b_check) {
		cout << "\nWHITE WINS\nGame Over\n";
		ischeckmate = true;
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (Board[i][j] > 'a'&&Board[i][j] < 'z')
				wpieces++;
			if (Board[i][j] > 'A'&&Board[i][j] < 'Z')
				bpieces++;
		}
	}

	if (bpieces < 15)
	{
		if (stalemate(Board, turn))
		{
			cout << "\nSTALEMATE!!\nGAMEOVER!!\n";
			isstalemate = true;
		}
	}
	if (wpieces < 15)
	{
		if (stalemate(Board, turn))
		{
			cout << "\nSTALEMATE!!\nGAMEOVER!!\n";
			isstalemate = true;
		}
	}
	


}

int main()
{
	bool turn = 1; // 1 represents white and 0 black.
	bool check = false;
	char newB[8][8] = {
	{'R','N','B','Q','K','B','N','R'},
	{'P','P','P','P','P','P','P','P'},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ',' ',' ',' '},
	{'p','p','p','p','p','p','p','p'},
	{'r','n','b','q','k','b','n','r'}
	};
	cout << "WELCOME TO SIMPLE CHESS GAME BY NOUMAN!\n";
	char board[8][8];
	initboard(newB, board);
	printBoard(board, turn);

	char input[5];

	cout << "\nType 'exit' to leave\nType 'save' to save and exit\ntype in 4 characters to move for example 'a2a4' to move from a2 to a4\n";
	while (true)
	{
		bool moveDone = false , flag = false;
		check = false;
		cin >> input;

		if (input[0] == 'e' && input[1] == 'x' && input[2] == 'i' && input[3] == 't')
		{
			break;
		}
		else if (input[0] == 's' && input[1] == 'a' && input[2] == 'v' && input[3] == 'e')
		{
			ofstream fout("C:\\Users\\TOSHIBA\\Documents\\chesssaved.txt");
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					fout << board[i][j];
				}
				fout << endl;
			}
			//break;
		}
		else
		{
			int prow, pcol, nrow, ncol;
			pcol = input[0] - 97;
			ncol = input[2] - 97;
			prow = input[1] - 49;
			nrow = input[3] - 49;

			if (validPlayer(turn, prow, pcol, board) && isWayClear(board, prow, pcol, nrow, ncol))
			{
				if (w_check)
				{
					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							if (board[i][j] > 'A' && board[i][j] < 'Z')
							{
								if (isCheck(board, i, j,w_check,b_check ,!turn))
								{
									cout << "\nInvalid Move\n";
									flag = true;
									//break;
								}
							}
						}
					}
				}
				else if (b_check)
				{
					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							if (board[i][j] > 'a' || board[i][j] < 'z')
							{
								if (isCheck(board, i, j,w_check, b_check, !turn))
								{
									cout << "\nInvalid Move\n";
									flag = true;
									//break;
								}
							}
						}
					}
				}
				//check = isCheck(board, nrow, ncol, turn);
				if (!flag)
				{
					if (board[prow][pcol] == 'p' || board[prow][pcol] == 'P') // if pawn.
					{
						if (em_passant(board, prow, pcol, nrow, ncol))
						{
							Pawn_promotion(board, prow, pcol, nrow, ncol);
							board[nrow][ncol] = board[prow][pcol];
							board[prow][pcol] = ' ';
							board[prow][ncol] = ' ';
							moveDone = true;
						}
						else if (validPawnMove(board, prow, pcol, nrow, ncol))
						{
							board[nrow][ncol] = board[prow][pcol];
							board[prow][pcol] = ' ';
							moveDone = true;
						}
					}
					else if (board[prow][pcol] == 'n' || board[prow][pcol] == 'N') // if knight
					{
						if (validKnightMove(board, prow, pcol, nrow, ncol, turn))
						{
							board[nrow][ncol] = board[prow][pcol];
							board[prow][pcol] = ' ';
							moveDone = true;
						}
					}
					else if (board[prow][pcol] == 'r' || board[prow][pcol] == 'R') // if rook
					{
						if (validRookMove(board, prow, pcol, nrow, ncol, turn))
						{
							if (castling(board, prow, pcol, nrow, ncol))
							{
								board[nrow][ncol] = board[prow][pcol];
								
								if (board[prow][pcol] == 'r')
								{
									if (prow == 7 && pcol == 7)
									{
										board[7][6] = 'k';
										board[7][4] = ' ';
									}
									else if (prow == 7 && pcol == 0)
									{
										board[7][2] = 'k';
										board[7][4] = ' ';
									}
								}
								else if(board[prow][pcol] == 'R')
								{
									if (prow == 0 && pcol == 7)
									{
										board[0][6] = 'k';
										board[0][4] = ' ';
									}
									else if (prow == 0 && pcol == 0)
									{
										board[0][2] = 'k';
										board[0][4] = ' ';
									}
								}
								board[prow][pcol] = ' ';
								moveDone = true;
							}
							else
							{
								board[nrow][ncol] = board[prow][pcol];
								board[prow][pcol] = ' ';
								moveDone = true;
							}
						}
					}


					else if (board[prow][pcol] == 'b' || board[prow][pcol] == 'B') // if bishop
					{
						if (validBishopMove(board, prow, pcol, nrow, ncol, turn))
						{
							board[nrow][ncol] = board[prow][pcol];
							board[prow][pcol] = ' ';
							moveDone = true;
						}
					}
					else if (board[prow][pcol] == 'k' || board[prow][pcol] == 'K') // if king
					{
						if (validKingMove(board, prow, pcol, nrow, ncol, turn))
						{
							board[nrow][ncol] = board[prow][pcol];
							board[prow][pcol] = ' ';
							moveDone = true;
						}
					}
					else if (board[prow][pcol] == 'q' || board[prow][pcol] == 'Q') // if queen
					{
						if (validQueenMove(board, prow, pcol, nrow, ncol, turn))
						{
							board[nrow][ncol] = board[prow][pcol];
							board[prow][pcol] = ' ';
							moveDone = true;
						}
					}

					else if (!moveDone)
					{
						cout << " INVALID MOVE ";
					}


					check = isCheck(board, nrow, ncol, w_check, b_check, turn);
					if (moveDone)
					{
						turn = !turn;
					}
					printBoard(board, turn);
					if (ischeckmate)
						break;
					if (isstalemate)
						break;
				}
				//check = isCheck(board, nrow, ncol, turn);
			}
		}
		
	}
	cout << "GAME EXITED SUCCESSFULLY!!!!\n";
	system("pause");
	return 0;
}


