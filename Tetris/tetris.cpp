#include <graphics.h>
#include<iostream>
#include <conio.h>
#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")
using namespace std;

#define num_X    20
#define num_Y    30
#define BLOCK_WIDTH 25
#define X_origin 20
#define Y_origin 20
#define windowWidth 900
#define windowHeight 800

int blocks[7][4][4][2] = {
    //"T"型方块,BLUE,T
    {{{0, 0}, {-1, 0}, {0, -1}, {1, 0}},
     {{0, 0}, {0, -1}, {1, 0}, {0, 1}},
     {{0, 0}, {1, 0}, {0, 1}, {-1, 0}},
     {{0, 0}, {0, 1}, {-1, 0}, {0, -1}}},
     //反"Z"型方块,GREEN,Q
     {{{0, 0}, {-1, 0}, {0, -1}, {1, -1}},
      {{0, 0}, {0, -1}, {1, 0}, {1, 1}},
      {{0, 0}, {1, 0}, {0, 1}, {-1, 1}},
      {{0, 0}, {0, 1}, {-1, 0}, {-1, -1}}},
      //"Z"型方块,CYAN,Z
      {{{0, 0}, {-1, -1}, {0, -1}, {1, 0}},
       {{0, 0}, {1, -1}, {1, 0}, {0, 1}},
       {{0, 0}, {1, 1}, {0, 1}, {-1, 0}},
       {{0, 0}, {-1, 1}, {-1, 0}, {0, -1}}},
       //"一"字型方块,RED,I
       {{{0, 0}, {-2, 0}, {-1, 0}, {1, 0}},
        {{0, 0}, {0, -2}, {0, -1}, {0, 1}},
        {{0, 0}, {2, 0}, {1, 0}, {-1, 0}},
        {{0, 0}, {0, 2}, {0, 1}, {0, -1}}},
        //"田"字型方块,MAGENTA,M
        {{{0, 0}, {-1, 0}, {-1, -1}, {0, -1}},
         {{0, 0}, {0, -1}, {1, -1}, {1, 0}},
         {{0, 0}, {1, 0}, {1, 1}, {0, 1}},
         {{0, 0}, {0, 1}, {-1, 1}, {-1, 0}}},
         //"L"型方块,BROWN,L
         {{{0, 0}, {-1, 0}, {1, 0}, {1, -1}},
          {{0, 0}, {0, -1}, {0, 1}, {1, 1}},
          {{0, 0},{1, 0}, {-1, 0}, {-1, 1}},
          {{0, 0}, {0, 1}, {0, -1}, {-1, -1}}},
          //反"L"型方块,YELLOW,J
          {{{0, 0}, {-1, 0}, {1, 0}, {1, 1}},
           {{0, 0}, {0, -1}, {0, 1}, {-1, 1}},
           {{0, 0}, {1, 0}, {-1, 0}, {-1, -1}},
           {{0, 0}, {0, 1}, {0, -1}, {1, -1}}}
};

//Set block color.
int color[7] = { BLUE ,GREEN ,CYAN ,RED ,MAGENTA ,BROWN ,YELLOW };
int block_color[7] = { 1,2,3,4,5,6,7 };
int current_x, current_y;
int type_all;
int rotate_all;
int LandedBlock[num_X][num_Y] = { -1 };
int LandFlag = 0;
int BLOCK_COUNT = 0;
int score = 0;
int type_new, rotate_new;
int clearFlag = 0;


// 画出单元格.
void drawUnitBlock(int x, int y, int color)
{
    int left, top, right, bottom;
    left = X_origin + x * BLOCK_WIDTH;
    top = Y_origin + y * BLOCK_WIDTH;
    right = left + BLOCK_WIDTH;
    bottom = top + BLOCK_WIDTH;
    setfillcolor(color);
    setlinecolor(WHITE);
    setlinestyle(PS_SOLID | PS_JOIN_ROUND, 3);
    fillcircle(left + BLOCK_WIDTH / 2, top + BLOCK_WIDTH / 2, BLOCK_WIDTH / 2);
    //fillrectangle(left, top, right, bottom);
}

//提前画出下一个方块
void drawnewblock(int t, int r, int c) {
    int newblock = X_origin + BLOCK_WIDTH * num_X + 50;
    setlinecolor(WHITE);
    rectangle(newblock, Y_origin, newblock + 300, Y_origin + 300);
    for (int i = 0; i < 4; i++) {

        int x = blocks[t][r][i][0];
        int y = blocks[t][r][i][1];

        int left, top, right, bottom;
        left = X_origin + x * 40 + 680;
        top = Y_origin + y * 40 + 100;
        right = left + 40;
        bottom = top + 40;
        setfillcolor(color[type_new]);
        setlinecolor(WHITE);
        fillcircle(left + BLOCK_WIDTH / 2, top + BLOCK_WIDTH / 2, 20);
        //fillrectangle(left, top, right, bottom);
       //drawUnitBlock((newblock + 150) / BLOCK_WIDTH + x, 3 + y, c);
    }
}

//画出新的位置的俄罗斯方块
void drawTetrisBlock(int x, int y, int iType, int iRotate, int color)
{
    int new_X, new_Y;
    for (int i = 0; i < 4; i++)
    {
        new_X = x + blocks[iType][iRotate][i][0];
        new_Y = y + blocks[iType][iRotate][i][1];
        drawUnitBlock(new_X, new_Y, color);
    }
}

//创造blocks
void genBlock()
{
    BLOCK_COUNT++;
    time_t t;
    time(&t);
    srand((unsigned int)t);
    type_new = rand() % 7;
    rotate_new = rand() % 4;
}

void drawgenblock() {
    time_t t1;
    time(&t1);
    srand((unsigned int)t1);
    current_x = 4;
    //current_x = 1 + rand() % (18 - 1 + 1);
    current_y = 1;

    drawTetrisBlock(current_x, current_y, type_all, rotate_all, color[type_all]);
}


//画背景
void drawBackground()
{
    cleardevice();

    //setbkcolor(RGB(138, 43, 226));
    IMAGE img;
    loadimage(&img, "bk.jpg", 900, 800);
    putimage(0, 0, &img);

    
    setlinecolor(WHITE);
    rectangle(X_origin, Y_origin+20, X_origin + BLOCK_WIDTH * num_X, Y_origin + BLOCK_WIDTH * num_Y);
    for (int i = 0; i <= num_X; ++i)
    {
        for (int j = 0; j <= num_Y; ++j)
        {
            if (LandedBlock[i][j] > 0) {
                drawUnitBlock(i, j, color[LandedBlock[i][j] - 1]);
            }
        }
    }
    void drawnewblock(int t, int r, int c);
    drawnewblock(type_new, rotate_new, color[type_new]);

    int newblock = X_origin + BLOCK_WIDTH * num_X + 50;
    setlinecolor(WHITE);
    rectangle(newblock, Y_origin, newblock + 300, Y_origin + 300);

    settextstyle(60, 0, "楷体");
    setbkmode(TRANSPARENT);
    settextcolor(WHITE);
    outtextxy(550, 350, "Score:");


    bool clearcheck(int Rowld);
    TCHAR s[5];

    for (int i = 0; i < num_Y; i++)
    {
        if (clearcheck(i))
        {
            score += 10;

            _stprintf_s(s, _T("%d"), score);
            outtextxy(600, 450, s);


        }
        else
        {
            _stprintf_s(s, _T("%d"), score);
            outtextxy(600, 450, s);
        }
    }
}

void landBlock(int x, int y, int Type, int Rotate)
{
    int CoordX, CoordY;
    for (int j = 0; j < 4; j++)
    {
        CoordX = x + blocks[Type][Rotate][j][0];
        CoordY = y + blocks[Type][Rotate][j][1];
        LandedBlock[CoordX][CoordY] = block_color[Type];
    }
    LandFlag = 1;
}


bool canGoLeft(int x, int y, int iType, int iRotate)
{
    int i;
    int willBeX, willBeY;
    for (i = 0; i < 4; i++)
    {
        willBeX = x + blocks[iType][iRotate][i][0] - 1;
        willBeY = y + blocks[iType][iRotate][i][1];
        if (willBeX < 0) {
            return false;
        }
        if (LandedBlock[willBeX][willBeY] > 0) {

            return false;
        }
    }
    return true;
}

bool canGoRight(int x, int y, int Type, int Rotate)
{
    int i;
    int willBeX, willBeY;
    for (i = 0; i < 4; i++)
    {
        willBeX = x + blocks[Type][Rotate][i][0] + 1;
        willBeY = y + blocks[Type][Rotate][i][1];
        if (willBeX >= num_X) {
            return false;
        }
        if (LandedBlock[willBeX][willBeY] > 0) {
            return false;
        }

    }
    return true;
}



bool canFall(int x, int y, int Type, int Rotate)
{
    int i;
    int willBeX, willBeY;
    for (i = 0; i < 4; i++)
    {
        willBeX = x + blocks[Type][Rotate][i][0];
        willBeY = y + blocks[Type][Rotate][i][1] + 1;

        if (willBeY >= num_Y || LandedBlock[willBeX][willBeY] > 0) {
            return false;
        }

    }
    return true;
}

bool canRotate(int x, int y, int Type, int Rotate)
{
    int i;
    int willBeX, willBeY;
    int NewRotate = Rotate + 1;
    if (NewRotate > 3)
    {
        NewRotate = 0;
    }
    for (i = 0; i < 4; i++)
    {
        willBeX = x + blocks[Type][NewRotate][i][0];
        willBeY = y + blocks[Type][NewRotate][i][1];
        if (willBeX < 0 || willBeX >= num_X || willBeY < 0 || willBeY >= num_Y) {
            return false;
        }
        if (LandedBlock[willBeX][willBeY] > 0) {
            return false;
        }
    }
    return true;
}
void moveBlock(char input)
{
    if (input == 'a')
    {
        if (canGoLeft(current_x, current_y, type_all, rotate_all))
        {
            current_x--;
            drawTetrisBlock(current_x, current_y, type_all, rotate_all, color[type_all]);
        }

    }
    else if (input == 'd')
    {

        if (canGoRight(current_x, current_y, type_all, rotate_all))
        {
            current_x++;
            drawTetrisBlock(current_x, current_y, type_all, rotate_all, color[type_all]);
        }

    }
    else if (input == 's')
    {
        if (canFall(current_x, current_y, type_all, rotate_all))
        {
            while (canFall(current_x, current_y, type_all, rotate_all)) {
                current_y++;
            }
            drawTetrisBlock(current_x, current_y, type_all, rotate_all, color[type_all]);


        }
        else
        {
            landBlock(current_x, current_y, type_all, rotate_all);
        }

    }
    else if (input == 'w')
    {
        if (canRotate(current_x, current_y, type_all, rotate_all))
        {
            rotate_all++;
            if (rotate_all > 3)
            {
                rotate_all = 0;
            }
            drawTetrisBlock(current_x, current_y, type_all, rotate_all, color[type_all]);
        }
    }
}
void removeRow(int Rowld)
{
    for (int rowX = 0; rowX < num_X; rowX++)
    {
        for (int rowY = Rowld; rowY > 0; rowY--)
        {
            LandedBlock[rowX][rowY] = LandedBlock[rowX][rowY - 1];
        }
    }
}

//判断消行
bool clearcheck(int Rowld)
{
    for (int i = 0; i < num_X; i++)
    {
        if (LandedBlock[i][Rowld] <= 0)
        {
            return false;
        }
    }
    return true;
}
//判断结束
int gameover() {
    int flag = 0;
    for (int i = 0; i < num_X; i++)
    {
        if (LandedBlock[i][0] > 0) {
            flag = 1;
            break;
        }
    }
    return flag;
}

//移动方格
void removeWoleblocks()
{
    for (int i = 0; i < num_Y; i++)
    {
        if (clearcheck(i))
        {
            clearFlag = 1;
            removeRow(i);
        }
    }

}


void autoMove()
{
    if (canFall(current_x, current_y, type_all, rotate_all))
    {
        current_y++;
        Sleep(300);
        drawTetrisBlock(current_x, current_y, type_all, rotate_all, color[type_all]);
    }
    else {
        landBlock(current_x, current_y, type_all, rotate_all);
    }
}

void start() {
    initgraph(windowWidth, windowHeight);
    setbkcolor(WHITE);
    cleardevice();
    IMAGE img1;
    loadimage(&img1, "bk2.jpg", 900, 800);
    putimage(0, 0, &img1);
   

    setbkmode(TRANSPARENT);
    settextcolor(WHITE);
    settextstyle(100, 0, "楷体");
    outtextxy(200, 200, "TETRIS");
    settextstyle(70, 0, "楷体");
    outtextxy(300, 450, "start game");

    mciSendString("open bgm/m.mp3 alias song", NULL, 0, NULL);
    mciSendString("play song repeat", NULL, 0, NULL);
    system("pause");

    _getch();
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    settextstyle(50, 0, "楷体");
    outtextxy(330, 550, "规则说明");
    settextstyle(30, 0, "楷体");
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    settextstyle(30, 0, "楷体");
    outtextxy(200, 600, "操纵键盘上的 W A S D");
    outtextxy(180, 630, "W:改变形状 A:左 S:直接下落  D：右");

    _getch();
    closegraph();
}
void initialize() {
    for (int i = 0; i < num_X; i++) {
        for (int j = 0; j < num_Y; j++) {
            LandedBlock[i][j] = -1;
        }

    }
}
int main()
{
    start();

    initgraph(windowWidth, windowHeight);
    drawBackground();
    

    genBlock();
    drawgenblock();

    genBlock();
    BLOCK_COUNT--;
    drawnewblock(type_new, rotate_new, color[type_new]);


    char input;
    while (1)
    {

        BeginBatchDraw();


        //键盘输入
        if (_kbhit())
        {

            mciSendString(_T("close down"), NULL, 0, NULL);
            input = _getch();

            if (input != 'q')
            {
                moveBlock(input);
                if (input == 's') {
                    mciSendString(_T("open bgm/ding.mp3 alias down"), NULL, 0, NULL);
                    mciSendString(_T("play down"), NULL, 0, NULL);
                }

                
                 

                 //没落地
                if (LandFlag != 1)
                {
                    removeWoleblocks();
                    drawBackground();
                    drawnewblock(type_new, rotate_new, color[type_new]);
                    drawTetrisBlock(current_x, current_y, type_all, rotate_all, color[type_all]);

                }
                //落地
                else
                {

                    mciSendString(_T("close down"), NULL, 0, NULL);
                    type_all = type_new;
                    rotate_all = rotate_new;
                    drawgenblock();
                    removeWoleblocks();


                    LandFlag = 0;
                    genBlock();
                    drawBackground();

                }


            }
            else if (input == 'q') {
                break;
            }


            FlushBatchDraw();
        }
        //没敲键盘
        else
        {

            if (LandFlag != 1) {
                autoMove();
                drawBackground();
                drawnewblock(type_new, rotate_new, color[type_new]);
                drawTetrisBlock(current_x, current_y, type_all, rotate_all, color[type_all]);
            }
            else {
                type_all = type_new;
                rotate_all = rotate_new;
                drawgenblock();
                LandFlag = 0;
                autoMove();
                removeWoleblocks();
                drawBackground();
                genBlock();

            }

        }

        if (gameover() == 1) {

            if (_kbhit()) break;
            // 设置窗口弹窗
            HWND hand = GetHWnd();	// 获取图形窗口的句柄
            int ResultMB = MessageBox(hand, "你想再来一次吗", "GAMEOVER", MB_OKCANCEL);
            // 点击不同按钮之后的不同操作
            if (IDOK == ResultMB) {
                initialize();
                drawBackground();
                continue;
            }
            if (IDCANCEL == ResultMB) {
              
                initgraph(900, 800);
                IMAGE img1;
                loadimage(&img1, "bk2.jpg", 900, 800);
                putimage(0, 0, &img1);

                setbkmode(TRANSPARENT);
                settextcolor(RED);
                settextstyle(100, 0, "楷体");
                outtextxy(250, 250, "GAME OVER");
                settextstyle(100, 0, "楷体");
                outtextxy(150, 400, "YOUR SCORE IS");

                TCHAR s[5];
                _stprintf_s(s, _T("%d"), score);
                outtextxy(400, 500, s);
                FlushBatchDraw();
                break;
            }
        }


        EndBatchDraw();
    }
    _getch();
    closegraph();
    return 0;
}
