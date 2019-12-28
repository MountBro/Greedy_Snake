#include <iostream>
#include <string>
#include <ctime>
#include <windows.h>
#include <conio.h>

using namespace std;

int food[2] = {9, 9}; //初始食物坐标
int snake[1000][2];   //蛇身坐标
int length = 1;       //初始蛇长
int headX, headY;     //蛇头坐标
int speed = 500;      //游戏难度
int score = 0;        //分数
int level = 1;        //难度等级
string name;          //玩家姓名

void gotoxy(short x, short y); //移动光标
int setdirection(int x);       //确定方向变量
void changesnake(int x);       //改变蛇身坐标
void ifchangefood();           //判断蛇是否吃到食物
void makefood();               //创造新食物
bool judgelife();              //判断蛇是否存活
void drawsnake();              //画蛇
void drawfood();               //画食物
void drawwall();               //画墙
void drawscore();              //画数据
void draw();                   //绘图

int main()
{
    SetConsoleTitle(TEXT("Greeeeeedy_Snake!"));
    system("cls");
    int po = 2; //初始方向变量
    snake[0][0] = 7;
    snake[0][1] = 7; //初始蛇头坐标
    headX = snake[0][0];
    headY = snake[0][1];
    gotoxy(30, 7);
    cout << "Welcome!";
    gotoxy(30, 9);
    cout << "Made by ltl, bettered by jhf";
    gotoxy(30, 11);
    cout << "input your user name: ";
    cin >> name;
    system("cls");
    gotoxy(30, 7);
    cout << "controling method: ";
    gotoxy(30, 9);
    cout << "W:up S:down";
    gotoxy(30, 11);
    cout << "A:left D:right";
    gotoxy(30, 13);
    cout << "Space:cease";
    gotoxy(30, 15);
    cout << "Plz maximize the window before you start!";
    gotoxy(30, 17);
    cout << "Press enter to start the game...";
    cin.get();
    cin.get();
    system("cls");
    while (true)
    {
        po = setdirection(po);
        system("cls");
        changesnake(po);
        ifchangefood();
        if (!judgelife())
            break;
        draw();
        Sleep(speed);
    }
    gotoxy(30, 10);
    cout << "Game Over!!!";
    Sleep(2000);
    gotoxy(28, 12);
    system("pause");
    return 0;
}

void gotoxy(short x, short y)
{
    COORD position = {x, y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, position);
}

int setdirection(int x)
{
    char ch;
    if (_kbhit())
    {
        ch = _getch();
        switch (ch)
        {
        case 'w':
            x = 1;
            break;
        case 's':
            x = 2;
            break;
        case 'a':
            x = 3;
            break;
        case 'd':
            x = 4;
            break;
        case ' ':
            gotoxy(37, 16);
            cout << "ceasing the game. . .";
            gotoxy(37, 18);
            system("pause");
            break;
        default:
            break;
        }
    }
    return x;
}

void changesnake(int x)
{
    switch (x)
    {
    case 1:
        headY -= 1;
        break;
    case 2:
        headY += 1;
        break;
    case 3:
        headX -= 1;
        break;
    case 4:
        headX += 1;
        break;
    default:
        break;
    }
    for (int i = length; i > 0; --i)
    {
        for (int j = 0; j < 2; ++j)
        {
            snake[i][j] = snake[i - 1][j];
        }
    }
    snake[0][0] = headX;
    snake[0][1] = headY;
}

void ifchangefood()
{
    if (snake[0][0] == food[0] && snake[0][1] == food[1])
    {
        length++;
        makefood();
        ++score;
        if (length > 5)
        {
            speed = 450;
            level = 2;
        }
        if (length > 10)
        {
            speed = 400;
            level = 3;
        }
        if (length > 15)
        {
            speed = 350;
            level = 4;
        }
        if (length > 20)
        {
            speed = 300;
            level = 5;
        }
        if (length > 25)
        {
            speed = 250;
            level = 6;
        }
        if (length > 30)
        {
            speed = 200;
            level = 7;
        }
        if (length > 35)
        {
            speed = 150;
            level = 8;
        }
        if (length > 40)
        {
            speed = 100;
            level = 9;
        }
        if (length > 45)
        {
            speed = 50;
            level = 10;
        }
    }
}

void makefood()
{
    srand((unsigned)time(NULL));
    food[0] = rand() % 30 + 2;
    food[1] = rand() % 30 + 4;
    for (int m = 0; m < length; ++m)
    {
        if (food[0] == snake[m][0] && food[1] == snake[m][1])
        {
            makefood();
            break;
        }
    }
}

bool judgelife()
{
    for (int x = 1; x < length; ++x)
    {
        if (headX == snake[x][0] && headY == snake[x][1])
        {
            return false;
        }
    }
    if (headX < 1 || headY < 3 || headX > 34 || headY > 34)
        return false;
    else
        return true;
}

void drawsnake()
{
    gotoxy(snake[0][0], snake[0][1]);
    cout << "@";
    for (int n = 1; n < length; ++n)
    {
        gotoxy(snake[n][0], snake[n][1]);
        cout << "o";
    }
}

void drawfood()
{
    gotoxy(food[0], food[1]);
    cout << "$";
}

void drawwall()
{
    gotoxy(0, 0);
    cout << "------------------------------------";
    gotoxy(16, 1);
    cout << "Greeeeeedy Snake!";
    gotoxy(0, 2);
    cout << "++++++++++++++++++++++++++++++++++++";
    gotoxy(0, 35);
    cout << "------------------------------------";
    for (int x = 0; x < 35; ++x)
    {
        gotoxy(0, x);
        cout << "|";
        gotoxy(35, x);
        cout << "|";
    }
}

void drawscore()
{
    gotoxy(37, 10);
    cout << "Score: " << score;
    gotoxy(37, 12);
    cout << "Rank: " << level;
    gotoxy(37, 14);
    cout << "User Name: " << name;
}

void draw()
{
    drawsnake();
    drawfood();
    drawwall();
    drawscore();
}