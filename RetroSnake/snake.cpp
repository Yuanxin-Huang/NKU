#include <graphics.h>
#include <conio.h>
#include<iostream>
#include<windows.h>
#include<random>
#include <time.h>
#include<vector>
#include<stdio.h>
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")
using namespace std;
int toDir;
/*�����:f�����ȡ���׼����x��y�����ڿ�ȡ��߶ȵ�*/

#define  block_width 22
#define  x_origin 30
#define  y_origin 50
#define x_border 41
#define y_border 21
#define windowWidth 1000
#define windowHeight 700
#define DIR_UP 1
#define DIR_DOWN 2
#define DIR_LEFT 3
#define DIR_RIGHT 4

/*������ĳ�ʼ������*/
int length = 3;
int block[4000][2];
/*�����ߵ��������*/
//void gensnake() {
//	time_t t1;
//	time(&t1);
//	srand((unsigned int)t1);
//	int x = (rand() % (37 - 1)) + 1;
//	int y= (rand() % (17 - 1)) + 1;
//	snake[0][0] = x;
//	snake[0][1] = y;
//	snake[1][0] = x++;
//	snake[1][1] = y;
//	snake[2][0] = x++;
//	snake[2][1] = y;
//}
int snake[1000][2] = {
	{9,7},
	{8,7},
	{7,7},
	{0}
};

/*����������ĵ�Ԫ��*/
void drawUnitBlock(int x)
{
	int left, top, right, bottom;
	left = x_origin + block_width * snake[x][0];
	top= y_origin + block_width * snake[x][1];
	right = left + block_width;
	bottom = top + block_width;

	fillrectangle(left, top, right, bottom);

	int left1, top1;
	left1 = x_origin + block_width * snake[0][0];
	top1 = y_origin + block_width * snake[0][1];

	IMAGE img1;
	loadimage(&img1, _T("starhead.jpg"), 25, 25);
	putimage(left1, top1, &img1);

	IMAGE img2;
	loadimage(&img2, _T("star.jpg"), 20, 20);
	putimage(left, top, &img2);

}

/*������������*/
void drawSnake()
{
	setlinestyle(PS_DASH | PS_ENDCAP_ROUND, 1);
	setlinecolor(WHITE);
	int i = 0,j=0;
	for (i = 0; i < length;i++){
		drawUnitBlock(i);
	}
}
/*�滭����*/
	/*ÿ����Ԫ�������*/
	void drawEveryBlock(int x, int y) 
	{
		int left, top, right, bottom;
		left = x_origin + block_width * block[x][0];
		top = y_origin + block_width * block[x][1];
		right = left + block_width;
		bottom = top + block_width;

		rectangle(left, top, right, bottom);
	}
	/*������Ԫ��*/
	void drawblock()
	{
		setlinestyle(PS_DASH | PS_ENDCAP_ROUND, 1);
		setlinecolor(WHITE);
		for (int i = 0; i <40;++i)
		{
			for (int j = 0; j <20; ++j)
			{
				block[i][0] = i+1;
				block[i][1] = j+1;
				drawEveryBlock(i, j);
			}
		}
	}
	/*�����߿�/ǽ*/
	void drawframe() 
	{
		setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, 6);
		setlinecolor(YELLOW);
		rectangle(x_origin+ block_width, y_origin+ block_width,
			x_origin+ block_width*41, y_origin+ block_width*21);
	}
	/*������*/
	void drawbackground() 
	{
		cleardevice();
		IMAGE back;
		loadimage(&back, _T("background.jpg"), 1020, 800);
		putimage(0, 0, &back);

		settextstyle(60,0,"����");
		setbkmode(TRANSPARENT);
		settextcolor(WHITE);
		outtextxy(300,520,"Your Score");

		drawblock();
		drawframe();
	}

	void moveSnake() 
	{
		/*��ȡ�����WASD�����ı��ߵ����꣬�ƶ���*/
		char direction = _getch();
		for (int i = length-1; i > 0; i--) {
			snake[i][0] = snake[i - 1][0];
			snake[i][1] = snake[i - 1][1];
		}

		switch (direction)
		{
		case 'w':  
			if (toDir != DIR_DOWN)  
			{
				snake[0][1]--;
				toDir = DIR_UP;
				break;
			}
		case 's':   
			if (toDir != DIR_UP)   
			{
				snake[0][1]++;
				toDir = DIR_DOWN;
				break;
			}
		case 'a':    
			if (toDir != DIR_RIGHT)   
			{
				snake[0][0]--;
				toDir = DIR_LEFT;
				break;
			}
		case 'd':    
			if (toDir != DIR_LEFT)   
			{
				snake[0][0]++;
				toDir = DIR_RIGHT;
				break;
			}
		default: break;
		}
	}
	/*�Զ��ƶ�*/
	void autoMove() 
	{
		for (int i = length-1; i > 0; i--) 
		{
			snake[i][0] = snake[i - 1][0];
			snake[i][1] = snake[i - 1][1];
		}
		switch (toDir) 
		{
		case DIR_UP:
			snake[0][1]--; break;
		case DIR_DOWN:
			snake[0][1]++; break;
		case DIR_LEFT:
			snake[0][0]--; break;
		case DIR_RIGHT:
			snake[0][0]++; break;
		default: break;
		}
		drawSnake();
	}
	/*�ж����Ƿ�ײ��ǽ���������Լ�������*/
	bool checkCollision()
	{

		/*ǽ�������ж�*/
		if (snake[0][0] >=40 || snake[0][1] >=20 || snake[0][0] <=1 || snake[0][1] <=1) {
			return false;
		}
		/*����������ж�*/
		for (int i=1;i<length;i++)
		{
			if (snake[0][0]== snake[i][0]&& snake[0][1]== snake[i][1])
			{
				return false;
			}
		}
		return true;
	}

	int eat = 0;//0��ʾʳ��δ����
	int food_x;
	int food_y;
	/*�����������ʳ�������*/
	void drawFood(int food_x,int food_y) 
	{
		setfillcolor(YELLOW);
		fillrectangle(food_x * block_width + x_origin, food_y * block_width + y_origin,
			(food_x + 1) * block_width + x_origin, (food_y + 1) * block_width + y_origin);
	}
	void generateFood() 
	{
		time_t t;
		time(&t);
		srand((unsigned int)t);
		food_x = (rand() % (40-2))+2;//���ɷ�Χ��2~40  (rand()%(b-a))+a
		food_y = (rand() % (20 - 2)) + 2;
		int flag = 0;//�жϱ�־��Ϊ1ʱ����ʳ��
		/*����ʳ�����겻���ߵ������غ�*/
		for (int i = 0; i<length; i++)
		{
			if (food_x != snake[i][0] && food_y != snake[i][1]) 
			{
				flag = 1;
			}
		}
		if (flag) 
		{
			drawFood(food_x, food_y);
		}

	}/*�ж�ʳ���Ƿ��߳ԣ�����ͷ�����ʳ�������غ�Ϊ��׼*/
	
	int eatFood()
	{
		eat = 0;
		if (snake[0][0] == food_x && snake[0][1] == food_y) {
			eat = 1;//��ʾʳ�ﱻ��
		}
		return eat;
	}
	/*�����ߵĳ���*/
	void increaseLength()
	{
		int tailX, tailY;
		if (eatFood() == 1) {
			tailX = snake[length - 1][0];
			tailY = snake[length - 1][1];
			autoMove();
			snake[length][0] = tailX;
			snake[length][1] = tailY;
			length++;
			drawSnake();
		}
	}
	/*�ж�ʳ���Ƿ񱻳�*/
	int score = 0;
	void checkFood() {

		
		TCHAR s[5];

		if (eatFood() == 1)
		{
			increaseLength();
			generateFood();
			drawbackground();
			drawSnake();
			drawFood(food_x, food_y);
			score++;
			_stprintf_s(s, _T("%d"), score);
			outtextxy(400, 580, s);

		}
		else
		{
			drawFood(food_x, food_y);
			drawSnake();
			_stprintf_s(s, _T("%d"), score);
			outtextxy(400, 580, s);
		}
	}
	/*��Ϸʧ�ܽ��������*/
	void gameover() 
	{
		mciSendString(_T("close ./bgm2.mp3 "), NULL, NULL, NULL);
		mciSendString(_T("open ./loser.mp3 alias bgm"), NULL, NULL, NULL);
		mciSendString(_T("play ./loser.mp3 repeat"), NULL, NULL, NULL);

		initgraph(600, 800);
		SetWindowText(GetHWnd(), "error");
		IMAGE img5;
		loadimage(&img5, "lose.jpg", 600, 800);
		putimage(0, 0, &img5);

		setbkmode(TRANSPARENT);
		settextcolor(WHITE);
		settextstyle(50, 0, "����");
		outtextxy(80, 60, "��������������ʧ���ˣ�");
		outtextxy(70, 110, "��Ҫ���٣�");
		outtextxy(70, 160, "��������һ�Σ�");
		setbkmode(TRANSPARENT);
		settextcolor(RED);
		
		setbkmode(TRANSPARENT);
		settextcolor(BLACK);
		settextstyle(20, 0, "����");
		outtextxy(70, 600, "���ߵ�С˽�ģ����ֻؿ���ҫůů�ˣ��ҵ�Ů��̫�ÿ��˰ȣ�");
		outtextxy(70, 625, "�Һð������������ҵ�����Ů�죡");
		outtextxy(70, 650, "û�취��̫���ˣ�");

	}
	void begin() {
		/*��ʼ����*/
		initgraph(600, 800);
		SetWindowText(GetHWnd(), "ůů");
		mciSendString(_T("open ./bgm.mp3 alias bgm"), NULL, NULL, NULL);
		mciSendString(_T("play ./bgm.mp3 repeat"), NULL, NULL, NULL);
		

		IMAGE img3;
		loadimage(&img3, "start.jpg", 600, 800);
		putimage(0, 0, &img3);

		setbkmode(TRANSPARENT);
		settextcolor(WHITE);
		settextstyle(50, 0, "����");
		outtextxy(190, 650, "ůů֮�ж�̰����");
		_getch();
		closegraph();

		/*����˵������*/
		initgraph(600, 800);
		IMAGE img4;
		loadimage(&img4, "start2.jpg", 600, 800);
		putimage(0, 0, &img4);

		setbkmode(TRANSPARENT);
		settextcolor(WHITE);
		settextstyle(50, 0, "����");
		outtextxy(160, 60, "����˵��");
		settextstyle(30, 0, "����");
		outtextxy(60, 110, "  ��ůů�������漣��½����;��");
		outtextxy(50, 140, "    ʧȥ���������޷�ս��");
		outtextxy(60, 170, "     ����Ҫ��İ���");
		outtextxy(80, 570, "��һ�������漣��½��");
		setbkmode(TRANSPARENT);
		settextcolor(RED);
		settextstyle(30, 0, "����");
		outtextxy(60, 400, "���ݼ����ϵ� W A S D");
		outtextxy(60, 430, "W:�� A:�� S:�� D����");
		outtextxy(60, 460, "ע�⣺1����Ҫ��������");
		outtextxy(60, 490, "     2����Ҫ������ɫ�߿�");
		setbkmode(TRANSPARENT);
		settextcolor(RED);
		settextstyle(40, 0, "����");
		outtextxy(60, 520, "�����ܶ�û�ȡ��ɫ������");
		

		_getch();
		mciSendString(_T("close ./bgm.mp3 "), NULL, NULL, NULL);
		closegraph();
		/*cleardevice();
		while (1) {
			int x = 100, y = 200;
			char k = _getch();
			if (k == 'w') {
				y -= 25;
			}
			else if (k == 's') {
				y += 25;
			}
			else if (k == 'a') {
				x -= 25;
			}
			else if (k == 'd') {
				x += 25;
			}
			else if (k == ' ') {
				break;
			}
		}*/
	}
		int main()
		{
			begin();
			mciSendString(_T("open ./bgm2.mp3 "), NULL, NULL, NULL);
			mciSendString(_T("play ./bgm2.mp3 repeat"), NULL, NULL, NULL);
			/*��Ϸ���洰��*/
			initgraph(windowWidth, windowHeight);
			cleardevice();
			drawbackground();

			drawSnake();
			toDir = 4;
			char input = _getch();
			generateFood();
			drawFood(food_x, food_y);
			
			while (1) 
			{
				BeginBatchDraw();
					if (_kbhit())
					{
							moveSnake();
							drawbackground();
							checkFood();
							if (checkCollision() == 0) {
								gameover();
								_getch();
								mciSendString(_T("close ./loser.mp3 "), NULL, NULL, NULL);
								closegraph();
								break;
							}
					}
					else
					{
							autoMove();
							drawbackground();
							drawSnake();
							checkFood();
							Sleep(200);
							if (checkCollision() == 0) {
								gameover();
								_getch();
								mciSendString(_T("close ./loser.mp3 "), NULL, NULL, NULL);
								closegraph();
								break;
							}
					}
					FlushBatchDraw();
			}
			EndBatchDraw();
			_getch();
			closegraph();
			return 0;
		}