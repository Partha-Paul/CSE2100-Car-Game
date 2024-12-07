#include<windows.h>
#include<iostream>
#include <conio.h>
#include <dos.h>
#include<thread>
#include <time.h>
#define Screen_height 30
#define Screen_width 120
#define win_width 70
using namespace std;


HANDLE amar = GetStdHandle(STD_OUTPUT_HANDLE);
COORD kothay;
int flag=0;
int enemyx[3];
int enemyY[3];
int enemyflag[3];
char car[5][6] = {' ','/','/','\\','\\',' ',
                  '[',' ','=', '=',' ',']',
                  ' ','|','=','=', '|',' ',
                  '[',' ','=', '=',' ',']',
                  ' ','\\','\\', '/', '/',' '
                 };
int car_pos;
int score = 0;
thread th1;
void song();
void song1();
void welcome();
void xy(int x, int y);
void setcursor(bool vis, DWORD size);
void drawborder();
void genenemy(int ind);
void drawenemy(int ind);
void eraseenemy(int ind);
void resetenemy(int ind);
void drawcar();
void erasecar();
int colision();
void gameover();
void updateScore();
void Instructions();
void play();
void song();
void transition_typing(string s,int x,int y);
void xy(int x, int y)
{
    kothay.X = x;
    kothay.Y = y;
    SetConsoleCursorPosition(amar, kothay);
}
void setcursor(bool vis, DWORD size)
{
    if (size == 0)
    {
        size = 80;
        CONSOLE_CURSOR_INFO lpcursor;
        lpcursor.bVisible = vis;
        lpcursor.dwSize = size;
        SetConsoleCursorInfo(amar, &lpcursor);
    }
}
void drawborder()
{
    for (int i = 0; i < Screen_height; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            xy(j, i);
            cout << "~";
            xy(win_width-j, i);
            cout << "~";
        }
    }
}
void genenemy(int ind)
{
    enemyx[ind] = 15+(rand() % (38));
}

void drawenemy(int ind)
{
    if (enemyflag[ind] == 1)
    {
        SetConsoleTextAttribute(amar, 26);
        xy(enemyx[ind], enemyY[ind]);
        cout << "++++";
        xy(enemyx[ind], enemyY[ind] + 1);
        cout << " ++ ";
        xy(enemyx[ind], enemyY[ind] + 2);
        cout << "++++";
        xy(enemyx[ind], enemyY[ind] + 3);
        cout << "\\\\//";
    }
}
void eraseenemy(int ind)
{
    if (enemyflag[ind] == true)
    {
        SetConsoleTextAttribute(amar, 19);
        xy(enemyx[ind], enemyY[ind]);
        cout << "    ";
        xy(enemyx[ind], enemyY[ind] + 1);
        cout << "    ";
        xy(enemyx[ind], enemyY[ind] + 2);
        cout << "    ";
        xy(enemyx[ind], enemyY[ind] + 3);
        cout << "    ";
    }
}
void resetenemy(int ind)
{
    eraseenemy(ind);
    enemyY[ind] = 1;
    genenemy(ind);
}
void drawcar()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            xy(j + car_pos, i + 25);
            SetConsoleTextAttribute(amar, 100);
            cout << car[i][j];
        }
    }
}
void erasecar()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            xy(j + car_pos, i + 25);
            SetConsoleTextAttribute(amar, 19);
            cout << " ";
        }
    }
}
int colision()
{
    if (enemyY[0] + 4 >= 25)
    {
        if ((enemyx[0] >= car_pos && enemyx[0] <= car_pos + 6) || (enemyx[0] + 4 >= car_pos && enemyx[0] + 4 <= car_pos + 6))
        {
            Beep(2637,300);
            return 1;
        }
    }
    if (enemyY[1] + 4 >= 25)
    {
        if ((enemyx[1] >= car_pos && enemyx[1] <= car_pos + 6) || (enemyx[1] + 4 >= car_pos && enemyx[1] + 4 <= car_pos + 6))
        {
            Beep(2637,300);
            return 1;
        }
    }
    return 0;
}
void gameover()
{
    system("cls");
    int n=30,m=120;
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            SetConsoleTextAttribute(amar, 100);
            xy(i,j);
            cout<<"   ";
        }
        Sleep(5);
    }
    for(int i=30; i>=5; i--)
    {
        xy(38,i-1);
        cout<<"   ";
        xy(38, i);
        cout << "------xxxxxxGAMEOVERxxxxxx------" ;
        xy(38, i+1);
        cout << "                                 ";
        Sleep(20);
    }
    for(int i=30; i>=7; i--)
    {
        xy(50,i-1);
        cout<<"   ";
        xy(50, i);
        cout << "Score:" ;
        xy(56,i);
        cout << score;
        xy(50, i+1);
        cout << "            ";
        Sleep(20);
    }
    string s="Press any key to go back to menu...";
    transition_typing(s,38,9);
    getch();
}
void updateScore()
{
    xy(win_width + 7, 5);
    SetConsoleTextAttribute(amar, FOREGROUND_RED | BACKGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "Score:" ;
    SetConsoleTextAttribute(amar, BACKGROUND_RED | FOREGROUND_INTENSITY);
    cout<<score << "\n";
}
void Instructions()
{
    system("cls");
    for(int i=0; i<120; i+=4)
    {
        SetConsoleTextAttribute(amar,BACKGROUND_RED);
        xy(i,0);
        cout<<" ";
        xy(i+1,0);
        cout<<" ";
        SetConsoleTextAttribute(amar,100);
        xy(i+2,0);
        cout<<" ";
        xy(i+3,0);
        cout<<" ";
        SetConsoleTextAttribute(amar,BACKGROUND_RED);
        xy(i,29);
        cout<<" ";
        xy(i+1,29);
        cout<<" ";
        SetConsoleTextAttribute(amar,100);
        xy(i+2,29);
        cout<<" ";
        xy(i+3,29);
        cout<<" ";
    }
    for(int i=0; i<30; i+=2)
    {
        SetConsoleTextAttribute(amar,BACKGROUND_RED);
        xy(0,i);
        cout<<" ";
        xy(1,i);
        cout<<" ";
        SetConsoleTextAttribute(amar,100);
        xy(0,i+1);
        cout<<" ";
        xy(1,i+1);
        cout<<" ";
        SetConsoleTextAttribute(amar,BACKGROUND_RED);
        xy(119,i);
        cout<<" ";
        xy(118,i);
        cout<<" ";
        SetConsoleTextAttribute(amar,100);
        xy(119,i+1);
        cout<<" ";
        xy(118,i+1);
        cout<<" ";
    }
    SetConsoleTextAttribute(amar, FOREGROUND_GREEN | BACKGROUND_BLUE);
    int n = 3;
    while (1)
    {
        xy((n++), 5);
        cout << " Instructions";
        xy((n-1), 6);
        cout<<" ------------\n\n";
        if (n == 50)
        {
            break;
        }
        Sleep(25);
    }
    string s= "1. Press A and D to move left and right OR Use Left and Right Arrow...";
    transition_typing(s,3,7);
    s= "2. Press Escape to exit...";
    transition_typing(s,3,9);
    s= "3. The speed of the game increases with every 15 points you get...";
    transition_typing(s,3,11);
    s= "Press any key to go to menu...";
    transition_typing(s,40,15);
    getch();
}
void play()
{
    car_pos = win_width / 2;
    score = 0;
    enemyflag[0] = 1;
    enemyflag[1] = 0;
    enemyY[0] = enemyY[1] = 1;
    system("cls");
    drawborder();
    updateScore();
    xy(win_width + 7, 3);
    SetConsoleTextAttribute(amar, 22);
    cout << "Car game                 ";
    xy(win_width + 6, 4);
    cout << "----------               ";
    xy(win_width + 6, 6);
    cout << "---------                ";
    xy(win_width + 8, 12);
    SetConsoleTextAttribute(amar, 100);
    cout << "Control";
    xy(win_width + 7, 13);
    SetConsoleTextAttribute(amar, 22);
    cout << "---------";
    xy(win_width + 4, 14);
    SetConsoleTextAttribute(amar, 100);
    cout << "A-key or  Left  Arrow===>Left";
    xy(win_width + 4, 15);
    SetConsoleTextAttribute(amar, 100);
    cout << "D-key or Right Arrow===>Right";
    xy(20, 5);
    SetConsoleTextAttribute(amar, 22);
    cout << "Press any key to start...";
    getch();
    thread th1(song);
    xy(18, 5);
    SetConsoleTextAttribute(amar, BACKGROUND_BLUE);
    cout << "                            ";
    genenemy(0);
    genenemy(1);
    int speed = 50;
    int limit = 15;
    while (1)
    {
        if (kbhit())
        {
            char ch = getch();
            if (ch == 'a' || ch == 'A'|| ch==75)
            {
                if (car_pos > 16)
                {
                    car_pos -= 5;
                }
            }
            if (ch == 'd' || ch == 'D' ||ch==77)
            {
                if (car_pos < 48)
                {
                    car_pos += 5;
                }
            }
            if (ch == 27)
            {
                welcome();
            }
        }
        drawcar();
        drawenemy(0);
        drawenemy(1);
        if (colision() == 1)
        {
            gameover();
            welcome();
        }
        if (score >= limit)
        {
            limit += 15;
            if (speed >= 12)
                speed -= 15;
        }
        Sleep(speed);
        erasecar();
        eraseenemy(0);
        eraseenemy(1);
        int i = rand() % 10;
        if (i < 6)
        {
            i = 15 - i;
        }
        if (enemyY[0] == i)
        {
            if (enemyflag[1] == 0)
            {
                enemyflag[1] = 1;
            }
        }
        if (enemyflag[0] == 1)
        {
            enemyY[0] += 1;
        }
        if (enemyflag[1] == 1)
        {
            enemyY[1] += 1;
        }
        if (enemyY[0] > Screen_height - 4)
        {
            resetenemy(0);
            score++;
            updateScore();
        }
        if (enemyY[1] > Screen_height - 4)
        {
            resetenemy(1);
            score++;
            updateScore();
        }
    }
}
void song()
{
    PlaySound("C:\\Users\\parth\\Downloads\\retro-city-14099.wav",NULL,SND_ALIAS);
    return;
}
void song1()
{
    PlaySound("welcome.wav",NULL,SND_ALIAS);
    return;
}
void transition_typing(string s,int x,int y)
{
    for(int i=0,m=x; i<s.length(); i++,m++)
    {
        xy(m,y);
        cout<<s[i];
        Sleep(30);
    }
}
void welcome()
{
    system("cls");
    setcursor(0, 0);
    do
    {
        SetConsoleTextAttribute(amar, 20);
        system("cls");
        for(int i=0; i<120; i+=4)
        {
            SetConsoleTextAttribute(amar,BACKGROUND_RED);
            xy(i,0);
            cout<<" ";
            xy(i+1,0);
            cout<<" ";
            SetConsoleTextAttribute(amar,100);
            xy(i+2,0);
            cout<<" ";
            xy(i+3,0);
            cout<<" ";
            SetConsoleTextAttribute(amar,BACKGROUND_RED);
            xy(i,29);
            cout<<" ";
            xy(i+1,29);
            cout<<" ";
            SetConsoleTextAttribute(amar,100);
            xy(i+2,29);
            cout<<" ";
            xy(i+3,29);
            cout<<" ";
        }
        for(int i=0; i<30; i+=2)
        {
            SetConsoleTextAttribute(amar,BACKGROUND_RED);
            xy(0,i);
            cout<<" ";
            xy(1,i);
            cout<<" ";
            SetConsoleTextAttribute(amar,100);
            xy(0,i+1);
            cout<<" ";
            xy(1,i+1);
            cout<<" ";
            SetConsoleTextAttribute(amar,BACKGROUND_RED);
            xy(119,i);
            cout<<" ";
            xy(118,i);
            cout<<" ";
            SetConsoleTextAttribute(amar,100);
            xy(119,i+1);
            cout<<" ";
            xy(118,i+1);
            cout<<" ";
        }
        xy(50, 10);
        SetConsoleTextAttribute(amar, 22);
        cout << "   Car Game";
        xy(50, 12);
        SetConsoleTextAttribute(amar, 20);
        cout << "1.Start Game";
        xy(50, 14);
        SetConsoleTextAttribute(amar, 26);
        cout << "2.Instructions";
        xy(50, 16);
        SetConsoleTextAttribute(amar, 31);
        cout << "3.Quit";
        char ch = getch();
        if (ch == '1')
        {
            play();
        }
        else if (ch == '2')
        {
            Instructions();
        }
        else if (ch == '3')
        {
            exit(0);
        }
    }
    while (1);
}
int main()
{
    system("cls");
    setcursor(0, 0);
    SetConsoleTextAttribute(amar, 95);
    system("cls");
    for(int i=0; i<120; i+=4)
    {
        SetConsoleTextAttribute(amar,BACKGROUND_RED);
        xy(i,0);
        cout<<" ";
        xy(i+1,0);
        cout<<" ";
        SetConsoleTextAttribute(amar,100);
        xy(i+2,0);
        cout<<" ";
        xy(i+3,0);
        cout<<" ";
        SetConsoleTextAttribute(amar,BACKGROUND_RED);
        xy(i,29);
        cout<<" ";
        xy(i+1,29);
        cout<<" ";
        SetConsoleTextAttribute(amar,100);
        xy(i+2,29);
        cout<<" ";
        xy(i+3,29);
        cout<<" ";
        Sleep(10);
    }
    for(int i=0; i<30; i+=2)
    {
        SetConsoleTextAttribute(amar,BACKGROUND_RED);
        xy(0,i);
        cout<<" ";
        xy(1,i);
        cout<<" ";
        SetConsoleTextAttribute(amar,100);
        xy(0,i+1);
        cout<<" ";
        xy(1,i+1);
        cout<<" ";
        SetConsoleTextAttribute(amar,BACKGROUND_RED);
        xy(119,i);
        cout<<" ";
        xy(118,i);
        cout<<" ";
        SetConsoleTextAttribute(amar,100);
        xy(119,i+1);
        cout<<" ";
        xy(118,i+1);
        cout<<" ";
        Sleep(30);
    }
    xy(50, 10);
    SetConsoleTextAttribute(amar, 22);
    cout << "   Car Game";
    xy(50, 12);
    SetConsoleTextAttribute(amar, 20);
    cout << "1.Start Game";
    xy(50, 14);
    SetConsoleTextAttribute(amar, 26);
    cout << "2.Instructions";
    xy(50, 16);
    SetConsoleTextAttribute(amar, 31);
    cout << "3.Quit";
    song1();
    welcome();
}

