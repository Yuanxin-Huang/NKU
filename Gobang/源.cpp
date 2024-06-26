#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <iostream>
#include<stdlib.h>
#include <algorithm>
#include<mmsystem.h>
#include<random>
#pragma comment(lib,"Winmm.lib")
using namespace std;

#define N 19
#define block_width 25
#define margin 60
#define board_width 
#define board_height
int chessBox[N][N] = { 0 };
int backBox[N][N] = { 0 };
int color=0;//1Ϊ�ڣ�-1Ϊ��
int aiColor;
int humanColor;
double checkBound = block_width * 0.4; 
int clickRow, clickCol;
int human, AI;
int humanScore[N][N];
int aiScore[N][N];
int scoreMap[N][N] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,
	0,1,2,3,3,3,3,3,3,3,3,3,3,3,3,3,2,1,0,
	0,1,2,3,4,4,4,4,4,4,4,4,4,4,4,3,2,1,0,
	0,1,2,3,4,5,5,5,5,5,5,5,5,5,4,3,2,1,0,
	0,1,2,3,4,5,6,6,6,6,6,6,6,5,4,3,2,1,0,
	0,1,2,3,4,5,6,7,7,7,7,7,6,5,4,3,2,1,0,
	0,1,2,3,4,5,6,7,8,8,8,7,6,5,4,3,2,1,0,
	0,1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2,1,0,
	0,1,2,3,4,5,6,7,8,8,8,7,6,5,4,3,2,1,0,
	0,1,2,3,4,5,6,7,7,7,7,7,6,5,4,3,2,1,0,
	0,1,2,3,4,5,6,6,6,6,6,6,6,5,4,3,2,1,0,
	0,1,2,3,4,5,5,5,5,5,5,5,5,5,4,3,2,1,0,
	0,1,2,3,4,4,4,4,4,4,4,4,4,4,4,3,2,1,0,
	0,1,2,3,3,3,3,3,3,3,3,3,3,3,3,3,2,1,0,
	0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

void drawEveryBlock(int x, int y);//��ÿһ������
void drawblock();//��ʼ�����÷���
void initBoard();//��ʼ������
void drawChess(int row, int col, int color);//������
bool checkClick(ExMessage msg);//��������λ��
int checkLimit(int n);
bool judgeWin(int clickRow, int clickCol, int checkColor);//�ж��Ƿ���������
void initialize();//��ʼ��chessBox[][]�Ա����¿�ʼ
void aiDown();//�˻���սAI����
void caculateScore();//�������
void humanPlay();//���˶�սģʽ
void aiPlay();//�˻���սģʽ
void start1();//��Ϸ��ʼ����
void start2();//ѡ���սģʽ
void begin();//����������
void colorChoose();//ѡ��������
int Max_Value(int row, int col, int depth);
int Min_Value(int row, int col, int depth);
void evaluateScore();
void evaluateValue();
void music();//BGM



//������
void drawEveryBlock(int x, int y)
{
	int left, top, right, bottom;
	left = margin+ block_width * backBox[x][0];
	top = margin + block_width * backBox[x][1];
	right = left + block_width;
	bottom = top + block_width;

	rectangle(left, top, right, bottom);
}

void drawblock()
{
	setlinestyle(PS_SOLID, 1);
	setlinecolor(BLACK);
	for (int i = 0; i < 18; ++i)
	{
		for (int j = 0; j < 18; ++j)
		{
			backBox[i][0] = i ;
			backBox[i][1] = j ;
			drawEveryBlock(i, j);
		}
	}
}


//��ʼ������
void initBoard() {
	BeginBatchDraw();
	//int boardColor = RGB(244,164,95);
	//setbkcolor(boardColor);

	cleardevice();
	IMAGE b;
	loadimage(&b, "bk.jpg", 800, 600);
	putimage(0, 0, &b);

	
	//С�ڵ�
	for (int i = 3; i <= 15; i += 6) {
		for (int j = 3; j <= 15; j += 6) {
			setfillcolor(BLACK);
			solidcircle(i * block_width + margin, j * block_width + margin, 4);
		}
	}
	drawblock();
	//num
	TCHAR s[20];
	for (int i = 0; i < 19; i++)
	{
		int num = i+1;

		setbkmode(TRANSPARENT);
		settextcolor(BLACK);
		settextstyle(NULL,NULL,"����");
		_stprintf_s(s, _T("%d"), num);
		outtextxy(margin + i * block_width - 3, margin - 15, s);
	}
	//number
	TCHAR s1[20];
	for (int i = 0; i < 19; i++)
	{
		char c = 'A'+i;

		setbkmode(TRANSPARENT);
		settextcolor(BLACK);
		settextstyle(NULL, NULL, "����");
		_stprintf_s(s1, _T("%c"),c);
		outtextxy(margin -12, margin +i*block_width-8, s1);
	}
	IMAGE i;
	loadimage(&i, "p1.jpg", 300, 500);
	putimage(515, 20, &i);


	IMAGE p3;
	loadimage(&p3, "p3.jpg", 80, 100);
	putimage(0, 0, &p3);

	EndBatchDraw();
}
//��������
void drawChess(int row, int col, int color) {
	int x = margin + col * block_width;
	int y = margin + row * block_width;

			if (color == 1) {
				setfillcolor(BLACK);
				solidcircle(x, y, 12);
			}
			else {
				setfillcolor(WHITE);
				solidcircle(x, y, 12);
			}	
			//mciSendString(_T("resume luo.mp3"), NULL, 0, NULL);
}
//����
bool checkClick(ExMessage msg) {
	int x = msg.x;
	int y = msg.y;
	int col = (x - margin) / block_width;
	int row = (y - margin) / block_width;
	int leftTopX = margin + col * block_width;
	int leftTopY = margin + row * block_width;
	double disLT, disLB, disRT, disRB;
	//Calculate 4 distances
	disLT = sqrt((x - leftTopX) * (x - leftTopX) + (y - leftTopY) * (y - leftTopY));
	disLB = sqrt((x - leftTopX) * (x - leftTopX) + (y - leftTopY - block_width) * (y - leftTopY - block_width));
	disRT = sqrt((x - leftTopX-block_width) * (x - leftTopX-block_width) + (y - leftTopY) * (y - leftTopY));
	disRB = sqrt((x - leftTopX-block_width) * (x - leftTopX-block_width) + (y - leftTopY - block_width) * (y - leftTopY - block_width));
		//Check if the distance is smaller than the boundary
	if (disLT < checkBound) {
		clickCol = col;
		clickRow = row;

	}
	else if (disLB < checkBound) {
		clickCol = col;
		clickRow = row + 1;

	}
	else if (disRT < checkBound) {
		clickCol = col + 1;
		clickRow = row;

	}

	else if (disRB < checkBound) {
		clickCol = col + 1;
		clickRow = row + 1;
	}
	else {
		return false;
	}

	if (clickCol >(N-1) || clickRow >(N-1)) return false;

	if (chessBox[clickRow][clickCol]==0) {
		chessBox[clickRow][clickCol] = color;
		music();
		return true;
	}
	else {
		
		return false;
	}

}
//��ֹ�������߽�
int checkLimit(int n) {
	if (n >= N) {
		return N - 1;
	}
	else if (n < 0) {
		return 0;
	}
	else
		return n;
}
//�ж���Ӯ
bool judgeWin(int clickRow,int clickCol,int checkColor) {
	int i = 0;
	int j = 0;
	int chess_Count = 0; 
	//�л�ʤ
	for (j = checkLimit(clickCol - 4); j <= checkLimit(clickCol + 4); j++) {
		i = clickRow;
		if (chessBox[i][j] != checkColor) {
			chess_Count = 0;
		}
		else if (chessBox[i][j] == checkColor) {
			chess_Count += 1;
		}
		if (chess_Count >= 5) {
			return true;
		}
	}
	chess_Count = 0;
	//�л�ʤ
	for (i = checkLimit(clickRow - 4); i <= checkLimit(clickRow + 4); i++) {
		j = clickCol;
		if (chessBox[i][j] != checkColor) {
			chess_Count = 0;
		}
		else if (chessBox[i][j] == checkColor) {
			chess_Count += 1;
		}
		if (chess_Count >=5) {
			return true;
		}
	}
	chess_Count = 0;
	//y=x
	for (j = checkLimit(clickCol - 4), i = checkLimit(clickRow + 4); j <= checkLimit(clickCol + 4); j++,i--) {
		
		if (chessBox[i][j] != checkColor) {
			chess_Count = 0;
		}
		else if (chessBox[i][j] == checkColor) {
			chess_Count += 1;
		}
		if (chess_Count >=5) {
			return true;
		}
		
	}
	chess_Count = 0;
//y=-x
	for (i = checkLimit(clickRow - 4), j = checkLimit(clickCol -4); i <= checkLimit(clickRow + 4); i++,j++) {
		
		if (chessBox[i][j] != checkColor) {
			chess_Count = 0;
		}
		else if (chessBox[i][j] == checkColor) {
			chess_Count += 1;
		}
		if (chess_Count >=5) {
			return true;
		}
	}

	return false;
}

//��ʼ��chessBox�Ա�����
void initialize() {
	color *= -1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			chessBox[i][j] = 0;
		}
	}
	
}


int evaluateScore(int row,int col,int color) {
	int value = scoreMap[row][col];
	int length = 0;
	int empty = 0;
	int directs[4][2] = { {1,0},{1,1},{0,1},{-1,1} };

	for (int k = 0; k < 4; k++) {
		int x = directs[k][0];
		int y = directs[k][1];
		//reset
		int chessNum = 0;
		int emptyNum = 0;
		//Calculate forword score
		for (int i = 1; i <= 4; i++)
		{
			int tempRow = row + i * y;
			int tempCol = col + i * x;
			if (tempRow >= 0 && tempRow < N && tempCol >= 0 && tempCol < N && chessBox[tempRow][tempCol] == color)
			{
				chessNum++;
			}
			else if (tempRow >= 0 && tempRow < N && tempCol >= 0 && tempCol < N && chessBox[tempRow][tempCol] == 0)
			{
				emptyNum++;
				break;
			}
			else
				break;
		}


		//Calculate backword score
		for (int i = 1; i <= 4; i++) {
			int tempRow = row - i * y;
			int tempCol = col - i * x;
			if (tempRow >= 0 && tempRow < N && tempCol >= 0 && tempCol < N && chessBox[tempRow][tempCol] == color)
			{
				chessNum++;
			}
			else if (tempRow >= 0 && tempRow < N && tempCol >= 0 && tempCol < N && chessBox[tempRow][tempCol] == 0)
			{
				emptyNum++;
				break;
			}
			else
				break;
		}

		//Check which type of chess is it.
		if (chessNum == 1) {//��������				
			if (emptyNum == 1)  //�߶�
				value += 15;
			else if (emptyNum == 2) //���
				value += 35;

		}
		else if (chessNum == 2)
		{
			if (emptyNum == 1)//�߶�
				value += 150;
			else if (emptyNum == 2)//���
				value += 300;
		}
		else if (chessNum == 3)
		{
			if (emptyNum == 1)//����
				value += 500;
			else if (emptyNum == 2)//����
				value += 2000;
		}
		else if (chessNum == 4)//����
		{
			value += 10000;
		}

	}
		return value;
}


int evaluateValue(int row, int col) {
	int value = evaluateScore(row, col,aiColor)+evaluateScore(row, col,humanColor);
	return value;
}

struct maxScorePoint {
	int row;
	int col;
};
int Max_Value(int row, int col, int depth) {
	int value = evaluateValue(row, col);
	if (depth <= 0 || value < 80000) return value;
	int maxValue = INT_MIN;
	

	for (int Row = 0; Row < N; Row++) {
		for (int Col = 0; Col < N; Col++) {
			if (chessBox[Row][Col] != 0) continue;
				chessBox[Row][Col] = aiColor;
				int temp = Min_Value(Row, Col, depth - 1);

				if (temp > maxValue) {
					maxValue = temp;
					
				}
				chessBox[Row][Col] = 0;
		}
	}
	return maxValue;
}

int Min_Value(int row, int col, int depth) {
	int value = evaluateValue(row, col);
	if (depth <= 0||value<80000) return value;
	int minValue = INT_MIN;

	for (int Row = 0; Row < N; Row++) {
		for (int Col = 0; Col < N; Col++) {
			if (chessBox[Row][Col] != 0) continue;
				chessBox[Row][Col] = humanColor;
				
				int temp = Max_Value(Row, Col, depth - 1);

				if (temp < minValue) {
					minValue = temp;
					
				}
				chessBox[Row][Col] = 0;
			
		}
	}
	return minValue;
}

maxScorePoint getMinMaxEvaluate(int depth) {
	int maxValue = INT_MIN;
	int k = 0; 
	maxScorePoint maxPoint [N*N]={0};
	for (int row = 0; row < N;row++) {
		for (int col = 0; col < N; col++) {

			if (chessBox[row][col] != 0) continue;

			chessBox[row][col] = aiColor;
			int temp = Min_Value(row, col, depth - 1);

			if (temp == maxValue) {
				maxPoint[k].row = row;
				maxPoint[k].col = col;
				k++;
			}
			if (temp > maxValue) {
				k = 0;
				memset(maxPoint, 0, sizeof(maxPoint));
				maxValue = temp;
				maxPoint[k].row = row;
				maxPoint[k].col = col;
				k++;
			}
			chessBox[row][col] = 0;
		}
	}
	int index = (int)(rand()%k);
	return maxPoint[index];
}
void aiDown() {
	maxScorePoint Point=getMinMaxEvaluate(3);
	chessBox[Point.row][Point.col] =aiColor;
	drawChess(Point.row, Point.col, aiColor);
}

void GameOver(ExMessage m) {
	
	m = getmessage(EM_MOUSE);
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {

			if (judgeWin(row, col, chessBox[row][col])) {
				
				if (chessBox[row][col] == 1) {
					IMAGE BLACKwin;
					loadimage(&BLACKwin, "BLACK.jpg", 300, 140);
					putimage(180, 220, &BLACKwin);
					mciSendString(_T("close bgm2.mp3"), NULL, 0, NULL);
					
					mciSendString(_T("open bgm3.mp3"), NULL, 0, NULL);
					mciSendString(_T("play bgm3.mp3"), NULL, 0, NULL);
					HWND hwnd = GetHWnd();
					int ret = 0;
					ret = MessageBox(hwnd, "�����ʤ\n����һ����", "��Ϸ����", MB_YESNO | MB_ICONQUESTION);
					if (ret == IDYES) {
						cleardevice();
						initialize();
						initBoard();
						mciSendString(_T("close bgm3.mp3"), NULL, 0, NULL);
					}
					else {
						mciSendString(_T("close bgm3.mp3"), NULL, 0, NULL);
						initialize();
						begin();
						
					}
				}
				else if (chessBox[row][col] == -1) {

					IMAGE WHITEwin;
					loadimage(&WHITEwin, "WHITE.jpg", 300, 140);
					putimage(180, 220, &WHITEwin);

					mciSendString(_T("close bgm2.mp3"), NULL, 0, NULL);

					mciSendString(_T("open bgm3.mp3"), NULL, 0, NULL);
					mciSendString(_T("play bgm3.mp3 repeat"), NULL, 0, NULL);

					HWND hwnd = GetHWnd();
					int ret = 0;
					ret = MessageBox(hwnd, "�����ʤ\n����һ����", "��Ϸ����", MB_YESNO | MB_ICONQUESTION);
					if (ret == IDYES) {
						cleardevice();
						initialize();
						initBoard();
						mciSendString(_T("close bgm3.mp3"), NULL, 0, NULL);
					}
					else {
						mciSendString(_T("close bgm3.mp3"), NULL, 0, NULL);
						initialize();
						begin();
					}
				}
			}

			else if (WM_KEYDOWN) {
				if (m.vkcode == VK_ESCAPE)
					exit(0);
			}

		}
	}
	

}
void music() {
	mciSendString(_T("open bgm2.mp3"), NULL, 0, NULL);
	mciSendString(_T("play bgm2.mp3 repeat"), NULL, 0, NULL);
	
}

void aiPlay() {
	mciSendString(_T("close bgm1.mp3"), NULL, 0, NULL);
	music();
	initgraph(800, 600);
	initBoard();
	
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(40, 20, "����");
	outtextxy(70, 10, "���:");
	drawChess(-1, 5, humanColor);
	outtextxy(400, 10, "AI:");
	drawChess(-1, 17.5, aiColor);

	IMAGE i;
	loadimage(&i, "p2.jpg", 300, 500);
	putimage(515, 20, &i);


	while (1) {

		ExMessage m;
		m = getmessage(EM_MOUSE);
	
		if (m.message == WM_LBUTTONDOWN && checkClick(m)) {

			drawChess(clickRow, clickCol, humanColor);
			aiDown();
			
			GameOver(m);
		}
	}
}
	

void humanPlay() {
	mciSendString(_T("close bgm1.mp3"), NULL, 0, NULL);
	music();
	initgraph(800, 600);
	initBoard();

	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(40, 20, "����");
	outtextxy(60, 10, "����:");
	drawChess(-1, 5, color);

	IMAGE i;
	loadimage(&i, "p2.jpg", 300, 500);
	putimage(515, 20, &i);

	while (1) {
		ExMessage m;
		m = getmessage(EM_MOUSE);

		if (m.message == WM_LBUTTONDOWN && checkClick(m)) {
			
			drawChess(clickRow, clickCol, color);
			GameOver(m);
			color *= -1;

			GameOver(m);
			
		}
	}
}
void start1() {
	initgraph(1000, 600);
	cleardevice();

	IMAGE begin;
	loadimage(&begin, "begin2.jpg", 1000, 600);
	putimage(0, 0, &begin);
	mciSendString(_T("open bgm1.mp3"), NULL, 0, NULL);
	mciSendString(_T("play bgm1.mp3"), NULL, 0, NULL);
	_getch();
	closegraph();
}
void start2() {
	cleardevice();

	IMAGE b1;
	loadimage(&b1, "bk2.jpg", 800, 600);
	putimage(0, 0, &b1);

	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(150, 80, "����");
	outtextxy(150, 20, "������");

	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(60, 30, "����");
	outtextxy(240, 200, "ѡ���սģʽ");
	settextstyle(50, 25, "����");
	outtextxy(240,300,"���˶�ս");
	outtextxy(240, 380, "�˻���ս");
	
}
void start3() {
	cleardevice();

	IMAGE b1;
	loadimage(&b1, "bk2.jpg", 800, 600);
	putimage(0, 0, &b1);

	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(150, 80, "����");
	outtextxy(150, 20, "������");


	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(60, 30, "����");
	outtextxy(240, 200, "ѡ��������");
	settextstyle(50, 25, "����");
	outtextxy(240, 300, "����");
	outtextxy(240, 380, "����");

}

void begin() {
	start1();
	colorChoose();
	initgraph(800, 500);
	start2();
	int a1 = 220, b1 = 315, a2 = 220, b2 = 335, a3 = 245, b3 = 325;
	setfillcolor(RED);
	POINT pts[] = { {a1, b1}, {a2, b2}, {a3,b3 } };
	fillpolygon(pts, 3);
	while (1) {
		char input = _getch();
		if (input == 's') {
			b1 += 80;
			b2 += 80;
			b3 += 80;
			if (b1 > 415 || b2 > 415 || b3 > 415) {
				a1 = 220, b1 = 315, a2 = 220, b2 = 335, a3 = 245, b3 = 325;
			}
			POINT pts1[] = { {a1, b1}, {a2, b2}, {a3,b3 } };
			start2();
			setfillcolor(RED);
			fillpolygon(pts1, 3);
			
		}
		else if (input == 'w') {
			a1 = 220, b1 = 315, a2 = 220, b2 = 335, a3 = 245, b3 = 325;
			POINT pts1[] = { {a1, b1}, {a2, b2}, {a3,b3 } };
			start2();
			setfillcolor(RED);
			fillpolygon(pts1, 3);
			
		}
		else {
			break;
		}
	}
	
	if (b3 == 325) {
		humanPlay();
	}
	else {
		if (color == 1) {
				humanColor = 1;
				aiColor = -1;	
		}
		else {
			color == -1;
			humanColor = -1;
			aiColor = 1;
		}
		aiPlay();
	}
	
}

void colorChoose() {

	initgraph(800, 500);
	start3();
	int a1 = 220, b1 = 315, a2 = 220, b2 = 335, a3 = 245, b3 = 325;
	setfillcolor(RED);
	POINT pts[] = { {a1, b1}, {a2, b2}, {a3,b3 } };
	fillpolygon(pts, 3);
	while (1) {
		char input = _getch();
		if (input == 's') {
			b1 += 80;
			b2 += 80;
			b3 += 80;
			if (b1 > 415 || b2 > 415 || b3 > 415) {
				a1 = 220, b1 = 315, a2 = 220, b2 = 335, a3 = 245, b3 = 325;
			}
			POINT pts1[] = { {a1, b1}, {a2, b2}, {a3,b3 } };
			start3();
			setfillcolor(RED);
			fillpolygon(pts1, 3);

		}
		else if (input == 'w') {
			a1 = 220, b1 = 315, a2 = 220, b2 = 335, a3 = 245, b3 = 325;
			POINT pts1[] = { {a1, b1}, {a2, b2}, {a3,b3 } };
			start3();
			setfillcolor(RED);
			fillpolygon(pts1, 3);

		}
		else {
			closegraph();
			break;
		}
	}
		if (b3 == 325) {
			color = 1;
		}
		else {
			color = -1;
		}
}
int main(){
	begin();	
	return 0;
}