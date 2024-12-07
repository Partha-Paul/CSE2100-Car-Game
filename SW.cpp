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
void play(){
        system("cls");
        setcursor(0, 0);
        SetConsoleTextAttribute(amar,BACKGROUND_RED);
        xy(50,15);
        cout<<"Press a,s,d,w to move the 'Hellow World' ";
        getch();
        xy(50,15);
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
        int Opn=0;
        int DB=0;
        while(1){
        char k=getch();
        xy(DB,Opn);
        SetConsoleTextAttribute(amar,100);
        cout<<"           ";
        if(k=='a'){
                DB=(DB-1)%120;
                if(DB<0){
                    DB=0;
                }

        }
        else if(k=='d'){
            DB=(DB+1)%120;
        }
        else if(k=='w'){
             Opn=(Opn-1)%30;
                if(Opn<0){
                    Opn=0;
                }
        }
        else if(k=='s'){
             Opn=(Opn+1)%30;
        }
        else{
            break;
        }
        SetConsoleTextAttribute(amar,BACKGROUND_RED);

        xy(DB,Opn);
        cout<<"Hello World";
        }

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

    song1();

    play();
}

