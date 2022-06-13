#include <iostream>
#include <algorithm>

#define SIZE 5
#define PLAYER 1
#define AI 2


struct MoveAI
{
    int row, col;
};

char Player_Move = 'X';
char AI_Move = 'O';

bool GridNotFull(char grid[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (grid[i][j] == ' ')
            {
                return true;
            }
        }
    }

    return false;
}

int calculate(char grid[SIZE][SIZE])
{
    int row_counter = 0;
    int col_counter = 0;
    int diag_counter = 0;

    for (int row = 0; row < SIZE; row++)
    {
        for (int i = 1; i < SIZE; i++)
        {
            if (grid[row][0] != ' ' && grid[row][0] == grid[row][i])
            {
                ++row_counter;
            }
        }
        if (row_counter == SIZE - 1)
        {
            if (grid[row][0] == 'X')
            {
                return -20;
            }
            else if (grid[row][0] == 'O')
            {
                return 10;
            }
        }
        row_counter = 0;
    }

    for (int col = 0; col < SIZE; col++)
    {
        for (int j = 1; j < SIZE; j++)
        {
            if (grid[0][col] != ' ' && grid[0][col] == grid[j][col])
            {
                ++col_counter;
            }
        }

        if (col_counter == SIZE - 1)
        {
            if (grid[0][col] == 'X')
            {
                return -20;
            }
            else if (grid[0][col] == 'O')
            {
                return 10;
            }
        }
        col_counter = 0;
    }

    for (int k = 1; k < SIZE; k++)
    {
        if (grid[0][0] != ' ' && grid[0][0] == grid[k][k])
        {
            ++diag_counter;
        }
    }

    if (diag_counter == SIZE - 1)
    {
        if (grid[0][0] == 'X')
        {
            return -20;
        }
        else if (grid[0][0] == 'O')
        {
            return 10;
        }
    }

    diag_counter = 0;
    int m = SIZE - 1;
    for (int l = 1; l < SIZE; l++)
    {
        if (grid[0][SIZE-1] != ' ' && grid[0][SIZE-1] == grid[l][m-1])
        {
            ++diag_counter;
        }
        --m;
    }

    if (diag_counter == SIZE - 1)
    {
        if (grid[0][SIZE-1] == 'X')
        {
            return -20;
        }
        else if (grid[0][SIZE-1] == 'O')
        {
            return 10;
        }
    }
    
    return 0;
}

int MinMax(char grid[SIZE][SIZE], int depth, bool AI_Turn, int alfa, int beta)
{
    int result = calculate(grid);

    if(result == 10 || result == -20)
    {
        return result;
    }
    if (depth == 5)
    {
        return 0;
    }

    if (!GridNotFull(grid))
    {
        return 0;
    }
    
    
    if (AI_Turn)
    {
        int best = -100;

        for (int row = 0; row < SIZE; row++)
        {
            for (int col = 0; col < SIZE; col++)
            {
                if(grid[row][col] == ' ')
                {
                    grid[row][col] = AI_Move;
                    best = std::max(best,MinMax(grid,depth+1,!AI_Turn, alfa,beta));
                    alfa = std::max(best,alfa);
                    grid[row][col] = ' ';
                    if (beta <= alfa)
                    {
                        break;
                    }
                    
                }
            }
            
        }
        return best;
    }
    else
    {
        int best = 100;

        for (int row = 0; row < SIZE; row++)
        {
            for (int col = 0; col < SIZE; col++)
            {
                if (grid[row][col] == ' ')
                {
                    grid[row][col] = Player_Move;
                    best = std::min(best,MinMax(grid,depth+1,!AI_Turn,alfa,beta));
                    beta = std::min(beta,best);
                    grid[row][col] = ' ';
                    if(beta <= alfa)
                    {
                        break;
                    }
                }
                
            }
            
        }
        return best;
    }
    
}

MoveAI bestMove(char grid[SIZE][SIZE])
{
    int best = -100;

    MoveAI move;
    move.row = -1;
    move.col = -1;

    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            if (grid[row][col] == ' ')
            {
                grid[row][col] = AI_Move;
                int moveValue = MinMax(grid,0, false,-100,100);
                grid[row][col] = ' ';

                if (moveValue > best)
                {
                    move.row = row;
                    move.col = col;
                    best = moveValue;
                }
                
            }
            
        }
        
    }
    return move;
}

void Tutorial()
{
	if (SIZE == 3) {
		printf("Aby wstawic symbol w dana komorke wpisz x i y\n\n");
		printf("\t\t  (0,0) | (0,1) | (0,2)  \n");
		printf("\t\t--------------------------\n");
		printf("\t\t  (1,0) | (1,1) | (1,2)  \n");
		printf("\t\t--------------------------\n");
		printf("\t\t  (2,0) | (2,1) | (2,2)  \n\n");
	}
	if (SIZE == 4) {
		printf("Aby wstawic symbol w dana komorke wpisz x i y\n\n");
		printf("\t\t  (0,0) | (0,1) | (0,2) | (0,3) \n");
		printf("\t\t---------------------------------\n");
		printf("\t\t  (1,0) | (1,1) | (1,2) | (1,3)\n");
		printf("\t\t---------------------------------\n");
		printf("\t\t  (2,0) | (2,1) | (2,2) | (2,3)\n");
		printf("\t\t---------------------------------\n");
		printf("\t\t  (3,0) | (3,1) | (3,2) | (3,3) \n\n");
	}
	if (SIZE == 5) {
		printf("Aby wstawic symbol w dana komorke wpisz x i y\n\n");
		printf("\t\t  (0,0) | (0,1) | (0,2) | (0,3) | (0,4) \n");
		printf("\t\t-----------------------------------------\n");
		printf("\t\t  (1,0) | (1,1) | (1,2) | (1,3) | (1,4)\n");
		printf("\t\t-----------------------------------------\n");
		printf("\t\t  (2,0) | (2,1) | (2,2) | (2,3) | (2,4)\n");
		printf("\t\t-----------------------------------------\n");
		printf("\t\t  (3,0) | (3,1) | (3,2) | (3,3) | (3,4) \n");
		printf("\t\t----------------------------------------\n");
		printf("\t\t  (4,0) | (4,1) | (4,2) | (4,3) | (4,4)\n \n");
	}
}

void InitGrid(char grid[SIZE][SIZE])
{
    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            grid[row][col] = ' ';
        }
        
    }
    
}

void PrintGrid(char grid[SIZE][SIZE]) //grid jest tabilca charow - jak widac
{
	if (SIZE == 3)
	{
		printf("\n\n");
        printf("\t\t    || 0 | 1 | 2\n");
        printf("\t\t------------------\n");
        printf("\t\t------------------\n");
		printf("\t\t  0 || %c | %c | %c  \n", grid[0][0],
			grid[0][1], grid[0][2]); // w miejscach c kolejne wartosci z tablicy grid
		printf("\t\t------------------\n");
		printf("\t\t  1 || %c | %c | %c  \n", grid[1][0],
			grid[1][1], grid[1][2]);
		printf("\t\t------------------\n");
		printf("\t\t  2 || %c | %c | %c  \n\n", grid[2][0],
			grid[2][1], grid[2][2]);
	}

	if (SIZE == 4)
	{
		printf("\n\n");
        printf("\t\t    || 0 | 1 | 2 | 3\n");
        printf("\t\t----------------------\n");
        printf("\t\t----------------------\n");
		printf("\t\t  0 || %c | %c | %c | %c \n", grid[0][0],
			grid[0][1], grid[0][2], grid[0][3]); // w miejscach c kolejne wartosci z tablicy grid
		printf("\t\t----------------------\n");
		printf("\t\t  1 || %c | %c | %c | %c  \n", grid[1][0],
			grid[1][1], grid[1][2], grid[1][3]);
		printf("\t\t----------------------\n");
		printf("\t\t  2 || %c | %c | %c | %c  \n", grid[2][0],
			grid[2][1], grid[2][2], grid[2][3]);
		printf("\t\t----------------------\n");
		printf("\t\t  3 || %c | %c | %c | %c \n\n", grid[3][0],
			grid[3][1], grid[3][2], grid[3][3]);
	}
	if (SIZE == 5)
	{
		printf("\n\n");
        printf("\t\t    || 0 | 1 | 2 | 3 | 4 \n");
        printf("\t\t-------------------------\n");
        printf("\t\t-------------------------\n");
		printf("\t\t  0 || %c | %c | %c | %c | %c \n", grid[0][0],
			grid[0][1], grid[0][2], grid[0][3], grid[0][4]); // w miejscach c kolejne wartosci z tablicy grid
		printf("\t\t-------------------------\n");
		printf("\t\t  1 || %c | %c | %c | %c | %c \n", grid[1][0],
			grid[1][1], grid[1][2], grid[1][3], grid[1][4]);
		printf("\t\t-------------------------\n");
		printf("\t\t  2 || %c | %c | %c | %c | %c \n", grid[2][0],
			grid[2][1], grid[2][2], grid[2][3], grid[2][4]);
		printf("\t\t-------------------------\n");
		printf("\t\t  3 || %c | %c | %c | %c | %c \n", grid[3][0],
			grid[3][1], grid[3][2], grid[3][3], grid[3][4]);
		printf("\t\t-------------------------\n");
		printf("\t\t  4 || %c | %c | %c | %c | %c \n\n", grid[4][0],
			grid[4][1], grid[4][2], grid[4][3], grid[4][4]);
	}
}

void Winner(int whoseTurn)
{
    if(whoseTurn == PLAYER)
    {
        std::cout<<"Wygrywa gracz!!!"<<'\n';
    }
    else
    {
        std::cout<<"Wygrywa komputer!!!"<<'\n';
    }
    
}

bool checkRows(char grid[SIZE][SIZE])
{
    int row_counter = 0;

    for (int row = 0; row < SIZE; row++)
    {
        for (int i = 1; i < SIZE; i++)
        {
            if (grid[row][0] != ' ' && grid[row][0] == grid[row][i])
            {
                ++row_counter;
            }
        }
        if (row_counter == SIZE - 1)
        {
            return true;
        }
        row_counter = 0;
    }
    return false;
}

bool checkColumns(char grid[][SIZE])
{
    int col_counter = 0;

    for (int col = 0; col < SIZE; col++)
    {
        for (int j = 1; j < SIZE; j++)
        {
            if (grid[0][col] != ' ' && grid[0][col] == grid[j][col])
            {
                ++col_counter;
            }
        }

        if (col_counter == SIZE - 1)
        {
            return true;
        }
        col_counter = 0;
    }
    return false;
}

bool checkDiagonals(char grid[SIZE][SIZE])
{
    int diag_counter = 0;

    for (int k = 1; k < SIZE; k++)
    {
        if (grid[0][0] != ' ' && grid[0][0] == grid[k][k])
        {
            ++diag_counter;
        }
    }

    if (diag_counter == SIZE - 1)
    {
        return true;
    }

    diag_counter = 0;
    int m = SIZE - 1;
    for (int l = 1; l < SIZE; l++)
    {
        if (grid[0][SIZE-1] != ' ' && grid[0][SIZE-1] == grid[l][m-1])
        {
            ++diag_counter;
        }
        --m;
    }

    if (diag_counter == SIZE - 1)
    {
       return true;
    }

    return false;
}

bool GameOver(char grid[SIZE][SIZE])
{
    if(checkRows(grid)||checkColumns(grid)||checkDiagonals(grid))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Play(int whoseTurn)
{


    char grid[SIZE][SIZE];

    InitGrid(grid);
    Tutorial();
    int counter = 0;
    int x,y;

    while (!GameOver(grid) && counter != (SIZE*SIZE))
    {
       if (whoseTurn == PLAYER)
       {
        std::cout << "Podaj numer wiersza: ";
        std::cin >> x;
        std::cout <<'\n'<<"Podaj numer kolumny: ";
        std::cin >> y;
        std::cout <<'\n';

        if (x>=SIZE || y >= SIZE)
        {
            std::cout << "Przekroczono zakres wartości - spróbuj ponownie"<<'\n';
        }
        else
        {
            if(grid[x][y] == ' ')
            {
                grid[x][y] = Player_Move;
                std::cout <<"Gracz wstawił X w pole ("<<x<<','<<y<<")\n";
                PrintGrid(grid);
                ++counter;
                whoseTurn = AI;
            }
            else
            {
                std::cout << "To pole jest już zajęte - spróbuj ponownie\n";
            }
        }
        
        
       }
       else if (whoseTurn == AI)
       {
            MoveAI move = bestMove(grid);
            x = move.row;
            y = move.col;
            grid[x][y] = AI_Move;
            std::cout <<"Komputer wstawił O w pole ("<<x<<','<<y<<")\n";
            PrintGrid(grid);
            ++counter;
            whoseTurn = PLAYER;
       }
       
       
    }

    if(!GameOver(grid) && counter == (SIZE*SIZE))
    {
        std::cout << "Remis!!!\n";
    }
    else
    {
        if (whoseTurn == PLAYER)
        {
            whoseTurn = AI;
        }
        else if (whoseTurn == AI)
        {
            whoseTurn = PLAYER;
        }
        
        Winner(whoseTurn);
    }
    
}
int main()
{
    Play(PLAYER);

    return 0;
}