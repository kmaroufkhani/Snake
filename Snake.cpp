#include <iostream>
#include <cstdlib>
#include <time.h>
#include <conio.h>
#include <vector>
#include <windows.h>

using namespace std;

enum Direction { NONE, LEFT, RIGHT, UP, DOWN };
// ************ variables **
Direction direction;
int width = 26,
height = 26,
snakeX,
snakeY,
fruitX,
fruitY,
tailCount = 0,
score = 0;

bool Exit = false,
gameOver = false;

vector<int> tailX;
vector<int> tailY;
// sets position of the fruit
void setFruit()
{
	fruitX = snakeX;
	fruitY = snakeY;
	// make sure fruit is not at snake or on walls
	while (fruitX == snakeX && fruitY == snakeY)
	{
		fruitX = rand() % (height - 2);
		fruitY = rand() % (width - 2);
		if (fruitX == 0 || fruitY == 0 || fruitX > height - 2 || fruitY > height - 2)
		{
			setFruit();
		}
	}
}
// setup
void setup()
{
	gameOver = false;
	direction = NONE;
	snakeX = snakeY = height / 2;
	setFruit();
	tailX.clear();
	tailY.clear();
	tailCount = 0;
	tailX.push_back(0);
	tailY.push_back(0);
}
// to draw each round
void draw()
{
	system("cls");

	// first line
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;

	// middle lines
	for (int y = 0; y < height - 2; y++)
	{
		for (int x = 0; x < width; x++)
		{
			// fruit
			if (x == fruitX && y == fruitY)
			{
				cout << "O";
				continue;
			}
			// snake
			if (x == snakeX && y == snakeY)
			{
				cout << "Q";
				continue;
			}
			// first char
			if (x == 0)
				cout << "#";
			// last char
			else if (x == width - 1)
			{
				cout << "#" << endl;
			}
			//white space or tale
			else
			{
				bool printed = false;
				for (int t = 0; t < tailCount; t++)
				{
					if (tailX[t] == x && tailY[t] == y)
					{
						cout << "o";
						printed = true;
					}
				}
				if (!printed)
					cout << " ";
			}
		}

	}
	// last line
	for (int i = 0; i < width; i++)
		cout << "#";
} // setup

// set direction for snake
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			direction = LEFT;
			break;
		case 'd':
			direction = RIGHT;
			break;
		case 'w':
			direction = UP;
			break;
		case 's':
			direction = DOWN;
			break;
		default:
			break;
		}
	}
} // input

// handle
void handle()
{
	int prevX = tailX[0],
		prevY = tailY[0],
		prevX2,
		prevY2;
	tailX[0] = snakeX;
	tailY[0] = snakeY;
	for (int i = 1; i < tailCount; i++)
	{
		prevX2 = tailX[i];
		prevY2 = tailY[i];
		tailX.push_back(0);
		tailX[i] = prevX;
		tailY.push_back(0);
		tailY[i] = prevY;
		prevX = prevX2;
		prevY = prevY2;
	}
	// change direction
	switch (direction)
	{
	case LEFT:
		snakeX--;
		break;
	case RIGHT:
		snakeX++;
		break;
	case UP:
		snakeY--;
		break;
	case DOWN:
		snakeY++;
		break;
	default:
		break;
	}
	// ********* game over cases *********** //
		// catching tail
	for (int i = 0; i < tailCount; i++)
	{
		if (snakeX == tailX[i] && snakeY == tailY[i])
			gameOver = true;
	}
	// hitting walls
	if (snakeX <= 0 || snakeX > width - 2 || snakeY <= 0 || snakeY >= height - 2)
		gameOver = true;
	// increase tail size when eating fruit
	if (snakeX == fruitX && snakeY == fruitY)
	{
		score++;
		tailCount++;
		setFruit();
		// take care of tail
	}

} // handle

// for retries
char getChoice()
{
	system("cls");
	char choice;
	cout << "\n\n\n\n\n\n\n\n\n\n";
	cout << "       ********************** GAME OVER!!!! **********************\n\n"
		<< "       ********************** SCORE: " << score << " **************************\n\n"
		<< "       ******************** TRY AGAIN (Y/N) ? ********************\n\n"
		<< "       ...";
	cin >> choice;
	cout << endl;
	return choice;
} // getChoice
void intro()
{
	cout << "\n\n\n\n\n\n\n\n\n"
		<< "               *********************************************\n\n"
		<< "               ************* WELCOME TO SNAKE **************\n\n"
		<< "               *********Please use inputs: a,s,d,w *********\n\n";
	Sleep(3000);
}
int main()
{
	intro();

	char choice = 'y';
	srand(time(0));
	while (choice == 'Y' || choice == 'y')
	{
		choice = 'y';
		setup();
		while (!gameOver)
		{
			draw();
			Input();
			handle();
			Sleep(20);
		}
		choice = getChoice();
	}
	return 0;
}