#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<MMSystem.h>
#include<conio.h>
#include <stdbool.h>
#include"head.h"
#pragma comment(lib,"winmm.lib")

//播放BGM
void BGM1();
//显示首页
void firstpage();
//进入游戏检测
void testspace();
//设置界面
void set();
//停止播放、切换BGM
void BGM2();
//画蛇
void drawsnake();
//蛇随机位置
void snakepos();
//打印
void showbackground();
//蛇运动
void snakemove();
//销毁老蛇
void destroysnake();
//蛇改变方向
void changedir();
//蛇死亡判断
bool tobe_ornot_tobe();
//产生吃的
void food();
//蛇吃食物变长
void grow();
//侧边栏
void score();

int main(void)
{
	//显示首页
	firstpage();
	//播放BGM
	BGM1();
	//检测空格键
	testspace();
	//设置
	set();
	//停止播放、切换BGM
	BGM2();
	//清屏
	system("cls");
	//蛇随机位置
	snakepos();
	showbackground();
	//打印游戏
	while (1)
	{
		system("cls");
		//蛇变长
		grow();
		//产生吃的
		food();
		//改变方向
		changedir();
		//凉凉
		if (false == tobe_ornot_tobe())
		{
			printf("咋整的？你挂了！\n");
			printf("你的最终得分为:%d分！\n", g_score);
			break;
		}
		//蛇运动
		snakemove();
		//显示背景
		showbackground();
		//侧边栏
		score();
		//刷新频率
		Sleep(g_speed);
	}

	system("pause");

	return 0;
}


//显示首页
void firstpage()
{
	printf("\n\n\n");
	printf("***************************************************\n\n");
	printf("               《欢迎进入BUG蛇游戏！》\n\n\n");
	printf("                */W A S D以控制方向/*\n");
	printf("                */ 空格 以进入游戏 /*\n\n\n");
	printf("***************************************************\n");
}

//播放BGM
void BGM1()
{
	PlaySound(".\\GARNiDELiA - 極楽浄土.wav", NULL, SND_FILENAME | SND_ASYNC);
}

//进入游戏检测
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

//停止播放、切换BGM
void BGM2()
{
	PlaySound(NULL, 0, 0);
	PlaySound(".\\千年食谱颂.wav", NULL, SND_FILENAME | SND_ASYNC);
}

//打印
void showbackground()
{
	int i;

	for (i = 0; i < 25; i++)
	{
		printf(g_arrBackground[i]);
	}
}

//蛇的随机位置
void snakepos()
{
	int pX = -1, pY = -1;

	srand((unsigned int)time(NULL));//我种下一颗种子

	pX = rand() % 18 + 3;//防止一出来就撞墙
	pY = rand() % 22 + 1;
	//初始第一节（蛇头）
	g_arrsnake[0][0] = pY;//行
	g_arrsnake[0][1] = pX * 2;//列
	g_arrsnake[0][2] = to_west;//方向
	//初始第二节
	g_arrsnake[1][0] = pY;//行
	g_arrsnake[1][1] = pX * 2 + 2;//列
	g_arrsnake[1][2] = to_west;//方向


	//画到地图上
	drawsnake();

}

//画蛇
void drawsnake()
{
	int i;
	for (i = 0; g_arrsnake[i][0] != 0; i++)
	{
		strncpy(&g_arrBackground[g_arrsnake[i][0]][g_arrsnake[i][1]], "■", 2);
	}
}

//销毁老蛇
void destroysnake()
{
	int i;
	for (i = 0; g_arrsnake[i][0] != 0; i++)
	{
		strncpy(&g_arrBackground[g_arrsnake[i][0]][g_arrsnake[i][1]], "  ", 2);
	}
}


//蛇运动
void snakemove()
{
	int i = length - 1;

	//销毁老蛇
	destroysnake();

	for (i; i >= 1; i--)
	{
		//过滤不存在的蛇
		if (0 == g_arrsnake[i][0])
		{
			continue;
		}
		//前一个赋值给当前节点
		g_arrsnake[i][0] = g_arrsnake[i - 1][0];
		g_arrsnake[i][1] = g_arrsnake[i - 1][1];
		g_arrsnake[i][2] = g_arrsnake[i - 1][2];

	}
	//蛇头向前、转弯
	g_arrsnake[0][2] = g_nsnakedir;//改变方向

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

//蛇改变方向
void changedir()
{
	//另外要防止蛇倒悬掉头
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

//蛇死亡判断
bool tobe_ornot_tobe()
{
	//蛇头前进方向的下一个是方块
	if (to_west == g_arrsnake[0][2] || to_east == g_arrsnake[0][2])
	{
		if (0 == strncmp(&g_arrBackground[g_arrsnake[0][0]][g_arrsnake[0][1] + g_arrsnake[0][2]], "■", 2))
		{
			return false;
		}
	}

	else if (to_north == g_arrsnake[0][2] || to_south == g_arrsnake[0][2])
	{
		if (0 == strncmp(&g_arrBackground[g_arrsnake[0][1]][g_arrsnake[0][0] + g_arrsnake[0][2]], "■", 2))
		{
			return false;
		}
	}

	return true;
}

//产生吃的
void food()
{
	int i;
	//判断是否被吃掉了
	if (false == g_testfood)
	{
		return;
	}

	//产生随机坐标
	srand((unsigned int)time(NULL));//我种下一颗种子

	while (1)
	{
		bool aflag = true;

		aX = rand() % 17 + 2;//考虑到控制台反应速度，食物也不在边缘生成
		aY = rand() % 19 + 2;

		for (i = 0; g_arrsnake[i][0] != 0; i++);
		{
			//避免与蛇重合
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

	//画出食物
	strncpy(&g_arrBackground[aX][aY * 2], "★", 2);
	//关上一楼的大门
	g_testfood = false;
}

//吃食物变长
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

//侧边栏
void score()
{
	COORD rd;
	rd.X = 55;
	rd.Y = 8;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	printf("%s,欢迎进入游戏！", str);
	rd.X = 58;
	rd.Y = 10;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	printf("您的分数为：\n");
	rd.X = 65;
	rd.Y = 11;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	printf("%d", g_score);
}

//设置界面
void set()
{
	system("cls");
	printf("请输入您的昵称：(按回车以确定）\n");
	scanf("%s", str);
	system("cls");
	printf("请设置游戏速度\n");
	printf("1、龟速\n");
	printf("2、正常\n");
	printf("3、光速\n");
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