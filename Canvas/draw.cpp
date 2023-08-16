#define _CRT_SECURE_NO_WARNINGS  1
#define _CRT_SECURE_NO_WARNINGS  1
#include <stdio.h>
//#include <graphics.h>
#include<easyx.h>
//����һ���洢����Ľṹ��
struct Point {
	int x;
	int y;
};
//����һ���洢�����ݵĽṹ��
struct LineTool {
	int size;       //�ߴ�ϸ
	COLORREF color;     //�ߵ���ɫ
	struct Point beginPos;  //��ʼ����
	struct Point  endPos;//��������
	bool isDown;//����Ƿ���
};
//No.1��ʼ��ֱ��
struct LineTool* createLineTool(int size, COLORREF color) {
	struct LineTool* pLine = (struct LineTool*)malloc(sizeof(struct LineTool));
	if (pLine == NULL) {
		return NULL;
	}
	pLine->color = color;
	pLine->size = size;
	pLine->isDown = false;
	return pLine;//�����ߵ�����
}

//���û滭��ʽ
void drawStyple(int x, int y, char* contect)
{
	settextcolor(RGB(0, 0, 0));

	LOGFONT f;
	gettextstyle(&f);

	f.lfHeight = 40;
	f.lfWidth = 20;
	f.lfQuality = ANTIALIASED_QUALITY;  //��������Ϊ������ݡ�Ч��
	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName),"Segoe UI Black");
	settextstyle(&f);

	setbkmode(TRANSPARENT);   //�������屳��Ϊ͸��Ч��

	outtextxy(x, y, contect);
}



//No.2���������ʾ
void setFace() {
	initgraph(1080, 800, 7);
	setbkcolor(RGB(100, 100, 100));//��������Ϊ��ɫ
	cleardevice();
	setfillcolor(WHITE);    //���Ƴ���ɫ��ͼ��
	fillrectangle(15, 15, 1060, 800);//��ɫ��ͼ�巶Χ
	setfillcolor(RGB(195, 195, 195));//��ɫѡ���������ɫ
	fillrectangle(980, 15, 1072, 800);       //��ɫѡ������ķ�Χ
	setlinecolor(WHITE);
	line(8, 10, 1072, 10);
	line(8, 10, 8, 795);
	line(1072, 10, 1072, 795);
	setfillcolor(RED);
	fillcircle(1026, 179, 30);
	setfillcolor(BLACK);
	fillcircle(1026, 250, 30);
	setfillcolor(GREEN);
	fillcircle(1026, 330, 30);
	setfillcolor(BLUE);
	fillcircle(1026, 410, 30);
	setfillcolor(RGB(239, 136, 190));
	fillcircle(1026, 490, 30);
	setfillcolor(YELLOW);
	fillcircle(1026, 570, 30);
	setfillcolor(LIGHTGRAY);
	fillrectangle(990, 650, 1060, 730);
	char arr[] = "���";
	int x = 990 + (40 - textwidth(arr)) / 2;
	int y = 650 + (50 - textheight(arr)) / 2;
	drawStyple(x, y, arr);
}
void drawLine(struct LineTool* pTool, ExMessage m) {
	//�ж�����Ƿ��ڻ�ͼ����
	if (m.x >= 18 && m.y >= 70 && m.x < 980 && m.y <= 800) {
	/*else
		pTool->isDown = false;*/
	if (m.message == WM_LBUTTONDOWN) {
		pTool->beginPos.x = m.x;
		pTool->beginPos.y = m.y;
		pTool->isDown = true;
	}
	if (m.message == WM_LBUTTONUP) {
		pTool->isDown = false;
	}
	if (m.message == WM_MOUSEMOVE && pTool->isDown) {
		setlinestyle(PS_ENDCAP_ROUND, pTool->size);
		setlinecolor(pTool->color);
		line(pTool->beginPos.x, pTool->beginPos.y, m.x, m.y);
	}
	pTool->beginPos.x = m.x;
	pTool->beginPos.y = m.y;
}

}

int main() {
	setFace();
	HRGN rgn = CreateRectRgn(20, 15, 980, 800);
	setcliprgn(rgn);
	int k = 0;
	ExMessage m;
	//m.x = 1000, m.y = 600;
		m.message = WM_LBUTTONUP;
	struct LineTool* pLine = createLineTool(5, k);
	while (1) {
		if (peekmessage(&m, EX_MOUSE | EX_KEY)) {    
			//��֧ʵ����ɫѡ��
			if (m.x <= 1056 && m.x >= 996 && m.y >= 140 && m.y < 200 && m.message == WM_LBUTTONDOWN)
				k = RED;
			if (m.x <= 1056 && m.x >= 996 && m.y >= 220 && m.y < 280 && m.message == WM_LBUTTONDOWN)
				k = BLACK;
			if (m.x <= 1056 && m.x >= 996 && m.y >= 300 && m.y < 360 && m.message == WM_LBUTTONDOWN)
				k = GREEN;
			if (m.x <= 1056 && m.x >= 996 && m.y >= 380 && m.y < 440 && m.message == WM_LBUTTONDOWN)
				k = BLUE;
			if (m.x <= 1056 && m.x >= 996 && m.y >= 460 && m.y < 520 && m.message == WM_LBUTTONDOWN)
				k = RGB(239, 136, 190);
			if (m.x <= 1056 && m.x >= 996 && m.y >= 540 && m.y < 600 && m.message == WM_LBUTTONDOWN)
				k = YELLOW;
			pLine->color = k;
			drawLine(pLine, m);
			if (m.x >= 990 && m.x <= 1060 && m.y >= 650 && m.y <= 730 && m.message == WM_LBUTTONDOWN)
			{
				setbkcolor(WHITE);    
				clearrectangle(15, 15, 1060, 800);
			}
		}
	}
	return 0;
}
