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
























































/*constexpr auto SCREEN_HEIGHT = 30;
constexpr auto SCREEN_WIDTH = 80;
constexpr auto WIND_WIDTH = 60;
constexpr auto SPACE_SIZE = 6;               // gap size
constexpr auto OBSTACLE_DIFF = 30;           // pip diff

int obstacle_pos[5];                         // pip pose
int space_pos[5];                                //gap pos
int obstacle[5];                          // pip flag


char bird[3][5] = { '\x5C','\x5C',' ',' ',' ',
					' ','\x5C','\x5C',' ',' ',
					'>','=','=','=','\xE7'};


int bird_pos = 5;
int score = 0;
bool game_over = false;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD cursorPos;

void gotoxy(int x, int y)
{
	cursorPos.X = x;
	cursorPos.Y = y;
	SetConsoleCursorPosition(console, cursorPos);
}


void set_console_cursor(bool visible, DWORD size)
{
	if (size == 0)
		size = 10;

	CONSOLE_CURSOR_INFO lpcursor;
	lpcursor.bVisible = visible;                 // the cursor is visible
	lpcursor.dwSize = size;                      //it specifies the percentage of a character cell that is filled by the cursor 1<lpcursor>100
	SetConsoleCursorInfo(console, &lpcursor);    //it reports whether the cursor is visible and describes the appearance of the cursor
}

void draw_border()
{
	std::cout << "\t FLAPPY BIRD GAME\n\n";

	for (int i = 0; i < SCREEN_WIDTH ; i++)
	{
		gotoxy(i, 0);
		std::cout << "#";
		gotoxy(i, SCREEN_HEIGHT);
		std::cout << "#";
	}
	
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		gotoxy(0,i);
		std::cout << "#";
		gotoxy(SCREEN_WIDTH, i);
		std::cout << "#";
		
	}  
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		gotoxy(i, 0);
		std::cout << "#";
		gotoxy(i, SCREEN_HEIGHT);
		std::cout << "#";
	}  

	for (int i = 0; i < SCREEN_HEIGHT ; i++)
	{
		gotoxy(WIND_WIDTH, i);
		std::cout << "#";
	}

}

void generate_obstacle(int n)         // gen pip
{
	space_pos[n] = 3 + rand() % 20;

}

void draw_obstacle(int n)                 // draw pipe
{
	if (obstacle[n] == true)
	{
		for (int i = space_pos[n] + SPACE_SIZE ; i <SCREEN_HEIGHT-1 ; i++ )
		{
			gotoxy(SCREEN_WIDTH - obstacle_pos[n], i + 1);
			std::cout << "*****";
		}
		for (int i = 0; i < space_pos[n]; i++)
		{
			gotoxy(SCREEN_WIDTH - obstacle_pos[n], i + 1);
			std::cout << "*****";
		}
	}
}

void clear_obstacle(int n)
{
	if (obstacle[n] == true)
	{
		for (int i = space_pos[n] + SPACE_SIZE; i < SCREEN_HEIGHT - 1; i++)
		{
			gotoxy(SCREEN_WIDTH - obstacle_pos[n], i + 1);
			std::cout << "     ";
		}
		for (int i = 0; i < space_pos[n]; i++)
		{
			gotoxy(SCREEN_WIDTH - obstacle_pos[n], i + 1);
			std::cout << "     ";
		}
	}
}

void draw_bird()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			gotoxy(j + 3, i + bird_pos);
			std::cout << bird[i][j];
		}
	}
}

void erase_bird()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			gotoxy(j + 3, i + bird_pos);
			std::cout <<" ";
		}
	}
}

int collision()
{
	if (obstacle_pos[0] >= 60)
	{
		if (bird_pos > space_pos[0] + SPACE_SIZE || bird_pos < space_pos[0])
		{
			return 1;
		}
	}
}


void play()
{
	bird_pos = 5;
	score = 0;
	obstacle[0] = 1;
	obstacle[1] = 0;
	obstacle_pos[0] = obstacle_pos[1] = 4;

	system("cls");
	draw_border();
	generate_obstacle(0);
 

	while (true)
	{
		if (_kbhit())
		{
			char p = _getch();

			if (p == 32)
			{
				if (bird_pos > 2)
				{
					bird_pos -= 2;
				}
			}

			if (p == 27)
			{
				bird_pos += 2;
			}

			draw_bird();
			draw_obstacle(0);
			draw_obstacle(1);

			// collision with obsacle
			if (collision() == 1)
			{
				game_over = true;
			    return; 
			}

			Sleep(100);
			erase_bird();
			clear_obstacle(0);
			clear_obstacle(1);

			bird_pos += 1;

			if (bird_pos > SCREEN_HEIGHT - 2)
			{
				game_over = true;

			}
			if (obstacle[0] == 1)
			{
				obstacle_pos[0] += 3;
			}
			if (obstacle[1] == 1)
			{
				obstacle_pos[1] += 3;
			}
			if (obstacle_pos[0] >= 40 && obstacle_pos[0] < 42)
			{
				obstacle[1] = 1;
				obstacle_pos[1] = 4;
				generate_obstacle(1);

			}
			if (obstacle_pos[0] > 68)
			{
				score++;
				obstacle[1] = 0;
				obstacle_pos[0] = obstacle_pos[1];
				space_pos[0] = space_pos[1];
			}
		}
	}
}
	

void game()
{
	while (!game_over)
	{
		set_console_cursor(1, 0);

		srand((unsigned)time(NULL));

		system("cls");
		play();
	}
	
	
}*/