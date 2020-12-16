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

int space_pos1 = 4 + rand() % 16;
int space_pos2 = 4 + rand() % 16;

bool game_over = false;
int i, j;
int score = 0;

// to move obstacles

int k = 20;    
int p = 1;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

COORD cursorPos;




void gotoxy(int x, int y)
{
	cursorPos.X = x;
	cursorPos.Y = y;
	SetConsoleCursorPosition(console, cursorPos);
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

	gotoxy(SCREEN_WIND + 7, 5);
	std::cout << " FLAPPY BIRD GAME\n";
	gotoxy(SCREEN_WIND + 7, 6);
	std::cout << " --------------";
	gotoxy(SCREEN_WIND + 7, 10);
	std::cout << " score : " << score;
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

	// collision with borders

	if (bird_pos == SCREEN_HEIGHT - 4 || bird_pos < 2)
	{
		game_over = true;
	}
}


void draw_Fobstacle()
{
	// drawing top obstacle

	for (i = 1; i < space_pos1; i++)
	{ 
		gotoxy(SCREEN_WIND - k, i);
		std::cout << obstacle;

		// collision with obstacle

		if (SCREEN_WIND - k == j + 15 && space_pos1 > bird_pos)
		{
			game_over = true;
		}
	}

	// drawing buttom obstacle

	for (i = space_pos1 + 6; i < SCREEN_HEIGHT - 1; i++)
	{
		gotoxy(SCREEN_WIND - k, i);
		std::cout << obstacle;

		// collision with obstacle

		if (SCREEN_WIND - k == j + 15  && bird_pos + 5 > space_pos1 + 6)
		{
			game_over = true;
		}
	}
}

void erase_Fobstacle()
{
	for (i = 1; i < SCREEN_HEIGHT - 1; i++)
	{
		gotoxy(SCREEN_WIND - k, i );
		std::cout << space;
	}
}


void draw_Sobstacle()
{
	// drawing top obstacle

	for (i = 1; i < space_pos2; i++)
	{
		gotoxy(SCREEN_WIND - p, i);
		std::cout << obstacle;

		// collision with obstacle

		if (SCREEN_WIND - p == j + 15 && space_pos2 > bird_pos)
		{
			game_over = true;
		}
	}

	// drawing buttom obstacle

	for (i = space_pos2 + 6; i < SCREEN_HEIGHT - 1; i++)
	{
		gotoxy(SCREEN_WIND - p, i);
		std::cout << obstacle;

		// collision with obstacle

		if (SCREEN_WIND - p == j + 15 && bird_pos + 5 > space_pos2 + 6)
		{
			game_over = true;
		}
	}
}

void erase_Sobstacle()
{
	for (i = 1; i < SCREEN_HEIGHT - 1; i++)
	{
		gotoxy(SCREEN_WIND - p, i);
		std::cout << space;
	}
}


void update()
{
	// updating score

	if (SCREEN_WIND - k == j + 10 || SCREEN_WIND - p == j + 10)
	{
		score++;
	}

	// updating first obstacle

	else if (SCREEN_WIND - k == 10)
	{
		space_pos1 = 4 + rand() % 16;
		
		k = 5;
	}

	// updating second obstacle

	else if ( SCREEN_WIND - p == 10)
	{
		space_pos2 = 4 + rand() % 16;

		p = 1;
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
	std::cout << "\t\t--------------  ---------------\n";
	std::cout << "\t\t-------   GAME OVER   ---------\n";
	std::cout << "\t\t--------------  ---------------\n";
	std::cout << "\t\t-------------------------------\n";

}


void run_game()
{
	srand((unsigned)time(NULL));

	while (!game_over)
	{
		draw_screen();

		// draw first obstacle

		draw_Fobstacle();

		Sleep(50);

		erase_Fobstacle();

		Sleep(50);

		// updating second obstacle

		draw_Sobstacle();

		Sleep(50);

		erase_Sobstacle();

		draw_bird();

		input();

		update();

<<<<<<< HEAD
		bird_pos++;
		k++;
		p++;
		
	}

	gameOver();
	
}
=======









>>>>>>> 671f26dad9c35f26581565b1b8c63d49abef83e5















