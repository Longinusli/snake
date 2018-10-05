#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<MMSystem.h>
#include<conio.h>
#include <stdbool.h>
#include"head.h"
#pragma comment(lib,"winmm.lib")

//����BGM
void BGM1();
//��ʾ��ҳ
void firstpage();
//������Ϸ���
void testspace();
//���ý���
void set();
//ֹͣ���š��л�BGM
void BGM2();
//����
void drawsnake();
//�����λ��
void snakepos();
//��ӡ
void showbackground();
//���˶�
void snakemove();
//��������
void destroysnake();
//�߸ı䷽��
void changedir();
//�������ж�
bool tobe_ornot_tobe();
//�����Ե�
void food();
//�߳�ʳ��䳤
void grow();
//�����
void score();

int main(void)
{
	//��ʾ��ҳ
	firstpage();
	//����BGM
	BGM1();
	//���ո��
	testspace();
	//����
	set();
	//ֹͣ���š��л�BGM
	BGM2();
	//����
	system("cls");
	//�����λ��
	snakepos();
	showbackground();
	//��ӡ��Ϸ
	while (1)
	{
		system("cls");
		//�߱䳤
		grow();
		//�����Ե�
		food();
		//�ı䷽��
		changedir();
		//����
		if (false == tobe_ornot_tobe())
		{
			printf("զ���ģ�����ˣ�\n");
			printf("������յ÷�Ϊ:%d�֣�\n", g_score);
			break;
		}
		//���˶�
		snakemove();
		//��ʾ����
		showbackground();
		//�����
		score();
		//ˢ��Ƶ��
		Sleep(g_speed);
	}

	system("pause");

	return 0;
}


//��ʾ��ҳ
void firstpage()
{
	printf("\n\n\n");
	printf("***************************************************\n\n");
	printf("               ����ӭ����BUG����Ϸ����\n\n\n");
	printf("                */W A S D�Կ��Ʒ���/*\n");
	printf("                */ �ո� �Խ�����Ϸ /*\n\n\n");
	printf("***************************************************\n");
}

//����BGM
void BGM1()
{
	PlaySound(".\\GARNiDELiA - �O�S����.wav", NULL, SND_FILENAME | SND_ASYNC);
}

//������Ϸ���
void testspace()
{
	char chinput;
	while (1)
	{
		chinput = _getch();
		if (' ' == chinput)
		{
			break;
		}
	}
}

//ֹͣ���š��л�BGM
void BGM2()
{
	PlaySound(NULL, 0, 0);
	PlaySound(".\\ǧ��ʳ����.wav", NULL, SND_FILENAME | SND_ASYNC);
}

//��ӡ
void showbackground()
{
	int i;

	for (i = 0; i < 25; i++)
	{
		printf(g_arrBackground[i]);
	}
}

//�ߵ����λ��
void snakepos()
{
	int pX = -1, pY = -1;

	srand((unsigned int)time(NULL));//������һ������

	pX = rand() % 18 + 3;//��ֹһ������ײǽ
	pY = rand() % 22 + 1;
	//��ʼ��һ�ڣ���ͷ��
	g_arrsnake[0][0] = pY;//��
	g_arrsnake[0][1] = pX * 2;//��
	g_arrsnake[0][2] = to_west;//����
	//��ʼ�ڶ���
	g_arrsnake[1][0] = pY;//��
	g_arrsnake[1][1] = pX * 2 + 2;//��
	g_arrsnake[1][2] = to_west;//����


	//������ͼ��
	drawsnake();

}

//����
void drawsnake()
{
	int i;
	for (i = 0; g_arrsnake[i][0] != 0; i++)
	{
		strncpy(&g_arrBackground[g_arrsnake[i][0]][g_arrsnake[i][1]], "��", 2);
	}
}

//��������
void destroysnake()
{
	int i;
	for (i = 0; g_arrsnake[i][0] != 0; i++)
	{
		strncpy(&g_arrBackground[g_arrsnake[i][0]][g_arrsnake[i][1]], "  ", 2);
	}
}


//���˶�
void snakemove()
{
	int i = length - 1;

	//��������
	destroysnake();

	for (i; i >= 1; i--)
	{
		//���˲����ڵ���
		if (0 == g_arrsnake[i][0])
		{
			continue;
		}
		//ǰһ����ֵ����ǰ�ڵ�
		g_arrsnake[i][0] = g_arrsnake[i - 1][0];
		g_arrsnake[i][1] = g_arrsnake[i - 1][1];
		g_arrsnake[i][2] = g_arrsnake[i - 1][2];

	}
	//��ͷ��ǰ��ת��
	g_arrsnake[0][2] = g_nsnakedir;//�ı䷽��

	if (to_west == g_arrsnake[0][2] || to_east == g_arrsnake[0][2])
	{
		g_arrsnake[0][1] += g_arrsnake[0][2];
	}
	else
	{
		g_arrsnake[0][0] += g_arrsnake[0][2];
	}

	drawsnake();
}

//�߸ı䷽��
void changedir()
{
	//����Ҫ��ֹ�ߵ�����ͷ
	if (GetAsyncKeyState('W') && g_arrsnake[0][2] != to_south)
	{
		g_nsnakedir = to_north;
	}

	else if (GetAsyncKeyState('S') && g_arrsnake[0][2] != to_north)
	{
		g_nsnakedir = to_south;
	}

	else if (GetAsyncKeyState('A') && g_arrsnake[0][2] != to_east)
	{
		g_nsnakedir = to_west;
	}

	else if (GetAsyncKeyState('D') && g_arrsnake[0][2] != to_west)
	{
		g_nsnakedir = to_east;
	}

}

//�������ж�
bool tobe_ornot_tobe()
{
	//��ͷǰ���������һ���Ƿ���
	if (to_west == g_arrsnake[0][2] || to_east == g_arrsnake[0][2])
	{
		if (0 == strncmp(&g_arrBackground[g_arrsnake[0][0]][g_arrsnake[0][1] + g_arrsnake[0][2]], "��", 2))
		{
			return false;
		}
	}

	else if (to_north == g_arrsnake[0][2] || to_south == g_arrsnake[0][2])
	{
		if (0 == strncmp(&g_arrBackground[g_arrsnake[0][1]][g_arrsnake[0][0] + g_arrsnake[0][2]], "��", 2))
		{
			return false;
		}
	}

	return true;
}

//�����Ե�
void food()
{
	int i;
	//�ж��Ƿ񱻳Ե���
	if (false == g_testfood)
	{
		return;
	}

	//�����������
	srand((unsigned int)time(NULL));//������һ������

	while (1)
	{
		bool aflag = true;

		aX = rand() % 17 + 2;//���ǵ�����̨��Ӧ�ٶȣ�ʳ��Ҳ���ڱ�Ե����
		aY = rand() % 19 + 2;

		for (i = 0; g_arrsnake[i][0] != 0; i++);
		{
			//���������غ�
			if (aX == g_arrsnake[i][0] && aY == g_arrsnake[i][1])
			{
				aflag = false;
				break;
			}
		}
		if (true == aflag)
		{
			break;
		}
	}

	//����ʳ��
	strncpy(&g_arrBackground[aX][aY * 2], "��", 2);
	//����һ¥�Ĵ���
	g_testfood = false;
}

//��ʳ��䳤
void grow()
{
	if (g_arrsnake[0][0] == aX && g_arrsnake[0][1] == aY * 2)
	{
		if (to_east == g_arrsnake[g_snakelength][2])
		{
			g_arrsnake[g_snakelength + 1][0] = g_arrsnake[g_snakelength][0];
			g_arrsnake[g_snakelength + 1][1] = g_arrsnake[g_snakelength][0] - 2;
			g_arrsnake[g_snakelength + 1][2] = g_arrsnake[g_snakelength][0];
		}
		else if (to_west == g_arrsnake[g_snakelength][2])
		{
			g_arrsnake[g_snakelength + 1][0] = g_arrsnake[g_snakelength][0];
			g_arrsnake[g_snakelength + 1][1] = g_arrsnake[g_snakelength][0] + 2;
			g_arrsnake[g_snakelength + 1][2] = g_arrsnake[g_snakelength][0];
		}
		else if (to_north == g_arrsnake[g_snakelength][2])
		{
			g_arrsnake[g_snakelength + 1][0] = g_arrsnake[g_snakelength][0] + 1;
			g_arrsnake[g_snakelength + 1][1] = g_arrsnake[g_snakelength][0];
			g_arrsnake[g_snakelength + 1][2] = g_arrsnake[g_snakelength][0];
		}
		else if (to_south == g_arrsnake[g_snakelength][2])
		{
			g_arrsnake[g_snakelength + 1][0] = g_arrsnake[g_snakelength][0] - 1;
			g_arrsnake[g_snakelength + 1][1] = g_arrsnake[g_snakelength][0];
			g_arrsnake[g_snakelength + 1][2] = g_arrsnake[g_snakelength][0];
		}
		g_snakelength++;
		g_testfood = true;
		g_score = g_score + 10;
	}
}

//�����
void score()
{
	COORD rd;
	rd.X = 55;
	rd.Y = 8;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	printf("%s,��ӭ������Ϸ��", str);
	rd.X = 58;
	rd.Y = 10;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	printf("���ķ���Ϊ��\n");
	rd.X = 65;
	rd.Y = 11;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	printf("%d", g_score);
}

//���ý���
void set()
{
	system("cls");
	printf("�����������ǳƣ�(���س���ȷ����\n");
	scanf("%s", str);
	system("cls");
	printf("��������Ϸ�ٶ�\n");
	printf("1������\n");
	printf("2������\n");
	printf("3������\n");
	char chinput;
	while (1)
	{
		chinput = _getch();
		if ('1' == chinput)
		{
			g_speed = 500;
			break;
		}
		else if ('2' == chinput)
		{
			g_speed = 150;
			break;
		}
		else if ('3' == chinput)
		{
			g_speed = 50;
			break;
		}
	}
}