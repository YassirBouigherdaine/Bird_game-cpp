#include"game.h"





constexpr auto SCREEN_HEIGHT = 30;
constexpr auto SCREEN_WIDTH = 90;
constexpr auto SCREEN_WIND = 60;

char obstacle[2] = {'#','#'};

char space[2] = {' ',' '};

char bird[3][5] = { '\x5C','\x5C',' ',' ',' ',
					' ','\x5C','\x5C',' ',' ',
					'>','=','=','=','>' };

int bird_pos = 10;

int space_pos = 4 + rand() % 16;

int i, j;

int score = 0;

int k = 4;

bool game_over = false;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

COORD cursorPos;

void gotoxy(int x, int y)
{
	cursorPos.X = x;
	cursorPos.Y = y;
	SetConsoleCursorPosition(console, cursorPos);
}

 
void draw_bird()
{
	// draw bird 

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 5; j++)
		{
			gotoxy(j + 15, i + bird_pos);
			std::cout << bird[i][j];
		}
	}

	Sleep(50);

	// erase bird

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 5; j++)
		{
			gotoxy(j + 15, i + bird_pos);
			std::cout << " ";
		}
	}
}

void draw_screen()
{
	for (i = 0; i < SCREEN_WIDTH; i++)
	{
		gotoxy(i, 0);
		std::cout << "#";
		gotoxy(i, SCREEN_HEIGHT - 1);
		std::cout << "#";
	}

	for (i = 0; i < SCREEN_HEIGHT; i++)
	{
		gotoxy(0, i);
		std::cout << "#";
		gotoxy(60, i);
		std::cout << "#";
		gotoxy(SCREEN_WIDTH, i);
		std::cout << "#";

	}

	// drawing game menu

	gotoxy(SCREEN_WIND + 7 , 5 );
	std::cout << " FLAY BIRD GAME\n";
	gotoxy(SCREEN_WIND + 7, 6);
	std::cout << " --------------";
	gotoxy(SCREEN_WIND + 7, 10);
	std::cout << " score : "<<score;
}


void draw_obstacle()
{
	// drawing top obstacle

	for (i = 1; i < space_pos; i++)
	{ 
		gotoxy(SCREEN_WIND - k, i);
		std::cout << obstacle;

		// collision with obstacle

		if (SCREEN_WIND - k == j + 15 && space_pos > bird_pos)
		{
			game_over = true;
		}
	}

	// drawing buttom obstacle

	for (i = space_pos + 6; i < SCREEN_HEIGHT - 1; i++)
	{
		gotoxy(SCREEN_WIND - k, i);
		std::cout << obstacle;

		// collision with obstacle

		if (SCREEN_WIND - k == j + 15  && bird_pos + 5 > space_pos + 6)
		{
			game_over = true;
		}
	}
}

void erase_obstacle()
{
	for (i = 1; i < SCREEN_HEIGHT - 1; i++)
	{
		gotoxy(SCREEN_WIND - k, i );
		std::cout << space;
	}
}

void input()
{
	if (_kbhit())
	{
		char p = _getch();

		if (p == 32)
		{
			bird_pos -= 2;
		}
	}
}

void gameOver()
{
	system("cls");

	std::cout << "\n\n\t\t-------------------------------\n";
	std::cout << "\t\t-------------------------------\n";
	std::cout << "\t\t--------- GAME OVER -----------\n";
	std::cout << "\t\t-------------------------------\n";
	std::cout << "\t\t-------------------------------\n";

}

void run_game()
{
	srand((unsigned)time(NULL));

	while (!game_over)
	{
		draw_screen();

		draw_obstacle();

		Sleep(50);

		erase_obstacle();

		draw_bird();

		input();

		bird_pos++;
		k++;
		
		// collision with borders

		if (bird_pos == SCREEN_HEIGHT - 4 || bird_pos < 2)
		{
			game_over = true;
		}
		
		// updating score

		else if (SCREEN_WIND - k == j + 10)
		{
			score++;
		}

		// updating obstacle

		else if (SCREEN_WIND - k == 4)
		{
			space_pos = 4 + rand() % 16;

			k = 6;
		}
	}

	gameOver();
	
}
























































